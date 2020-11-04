
/***
 *     ▄████▄  ▒██   ██▒ ██▒   █▓ █    ██   ██████ ▓█████  ██▀███
 *    ▒██▀ ▀█  ▒▒ █ █ ▒░▓██░   █▒ ██  ▓██▒▒██    ▒ ▓█   ▀ ▓██ ▒ ██▒
 *    ▒▓█    ▄ ░░  █   ░ ▓██  █▒░▓██  ▒██░░ ▓██▄   ▒███   ▓██ ░▄█ ▒
 *    ▒▓▓▄ ▄██▒ ░ █ █ ▒   ▒██ █░░▓▓█  ░██░  ▒   ██▒▒▓█  ▄ ▒██▀▀█▄
 *    ▒ ▓███▀ ░▒██▒ ▒██▒   ▒▀█░  ▒▒█████▓ ▒██████▒▒░▒████▒░██▓ ▒██▒
 *    ░ ░▒ ▒  ░▒▒ ░ ░▓ ░   ░ ▐░  ░▒▓▒ ▒ ▒ ▒ ▒▓▒ ▒ ░░░ ▒░ ░░ ▒▓ ░▒▓░
 *      ░  ▒   ░░   ░▒ ░   ░ ░░  ░░▒░ ░ ░ ░ ░▒  ░ ░ ░ ░  ░  ░▒ ░ ▒░
 *    ░         ░    ░       ░░   ░░░ ░ ░ ░  ░  ░     ░     ░░   ░
 *    ░ ░       ░    ░        ░     ░           ░     ░  ░   ░
 *    ░                      ░
 *
 *
 *	 APOFilter
 *	 24 April 2019
 *	 Class for chaining APO lib's
 */

#include "stdafx.h"
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "APOFilter.h"
//#include <math.h>

using namespace std;

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

APOFilter::APOFilter(GUID efguid, FilterEngine * e)
	:_effectguid(efguid), _eapo(e) {}

std::vector<std::wstring> APOFilter::initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames)
{
#define LEAVE_(b)  \
		 bypass = b; return channelNames;

	HRESULT hr = 0;
	EDataFlow devicetype = eRender;
	WAVEFORMATEX* sf;
	channelCount = channelNames.size();

	if (channelCount == 0) {
		LEAVE_(true)
	}
	if (_effectguid == GUID_NULL) {
		LEAVE_(true)
	}
	if (_eapo->getDeviceGuid() == L"") {
		TraceF(L"APO: Device guid not specified");
		LEAVE_(true)
	}
	
	//calc buffer size
	size_t buffersize = ((maxFrameCount * channelCount) * sizeof(float)) * 2;

	bufferinput = reinterpret_cast<float*> (MemoryHelper::alloc(buffersize));
	memset(bufferinput, 0, buffersize);

	bufferoutput = reinterpret_cast<float*>((unsigned char*)bufferinput + buffersize / 2);

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		reinterpret_cast<void**>(&pEnumerator));
	if (SUCCEEDED(hr) || 0 == pEnumerator)
	{
		IMMDevice* imd;
		IMMEndpoint* ime;
		std::wstring fulldevice = L"{0.0.0.00000000}.";

		fulldevice += _eapo->getDeviceGuid();
		hr = (this->pEnumerator)->GetDevice(fulldevice.c_str(), &imd);
		if (SUCCEEDED(hr))
		{
			imd->QueryInterface(__uuidof(IMMEndpoint), reinterpret_cast<void**> (&ime));
			ime->GetDataFlow(&devicetype);
			ime->Release();
			imd->Release();
		}

		hr = (this->pEnumerator)->EnumAudioEndpoints(
			devicetype, DEVICE_STATE_ACTIVE,
			&(this->pCollection));
		if (SUCCEEDED(hr) || 0 == pCollection)
		{
			hr = (this->pEnumerator)->GetDefaultAudioEndpoint(devicetype, eMultimedia, &pEndpoint);
			if (SUCCEEDED(hr))
			{
				hr = (this->pEndpoint)->Activate(__uuidof(IAudioClient), CLSCTX_ALL, 0, reinterpret_cast<void**> (&iAudClient));
				if (SUCCEEDED(hr))
				{
					hr = (this->iAudClient)->GetMixFormat(&sf);
				}
			}
		}	
	}

	//Initialize
	try
	{
		hr = CoCreateInstance(_effectguid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IAudioProcessingObject), reinterpret_cast<void**> (&APO));
		if (SUCCEEDED(hr))
		{
			hr = (this->APO)->QueryInterface(__uuidof(IAudioProcessingObjectRT), reinterpret_cast<void**> (&APORT));
			if (SUCCEEDED(hr))
			{
				hr = (this->APO)->QueryInterface(__uuidof(IAudioProcessingObjectConfiguration), reinterpret_cast<void**> (&APOCfg));
				if (SUCCEEDED(hr))
				{

					memset(&initstruct, 0, sizeof(APOInitSystemEffects2));

					hr = pEndpoint->OpenPropertyStore(
						STGM_READ, &pProps);
					if ((SUCCEEDED(hr)) || 0 != pProps)
					{
						//Get apo settings

						try
						{
							void* hlp = reinterpret_cast<IPropertyStoreFX*>(MemoryHelper::alloc(sizeof(IPropertyStoreFX)));
							if (hlp != 0) {
								fxprop = new(hlp) IPropertyStoreFX((this->_eapo)->getDeviceGuid(), KEY_READ);
								if (FAILED(fxprop->TryOpenPropertyStoreRegKey()))
								{
									TraceF(L"APO: This audio device Guid: %s Name: %s does not contain FxProperties section in registry",
										(this->_eapo)->getDeviceGuid().data(),
										(this->_eapo)->getDeviceName().data());
								}
							}
						}
						catch (...)
						{
							//...
						}

						initstruct.APOInit.cbSize = sizeof(APOInitSystemEffects);
						initstruct.APOInit.clsid = _effectguid;

						//IPropertyStore object !
						initstruct.pAPOEndpointProperties = pProps;
						initstruct.pAPOSystemEffectsProperties = reinterpret_cast<IPropertyStore*>(fxprop);

						//IMMDeviceCollection object !
						initstruct.pDeviceCollection = pCollection;

						/* only for APOInitSystemEffects2 structure
						initstruct.nSoftwareIoDeviceInCollection = 0;
						initstruct.nSoftwareIoConnectorIndex = 0;
						initstruct.AudioProcessingMode = AudioProcessingMode;
						initstruct.InitializeForDiscoveryOnly = InitializeForDiscoveryOnly;
						*/
					}

					hr = (this->APO)->Initialize(sizeof(APOInitSystemEffects), reinterpret_cast<BYTE*> (&initstruct));
					if (SUCCEEDED(hr))
					{
						hr = (this->APO)->GetRegistrationProperties(&APOInfo);
						if (SUCCEEDED(hr))
						{
							TraceF(L"APO: Successfully initialized Name: %s "
								"Copyright: %s Max Input cconnections %d "
								" Max Output connections %d "
								" APO interfaces count %d ",
								APOInfo->szFriendlyName,
								APOInfo->szCopyrightInfo,
								APOInfo->u32MaxInputConnections,
								APOInfo->u32MaxOutputConnections,
								APOInfo->u32NumAPOInterfaces);
						}
					}
				}
			}
		}
	}
	catch (...) {
		LEAVE_(true)
	}

	WAVEFORMATEX w = { 0 };
	w.nChannels = static_cast<WORD>(channelCount);
	w.nSamplesPerSec = static_cast<DWORD>(sampleRate);
	
	w.wFormatTag = (w.wBitsPerSample = sf ? sf->wBitsPerSample : 32) < 32 ?
		WAVE_FORMAT_PCM :
		WAVE_FORMAT_IEEE_FLOAT;

	w.nAvgBytesPerSec = w.nSamplesPerSec * (w.nBlockAlign = (w.wBitsPerSample * w.nChannels) / 8);
	
	hr = CreateAudioMediaType(&w, sizeof(WAVEFORMATEX), &iAudType);
	if (SUCCEEDED(hr) || 0 == iAudType)
	{
		//setting buffer
		pIn_.u32BufferFlags = BUFFER_VALID;
		pIn_.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
		pIn_.pBuffer = reinterpret_cast<UINT_PTR>(bufferinput);

		pOut_.u32BufferFlags = BUFFER_INVALID;
		pOut_.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
		pOut_.pBuffer = reinterpret_cast<UINT_PTR>(bufferoutput);

		//Configure input buffer
		coDeskIn_.Type = APO_CONNECTION_BUFFER_TYPE_ALLOCATED;
		coDeskIn_.u32Signature = APO_CONNECTION_DESCRIPTOR_SIGNATURE;
		coDeskIn_.u32MaxFrameCount = maxFrameCount;
		coDeskIn_.pFormat = iAudType;
		coDeskIn_.pBuffer = reinterpret_cast<UINT_PTR>(bufferinput);

		//Configure Out buffer
		coDeskOut_.Type = APO_CONNECTION_BUFFER_TYPE_EXTERNAL;
		coDeskOut_.u32Signature = APO_CONNECTION_DESCRIPTOR_SIGNATURE;
		coDeskOut_.u32MaxFrameCount = maxFrameCount;
		coDeskOut_.pFormat = iAudType;
		coDeskOut_.pBuffer = reinterpret_cast<UINT_PTR>(bufferoutput);
	
		try
		{
			//put settings to apo
			(this->APOCfg)->LockForProcess(1, &coDeskIn, 1, &coDeskOut);
			CM_RELEASE(sf)
			LEAVE_(false)
		}
		catch (...) {
			//...
		}

	}

	LEAVE_(true)
}

#pragma AVRT_CODE_BEGIN
void APOFilter::process(float** output, float** input, unsigned frameCount)
{
	if (bypass)
	{
		for (unsigned i = 0; i < channelCount; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		return;
	}

	__try
	{
		//write
		for (size_t c = 0; c < channelCount; c++)
		{
			for (unsigned fc = 0; fc < frameCount; fc++)
			{
				((float*)(bufferinput+c))[fc * channelCount] = input[c][fc];
			}
		}

		//pInput
		pIn_.u32ValidFrameCount = frameCount;

		//pOutput
		pOut_.u32BufferFlags = BUFFER_INVALID;
		pOut_.u32ValidFrameCount = frameCount;

		//chilling buffer
		APORT->APOProcess(1, &pIn, 1, &pOut); //Process

		//Read
		for (size_t c = 0; c < channelCount; c++)
		{
			for (size_t fc = 0; fc < frameCount; fc++)
			{
				output[c][fc] = ((float*)(bufferoutput+c))[fc * channelCount];
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		if (reportCrash)
		{
			TraceF(L"The APO plugin crashed during audio processing.");
			reportCrash = false;
		}

		for (unsigned i = 0; i < channelCount; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		bypass = true;
	}
}
#pragma AVRT_CODE_END

APOFilter::~APOFilter()
{
	try {
		MH_RELEASE(bufferinput)

			SAFE_RELEASE(iAudType)
			SAFE_RELEASE(iAudClient)

			CM_RELEASE(APOInfo)
			
			SAFE_RELEASE(pEnumerator)
			SAFE_RELEASE(pCollection)
			SAFE_RELEASE(pEndpoint)
			SAFE_RELEASE(pProps)

#ifndef _IPROP_FX_INTERNAL
			SAFE_RELEASE(fxprop)
#endif

			if (bypass == false)
			{
				if (APOCfg != 0) {
					APOCfg->UnlockForProcess();
				}

				if (APO != 0) {
					APO->Reset();
				}
			}

		SAFE_RELEASE(APOCfg)
			SAFE_RELEASE(APORT)
			SAFE_RELEASE(APO)

#ifdef _IPROP_FX_INTERNAL
			MH_RELEASE(fxprop)
#endif // !_IPROP_FX_INTERNAL

			//CoFreeUnusedLibrariesEx(0, 0); //is Unstable
	}
	catch (...) {
		TraceF(L"APO: Deinitialize failed");
	}
}