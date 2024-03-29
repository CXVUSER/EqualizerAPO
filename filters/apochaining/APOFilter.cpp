﻿#include "stdafx.h"
#include "APOFilter.h"

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

APOProxyFilter::APOProxyFilter(GUID efguid, FilterEngine* e)
	:m_Eguid(efguid), m_Eapo(e) {}

std::vector<std::wstring> APOProxyFilter::initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames)
{
	m_ch_cnt = channelNames.size();
	HRESULT hr = 0;
	EDataFlow devicetype = eRender;
	WAVEFORMATEX* sf{};

	if (m_ch_cnt == 0)
		return channelNames;

	if (m_Eguid == GUID_NULL)
		return channelNames;

	if (m_Eapo->getDeviceGuid() == L"") {
		TraceF(L"APOProxy: Device guid not specified");
		return channelNames;
	}

	//calc buffer size
	//int frameCount = sampleRate / 100;

	size_t buffersize = ((maxFrameCount * m_ch_cnt) * sizeof(float)) << 1;

	m_bIn = (float*)MemoryHelper::alloc(buffersize);
	m_bOut = (float*)((char*)m_bIn + (buffersize >> 1));

	memset(m_bIn, 0, buffersize);

	CoCreateInstance(CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, IID_IMMDeviceEnumerator,
		(void**)&m_pEnumerator);

	IMMDevice* imd = 0;
	IMMEndpoint* ime = 0;
	std::wstring fulldevice = L"{0.0.0.00000000}.";

	fulldevice += m_Eapo->getDeviceGuid();

	m_pEnumerator->GetDevice(fulldevice.c_str(), &imd);

	imd->QueryInterface(__uuidof(IMMEndpoint), (void**)&ime);
	ime->GetDataFlow(&devicetype);
	ime->Release();
	imd->Release();

	m_pEnumerator->EnumAudioEndpoints(devicetype, DEVICE_STATE_ACTIVE, &m_pCollection);
	m_pEnumerator->GetDefaultAudioEndpoint(devicetype, eMultimedia, &m_pEndpoint);

	m_pEndpoint->Activate(__uuidof(IAudioClient), CLSCTX_ALL, 0, (void**)&m_iAudClient);

	hr = m_iAudClient->GetMixFormat(&sf);

	//Initialize APO
	try
	{
		CoCreateInstance(m_Eguid, NULL, CLSCTX_INPROC_SERVER, __uuidof(IAudioProcessingObject), (void**)&m_IAudObj);

		if (!m_IAudObj)
			return channelNames;

		m_IAudObj->QueryInterface(__uuidof(IAudioProcessingObjectRT), (void**)&m_IAudRT);
		m_IAudObj->QueryInterface(__uuidof(IAudioProcessingObjectConfiguration), (void**)&m_IAudConf);

		if (!m_IAudRT)
			return channelNames;

		if (!m_IAudConf)
			return channelNames;

		memset(&m_initstruct, 0, sizeof(APOInitSystemEffects2));

		m_pEndpoint->OpenPropertyStore(STGM_READ, &m_pProps);

		if (!m_pProps)
			return channelNames;

		try
		{
			void* hlp = reinterpret_cast<IPropertyStoreFX*>(MemoryHelper::alloc(sizeof(IPropertyStoreFX)));
			if (hlp != 0) {
				m_IFXProp = new(hlp) IPropertyStoreFX(m_Eapo->getDeviceGuid(), KEY_READ);
				if (!m_IFXProp->TryOpenPropertyStoreRegKey())
					TraceF(L"APOProxy: This audio device Guid: %s Name: %s does not contain FxProperties section in registry",
						m_Eapo->getDeviceGuid().data(),
						m_Eapo->getDeviceName().data());
			}
			else {
				return channelNames;
			}
		}
		catch (...)
		{
			return channelNames;
		}

		m_initstruct.APOInit.cbSize = sizeof(APOInitSystemEffects);
		m_initstruct.APOInit.clsid = m_Eguid;

		//IPropertyStore
		m_initstruct.pAPOEndpointProperties = m_pProps;
		m_initstruct.pAPOSystemEffectsProperties = (IPropertyStore*)m_IFXProp;

		//IMMDeviceCollection
		m_initstruct.pDeviceCollection = m_pCollection;

		/* only for APOInitSystemEffects2 structure
		initstruct.nSoftwareIoDeviceInCollection = 0;
		initstruct.nSoftwareIoConnectorIndex = 0;
		initstruct.AudioProcessingMode = AudioProcessingMode;
		initstruct.InitializeForDiscoveryOnly = InitializeForDiscoveryOnly;
		*/

		m_IAudObj->Initialize(sizeof(APOInitSystemEffects), (BYTE*)&m_initstruct);

		if (SUCCEEDED(m_IAudObj->GetRegistrationProperties(&m_aProp)))
		{
			TraceF(L"APOProxy: Successfully initialized Name: %s "
				"Copyright: %s Max Input cconnections %d "
				" Max Output connections %d "
				" APO interfaces count %d ",
				m_aProp->szFriendlyName,
				m_aProp->szCopyrightInfo,
				m_aProp->u32MaxInputConnections,
				m_aProp->u32MaxOutputConnections,
				m_aProp->u32NumAPOInterfaces);
		}
	}
	catch (...) {
		return channelNames;
	}

	WAVEFORMATEX w = {};
	w.nChannels = (WORD)m_ch_cnt;
	w.nSamplesPerSec = (DWORD)sampleRate;

	w.wFormatTag = (w.wBitsPerSample = sf ? sf->wBitsPerSample : 32) < 32 ?
		WAVE_FORMAT_PCM :
		WAVE_FORMAT_IEEE_FLOAT;

	w.nAvgBytesPerSec = w.nSamplesPerSec * (w.nBlockAlign = (w.wBitsPerSample * w.nChannels) / 8);

	CreateAudioMediaType(&w, sizeof(WAVEFORMATEX), &m_iAudType);

	if (!m_iAudType)
		return channelNames;

	m_cp_in.u32BufferFlags = BUFFER_VALID;
	m_cp_in.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
	m_cp_in.pBuffer = (UINT_PTR)m_bIn;

	m_cp_out.u32BufferFlags = BUFFER_INVALID;
	m_cp_out.u32Signature = APO_CONNECTION_PROPERTY_SIGNATURE;
	m_cp_out.pBuffer = (UINT_PTR)m_bOut;

	m_cd_in.Type = APO_CONNECTION_BUFFER_TYPE_ALLOCATED;
	m_cd_in.u32Signature = APO_CONNECTION_DESCRIPTOR_SIGNATURE;
	m_cd_in.u32MaxFrameCount = maxFrameCount;
	m_cd_in.pFormat = m_iAudType;
	m_cd_in.pBuffer = (UINT_PTR)m_bIn;

	m_cd_out.Type = APO_CONNECTION_BUFFER_TYPE_EXTERNAL;
	m_cd_out.u32Signature = APO_CONNECTION_DESCRIPTOR_SIGNATURE;
	m_cd_out.u32MaxFrameCount = maxFrameCount;
	m_cd_out.pFormat = m_iAudType;
	m_cd_out.pBuffer = (UINT_PTR)m_bOut;
	
	try
	{
		//put settings to apo
		m_IAudConf->LockForProcess(1, &m_cd_in_p, 1, &m_cd_out_p);
		CM_RELEASE(sf)
			bypass = false;
	}
	catch (...) {
		return channelNames;
	}

	return channelNames;
}

#pragma AVRT_CODE_BEGIN
void APOProxyFilter::process(float** output, float** input, unsigned frameCount)
{
	if (bypass)
	{
		for (unsigned i = 0; i < m_ch_cnt; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		return;
	}

	__try
	{
		//write
		for (size_t c = 0; c < m_ch_cnt; c++)
			for (unsigned fc = 0; fc < frameCount; fc++)
				((float*)(m_bIn + c))[fc * m_ch_cnt] = input[c][fc];

		//pInput
		m_cp_in.u32ValidFrameCount = frameCount;

		//pOutput
		m_cp_out.u32BufferFlags = BUFFER_INVALID;
		m_cp_out.u32ValidFrameCount = frameCount;

		//chilling buffer
		m_IAudRT->APOProcess(1, &m_cp_in_p, 1, &m_cp_out_p); //Process

		//Read
		for (size_t c = 0; c < m_ch_cnt; c++)
			for (size_t fc = 0; fc < frameCount; fc++)
				output[c][fc] = ((float*)(m_bOut + c))[fc * m_ch_cnt];
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		if (reportCrash)
		{
			TraceF(L"The APO plugin crashed during audio processing.");
			reportCrash = false;
		}

		for (unsigned i = 0; i < m_ch_cnt; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		bypass = true;
	}
}
#pragma AVRT_CODE_END

APOProxyFilter::~APOProxyFilter()
{
	try {
		MH_RELEASE(m_bIn)

			SAFE_RELEASE(m_iAudType)
			SAFE_RELEASE(m_iAudClient)

			CM_RELEASE(m_aProp)

			SAFE_RELEASE(m_pEnumerator)
			SAFE_RELEASE(m_pCollection)
			SAFE_RELEASE(m_pEndpoint)
			SAFE_RELEASE(m_pProps)

			SAFE_RELEASE(m_IFXProp)

			if (bypass == false)
			{
				if (m_IAudConf != 0)
					m_IAudConf->UnlockForProcess();

				if (m_IAudObj != 0)
					m_IAudObj->Reset();
			}

		SAFE_RELEASE(m_IAudConf)
			SAFE_RELEASE(m_IAudRT)
			SAFE_RELEASE(m_IAudObj)
	}
	catch (...) {
		TraceF(L"APOProxy: Deinitialize failed");
	}
}