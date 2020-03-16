/**Kirill
* 24 April 2019
* APOFilter
*/

#include "stdafx.h"
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "APOFilter.h"
#include <mmdeviceapi.h>

using namespace std;

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

#define SAFE_MEM_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { delete punk; (punk) = NULL; }

#define MH_RELEASE(mem)  \
			  if ((mem) != NULL)  \
				{ MemoryHelper::free(mem); }

#define CM_RELEASE(mem)  \
			  if ((mem) != NULL)  \
				{ CoTaskMemFree(mem); }

APOFilter::APOFilter(GUID efguid,FilterEngine* e)
	:_effectguid(efguid),_eapo(e) {}

bool APOFilter::FillAPOInitSystemEffectsStructure(IMMDevice* aDev, GUID clsid, GUID AudioProcessingMode,bool InitializeForDiscoveryOnly,int __MIDL___MIDL_itf_audioengineendpoint_0000_0000_0001, APOInitSystemEffects2* initstruct)
{
	(int) (__MIDL___MIDL_itf_audioengineendpoint_0000_0000_0001);

	HRESULT hr = 0;
	int fault = 0;

#ifndef _IPROP_FX_INTERNAL
	IMMEndpointInternal* pInternal = NULL;
#endif

	if (initstruct != 0)
	{
		if (clsid != GUID_NULL)
		{
			memset(initstruct, 0, sizeof(APOInitSystemEffects2));

			hr = aDev->OpenPropertyStore(
				STGM_READ, & pProps);

#ifndef _IPROP_FX_INTERNAL

			if (!FAILED(hr))
			{
				hr = aDev->QueryInterface(IID_IMMEndpointInternal,reinterpret_cast<void**> (& pInternal)); //Windows 10 October 2018 update
				if (FAILED(hr))
				{
					hr = aDev->QueryInterface(IID_IMMEndpointInternal2,reinterpret_cast<void**> (& pInternal)); //Windows 7
					if (FAILED(hr))
					{
						hr = aDev->QueryInterface(IID_IMMEndpointInternal3, reinterpret_cast<void**> (& pInternal)); //Windows 10 may 2019 update
					}
				}

				if (pInternal == NULL)
					return true;
#endif
				if (!FAILED(hr))
				{
					//Get apo settings

#ifdef _IPROP_FX_INTERNAL

					try
					{
						void* hlp = reinterpret_cast<IPropertyStoreFX*>(MemoryHelper::alloc(sizeof(IPropertyStoreFX)));
						if (hlp != 0) {
							fxprop = new(hlp) IPropertyStoreFX((this->_eapo)->getDeviceGuid(), KEY_READ);
							if (fxprop->TryOpenPropertyStoreRegKey(0) != S_OK)
								fault = 1;
						}
					}
					catch (...)
					{
						fault = 1;
						TraceF(L"fxprop->TryOpenPropertyStoreRegKey(); failed!");
					}
#else
					try
					{
						hr = (this->pInternal)->TryOpenFXPropertyStore(false, & (this->fxprop));
						if (FAILED(hr)) { TraceF(L"pInternal->TryOpenFXPropertyStore failed! <0x%08llx>", hr); return true; }
					}
					catch (...)
					{
						fault = 1;
						TraceF(L"pInternal->TryOpenFXPropertyStore crashed")
					}
#endif
					initstruct->APOInit.cbSize = sizeof(APOInitSystemEffects);
					initstruct->APOInit.clsid = clsid;

					//IPropertyStore object ! 
					initstruct->pAPOEndpointProperties = pProps;

					if (fault == 1)
					{
						initstruct->pAPOSystemEffectsProperties = pProps;
					}
					else
					{
						initstruct->pAPOSystemEffectsProperties = reinterpret_cast<IPropertyStore*>(fxprop);
					}
					
					initstruct->pReserved = 0;

					//IMMDeviceCollection object !
					initstruct->pDeviceCollection = pCollection;

					// only for APOInitSystemEffects2 structure
					initstruct->nSoftwareIoDeviceInCollection = 0;
					initstruct->nSoftwareIoConnectorIndex = 0;
					initstruct->AudioProcessingMode = AudioProcessingMode;
					initstruct->InitializeForDiscoveryOnly = InitializeForDiscoveryOnly;
					
					
#ifndef _IPROP_FX_INTERNAL
				}
				else {
					TraceF(L"IMMEndpointInternal class not found!"); return true;
				}
				SAFE_RELEASE(pInternal);
#endif
				return false;
				}
			else {
				TraceF(L"aDev->OpenPropertyStore failed!!!");
			}
		}
	}

	return true;
}

HRESULT APOFilter::IsAudioFormatSupportedRemote(int audiopolicy, WAVEFORMATEX* oppositeformat, WAVEFORMATEX* requestedformat,WAVEFORMATEX** fsupported)
{
	IAudioMediaType* oppf = 0;
	IAudioMediaType* reqf = 0;
	IAudioMediaType* oppositef = 0;
	HRESULT hr = 0;

	if (oppositeformat)
		hr = CreateAudioMediaType(oppositeformat, sizeof(WAVEFORMATEX), &oppf);

	if (!FAILED(hr))
	{
		if (requestedformat)
			hr = CreateAudioMediaType(requestedformat, sizeof(WAVEFORMATEX), &reqf);
		if (!FAILED(hr))
		{
			if (audiopolicy)
			{
				hr = APO->IsInputFormatSupported(oppf, reqf, &oppositef);
			}
			else {
				hr = APO->IsOutputFormatSupported(oppf, reqf, &oppositef);
			}

			const WAVEFORMATEX* crf = oppositef->GetAudioFormat();

			if (!crf)
				hr = 0x88890008; //error bad audio format

			WAVEFORMATEX* fsp = reinterpret_cast<WAVEFORMATEX*> (CoTaskMemAlloc(sizeof(WAVEFORMATEX)));

			if (fsp)
			{
				memcpy(fsupported, crf, sizeof(WAVEFORMATEX));
				*fsupported = fsp;
			}
			else hr = 0x8007000E; //error 
		}
	}

	CoTaskMemFree(0);

	SAFE_RELEASE(oppf);
	SAFE_RELEASE(reqf);
	SAFE_RELEASE(oppositef);

	return hr;
}

/*
namespace Private_ {

	class prv_
	{
	public:
		
		std::shared_ptr<prv_> asd() {
			
			return prev;
		}

		static prv_ GetFace() {

			static Private_::prv_ Object;
			return Object;
		}

		void x() {

			vector<APOFilter*> x;
			vector<APOFilter*>& instance = x;

			std::vector<std::wstring> channels;

			std::wstring channelLeft = L"Left";
			std::wstring channelRight = L"Right";

			channels.push_back(channelLeft);
			channels.push_back(channelRight);

			CLSID guid;

			if (!FAILED(CLSIDFromString(L"{F87BDE87-3199-4377-B670-ED5B1B0EEC7F}", &guid)));
			{
				APOFilter* filt = new APOFilter(guid, 0);
				x.push_back(filt);

				for (vector<APOFilter*>::iterator it = instance.begin(); it != instance.end(); it++)
				{
					APOFilter* str = *it;

					//int Frames = (48000 * 24) * channels.size(); bitrate


					str->initialize(48000, Frames, channels);
					str->process(0, 0, 0);
				}
			}

			for (size_t i = 0; i < 5; i++)
			{
				x[i]->~APOFilter();
			}
		}

	private:

	};
}
*/

std::vector<std::wstring> APOFilter::initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames)
{

#define LEAVE_(b)  \
		 bypass = b; return channelNames;

	HRESULT hr = 0;
	EDataFlow devicetype = eRender;
	
	channelCount = channelNames.size();

	if (channelCount == 0) { LEAVE_(true) }

	size_t buffersize = (maxFrameCount * channelCount) * sizeof(float);

	bufferinput = reinterpret_cast<float*> (MemoryHelper::alloc(buffersize));
	memset(bufferinput, 0, buffersize);

	bufferoutput = reinterpret_cast<float*> (MemoryHelper::alloc(buffersize));
	memset(bufferinput, 0, buffersize);

	if (_effectguid == GUID_NULL) { LEAVE_(true) }
	
	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		reinterpret_cast<void**>(& pEnumerator));
	if (FAILED(hr))
	{
		TraceF(L"MMDeviceEnumerator CoCreateInstance failed!!!"); LEAVE_(true)
	} 

	IMMDevice* imd;
	IMMEndpoint* ime;
	std::wstring fulldevice = L"{0.0.0.00000000}.";
	fulldevice += _eapo->getDeviceGuid();
	hr = (this->pEnumerator)->GetDevice(fulldevice.c_str(), &imd);
	if (!FAILED(hr))
	{
		imd->QueryInterface(__uuidof(IMMEndpoint),reinterpret_cast<void**> (& ime));
		ime->GetDataFlow(&devicetype);
		ime->Release();
		imd->Release();
	}

	hr = (this->pEnumerator)->EnumAudioEndpoints(
		devicetype, DEVICE_STATE_ACTIVE,
		& (this->pCollection));
	if (FAILED(hr))
	{
		TraceF(L"Enum Audio Endpoints failed!!!"); 
		LEAVE_(true)
	}
	
	hr = (this->pEnumerator)->GetDefaultAudioEndpoint(devicetype, eMultimedia, & pEndpoint);
	if (FAILED(hr))
	{
		TraceF(L"Get GetDefaultAudioEndpout Failed");
		LEAVE_(true)
	}

	if (!FillAPOInitSystemEffectsStructure(pEndpoint, _effectguid,__uuidof(0),0,0, & initstruct))
	{

		hr = (this->pEndpoint)->Activate(__uuidof(IAudioClient), CLSCTX_ALL, 0,reinterpret_cast<void**> (& iAudClient));
		if (FAILED(hr))
		{
			TraceF(L"pEndpoint->Activate failed!");
			LEAVE_(true)
		}

		hr = (this->iAudClient)->GetMixFormat(&scardformat);
		if (FAILED(hr))
		{
			TraceF(L"iAudClient->GetMixFormat failed!");
			LEAVE_(true)
		}

		try
		{
			hr = CoCreateInstance(_effectguid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IAudioProcessingObject),reinterpret_cast<void**> (&APO));
			if (FAILED(hr))
			{
				TraceF(L"Error in CoCreateInstance for child apo");
				LEAVE_(true)
			}
			else {

				hr = (this->APO)->QueryInterface(__uuidof(IAudioProcessingObjectRT),reinterpret_cast<void**> (&APORT));
				if (FAILED(hr))
				{
					TraceF(L"Error in QueryInterface for child apo RT");
					LEAVE_(true)
				}

					hr = (this->APO)->QueryInterface(__uuidof(IAudioProcessingObjectConfiguration),reinterpret_cast<void**> (&APOCfg));
					if (FAILED(hr))
					{
						TraceF(L"Error in QueryInterface for child apo configuration");
						LEAVE_(true)
					}

						hr = (this->APO)->Initialize(sizeof(APOInitSystemEffects),reinterpret_cast<BYTE*> (&initstruct));
						if (FAILED(hr))
						{
							TraceF(L"Error initialize APO");
							LEAVE_(true)
						}

							hr = (this->APO)->GetRegistrationProperties(& APOInfo);
							if (FAILED(hr))
							{
								TraceF(L"APO %s GetRegistrationProperties failed!", APOInfo->szFriendlyName);
								LEAVE_(true)
							}

								TraceF(L"APO %s GetRegistrationProperties succ! "
									" %s Max Input channels %d "
									" Max Output channels %d "
									" APO interfaces count %d ", APOInfo->szFriendlyName,
									APOInfo->szCopyrightInfo,
									APOInfo->u32MaxInputConnections,
									APOInfo->u32MaxOutputConnections,
									APOInfo->u32NumAPOInterfaces);

				TraceF(L"Successfully created APO");
			}
		}
		catch (...)
		{
			LEAVE_(true)
		}

		//setting buffer
		pIn_.u32BufferFlags = BUFFER_VALID;
		pIn_.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
		pIn_.pBuffer = reinterpret_cast<UINT_PTR>(bufferinput);

		pOut_.u32BufferFlags = BUFFER_INVALID;
		pOut_.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
		pOut_.pBuffer = reinterpret_cast<UINT_PTR>(bufferoutput);

		WORD bits = scardformat->wBitsPerSample;

		WAVEFORMATEX w;
		w.nChannels = static_cast<WORD>(channelCount);
		w.nSamplesPerSec = static_cast<DWORD>(sampleRate);
		w.wBitsPerSample = bits;
		w.nBlockAlign = (w.wBitsPerSample * w.nChannels) / 8;
		w.nAvgBytesPerSec = w.nSamplesPerSec * w.nBlockAlign;

		if (bits < 32) {
			w.wFormatTag = WAVE_FORMAT_PCM;
		}
		else { w.wFormatTag = WAVE_FORMAT_IEEE_FLOAT; }

		w.cbSize = 0;

		hr = CreateAudioMediaType(&w, sizeof(WAVEFORMATEX),& iAudType);
		if (FAILED(hr))
		{
			TraceF(L"CreateAudioMediaType Error");
			LEAVE_(true)
		}

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
			hr = (this->APOCfg)->LockForProcess(1, &coDeskIn, 1, &coDeskOut);
		}
		catch (...)
		{
			LEAVE_(true)
		}
		
		if (FAILED(hr))
		{
			TraceF(L"APOCfg->LockForProcess error code <0x%08llx>", hr);
		}

		LEAVE_(false)
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
			float* sampleChannel = input[c];
			float* o2 = bufferinput + c;
			for (unsigned i = 0; i < frameCount; i++)
			{
				o2[i * channelCount] = sampleChannel[i];
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
			float* sampleChannel = output[c];
			float* i2 = bufferoutput + c;
			for (size_t i = 0; i < frameCount; i++)
			{
				sampleChannel[i] = i2[i	* channelCount];
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
		MH_RELEASE((bufferinput))
			MH_RELEASE((bufferoutput))

			SAFE_RELEASE((iAudType))
			SAFE_RELEASE((iAudClient))

			CM_RELEASE((APOInfo))
			CM_RELEASE((scardformat))

			SAFE_RELEASE((pEnumerator))
			SAFE_RELEASE((pCollection))
			SAFE_RELEASE((pEndpoint))
			SAFE_RELEASE((pProps))
			
#ifndef _IPROP_FX_INTERNAL
			SAFE_RELEASE((fxprop))
#endif

			if ((bypass) == false)
			{
				if ((APOCfg) != 0)
					(APOCfg)->UnlockForProcess();

				if ((APO) != 0)
					(APO)->Reset();
			}

		SAFE_RELEASE((APOCfg))
			SAFE_RELEASE((APORT))
			SAFE_RELEASE((APO))

#ifdef _IPROP_FX_INTERNAL
			MH_RELEASE((fxprop))
#endif // !_IPROP_FX_INTERNAL
	}
	catch (...) {
		TraceF(L"APO Deinitialize failed");
		}
}