
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
	channelCount = channelNames.size();
	HRESULT hr = 0;
	EDataFlow devicetype = eRender;
	WAVEFORMATEX* sf;

	if (channelCount == 0) {
		goto LEAVE_;
	}
	if (_effectguid == GUID_NULL) {
		goto LEAVE_;
	}
	if (_eapo->getDeviceGuid() == L"") {
		TraceF(L"APO: Device guid not specified");
		goto LEAVE_;
	}

	//calc buffer size
	int frameCount = sampleRate / 100;
	//(sampleRate * 0x51eb851f) >> 0x24 >> 1;
	//(sampleRate * 0x51eb851f) >> 0x24 >> 0x1f;

	size_t buffersize = ((frameCount * channelCount) * sizeof(float)) * 2;
	
	bufferinput = (float*) MemoryHelper::alloc(buffersize);
	memset(bufferinput, 0, buffersize);

	bufferoutput = (float*) ((char*)bufferinput + (buffersize / 2));
	
	if ((SUCCEEDED(CoCreateInstance
	(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		reinterpret_cast<void**>(&pEnumerator)
	))) || 0 == pEnumerator)
	{
		IMMDevice* imd = 0;
		IMMEndpoint* ime = 0;
		std::wstring fulldevice = L"{0.0.0.00000000}.";

		fulldevice += _eapo->getDeviceGuid();

		if (SUCCEEDED(pEnumerator->GetDevice(fulldevice.c_str(), &imd)))
		{
			imd->QueryInterface(__uuidof(IMMEndpoint), reinterpret_cast<void**> (&ime));
			ime->GetDataFlow(&devicetype);
			ime->Release();
			imd->Release();
		}

		if ((SUCCEEDED(pEnumerator->EnumAudioEndpoints(devicetype, DEVICE_STATE_ACTIVE, &pCollection))) || 0 == pCollection)
		{
			if (SUCCEEDED(pEnumerator->GetDefaultAudioEndpoint(devicetype, eMultimedia, &pEndpoint)))
			{
				if (SUCCEEDED(pEndpoint->Activate(__uuidof(IAudioClient), CLSCTX_ALL, 0, reinterpret_cast<void**> (&iAudClient))))
				{
					hr = iAudClient->GetMixFormat(&sf);
				}
			}
		}	
	}

	//Initialize
	try
	{
		if (SUCCEEDED(CoCreateInstance(_effectguid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IAudioProcessingObject), reinterpret_cast<void**> (&APO))))
		{
			if (SUCCEEDED(APO->QueryInterface(__uuidof(IAudioProcessingObjectRT), reinterpret_cast<void**> (&APORT))))
			{
				if (SUCCEEDED(APO->QueryInterface(__uuidof(IAudioProcessingObjectConfiguration), reinterpret_cast<void**> (&APOCfg))))
				{
					memset(&initstruct, 0, sizeof(APOInitSystemEffects2));

					if ((SUCCEEDED(pEndpoint->OpenPropertyStore(STGM_READ, &pProps))))
					{
						try
						{
							void* hlp = reinterpret_cast<IPropertyStoreFX*>(MemoryHelper::alloc(sizeof(IPropertyStoreFX)));
							if (hlp != 0) {
								fxprop = new(hlp) IPropertyStoreFX(_eapo->getDeviceGuid(), KEY_READ);
								if (true == fxprop->TryOpenPropertyStoreRegKey())
								{
									TraceF(L"APO: This audio device Guid: %s Name: %s does not contain FxProperties section in registry",
										_eapo->getDeviceGuid().data(),
										_eapo->getDeviceName().data());
								}
							}
						}
						catch (...)
						{
							goto LEAVE_;
						}

						initstruct.APOInit.cbSize = sizeof(APOInitSystemEffects);
						initstruct.APOInit.clsid = _effectguid;

						//IPropertyStore
						initstruct.pAPOEndpointProperties = pProps;
						initstruct.pAPOSystemEffectsProperties = reinterpret_cast<IPropertyStore*>(fxprop);

						//IMMDeviceCollection
						initstruct.pDeviceCollection = pCollection;

						/* only for APOInitSystemEffects2 structure
						initstruct.nSoftwareIoDeviceInCollection = 0;
						initstruct.nSoftwareIoConnectorIndex = 0;
						initstruct.AudioProcessingMode = AudioProcessingMode;
						initstruct.InitializeForDiscoveryOnly = InitializeForDiscoveryOnly;
						*/
					}

					if (SUCCEEDED(APO->Initialize(sizeof(APOInitSystemEffects), reinterpret_cast<BYTE*> (&initstruct))))
					{
						if (SUCCEEDED(APO->GetRegistrationProperties(&APOInfo)))
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
		goto LEAVE_;
	}

	if (APOCfg)
	{
		WAVEFORMATEX w = { 0 };
		w.nChannels = (WORD) channelCount;
		w.nSamplesPerSec = (DWORD) sampleRate;

		w.wFormatTag = (w.wBitsPerSample = sf ? sf->wBitsPerSample : 32) < 32 ?
			WAVE_FORMAT_PCM :
			WAVE_FORMAT_IEEE_FLOAT;

		w.nAvgBytesPerSec = w.nSamplesPerSec * (w.nBlockAlign = (w.wBitsPerSample * w.nChannels) / 8);

		if ((SUCCEEDED(CreateAudioMediaType(&w, sizeof(WAVEFORMATEX), &iAudType))) || 0 == iAudType)
		{
			//setting buffer
			pIn_.u32BufferFlags = BUFFER_VALID;
			pIn_.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
			pIn_.pBuffer = (UINT_PTR) bufferinput;

			pOut_.u32BufferFlags = BUFFER_INVALID;
			pOut_.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
			pOut_.pBuffer = (UINT_PTR) bufferoutput;

			//Configure input buffer
			coDeskIn_.Type = APO_CONNECTION_BUFFER_TYPE_ALLOCATED;
			coDeskIn_.u32Signature = APO_CONNECTION_DESCRIPTOR_SIGNATURE;
			coDeskIn_.u32MaxFrameCount = frameCount;
			coDeskIn_.pFormat = iAudType;
			coDeskIn_.pBuffer = (UINT_PTR) bufferinput;

			//Configure Out buffer
			coDeskOut_.Type = APO_CONNECTION_BUFFER_TYPE_EXTERNAL;
			coDeskOut_.u32Signature = APO_CONNECTION_DESCRIPTOR_SIGNATURE;
			coDeskOut_.u32MaxFrameCount = frameCount;
			coDeskOut_.pFormat = iAudType;
			coDeskOut_.pBuffer = (UINT_PTR) bufferoutput;

			try
			{
				//put settings to apo
				APOCfg->LockForProcess(1, &coDeskIn, 1, &coDeskOut);
				CM_RELEASE(sf)
					bypass = false;
					goto LEAVE_;
			}
			catch (...) {
				//...
			}
		}
	}

	LEAVE_:
	return channelNames;
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

			SAFE_RELEASE(fxprop)

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

	}
	catch (...) {
		TraceF(L"APO: Deinitialize failed");
	}
}