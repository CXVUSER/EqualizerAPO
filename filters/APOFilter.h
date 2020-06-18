/**Kirill
* 24 April 2019
* APOFilter
* Class for chaining APO lib's
*/
#pragma once

#include "IFilter.h"

#include <Unknwn.h>
#include <audioenginebaseapo.h>
#include <BaseAudioProcessingObject.h>
#include <audioclient.h>
#include <propvarutil.h>
#include <memory>
#include "FilterEngine.h"
#include "..//helpers/RegistryHelper.h"

#define _IPROP_FX_INTERNAL

#ifdef _IPROP_FX_INTERNAL
#include "IPropStore.h"
#endif 

//KS_NODETYPE				{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},0

// WIN 7 or VISTA
//GUID LFX; // Pre-Mix		{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},1
//GUID GFX; // Post-Mix		{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},2
//UI						{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},3
//Reserved					{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},4

// WIN 8 and 10
//GUID SFX; // Stream FX	{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},5
//GUID MFX; // Mode FX		{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},6
//GUID EFX; // Endpoint FX	{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},7

//Composite fx for Windows 10 only
// mode MFX   {D04E05A6-594B-4fb6-A80D-01AF5EED7D1D},14
// stream SFX {D04E05A6-594B-4fb6-A80D-01AF5EED7D1D},13
// end EFX	  {D04E05A6-594B-4fb6-A80D-01AF5EED7D1D},15

MIDL_INTERFACE("A4566D7A-C8F5-4150-0B7B-4EE7E744FC5C") //IMMEndpointInternal
IMMEndpointInternal : public IUnknown
{
public:
	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsEnabled() = 0;
	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInternalState() = 0;
	virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TryOpenFXPropertyStore(
		/* [annotation][in] */
		_In_  unsigned long wtf,
		/* [annotation][out] */
		_Out_  IPropertyStore** IPropertyStore) = 0;

};

const IID IID_IMMEndpointInternal = __uuidof(IMMEndpointInternal); //Windows 10 1809
const IID IID_IMMEndpointInternal2 = { 0xED899CBB,0x5613,0x4541,{0xA7,0x8F,0x66,0x30,0x2F,0x0C,0xE2,0x11} }; //Windows 7
const IID IID_IMMEndpointInternal3 = { 0xC537EE8D,0x5574,0x454A,{0x93,0x54,0xAA,0xA4,0xE4,0x21,0xD3,0x1E} }; //Windows 10 1909 1903


#pragma AVRT_VTABLES_BEGIN
class APOFilter : public IFilter
{
public:
	APOFilter(GUID efguid,FilterEngine* e);
	~APOFilter();

	bool getInPlace() override { return false; }
	std::vector<std::wstring> initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames) override;
	void process(float** output, float** input, unsigned frameCount) override;
	
private:
	__declspec(noinline) bool FillAPOInitSystemEffectsStructure(IMMDevice* aDev,
		GUID clsid,
		GUID AudioProcessingMode,
		bool InitializeForDiscoveryOnly,
		APOInitSystemEffects2* initstruct);
	
	//__declspec(noinline) HRESULT IsAudioFormatSupportedRemote(int audiopolicy, WAVEFORMATEX* input, WAVEFORMATEX* output,WAVEFORMATEX** fsupported);

	GUID _effectguid = GUID_NULL;
	FilterEngine* _eapo = 0;
	size_t channelCount = 0;

	bool bypass = true;
	bool reportCrash = true;

	IAudioProcessingObject* APO = 0;
	IAudioProcessingObjectRT* APORT = 0;
	IAudioProcessingObjectConfiguration* APOCfg = 0;
	APO_CONNECTION_PROPERTY pIn_ = { 0 };
	APO_CONNECTION_PROPERTY* pIn = &pIn_;
	APO_CONNECTION_PROPERTY pOut_ = { 0 };
	APO_CONNECTION_PROPERTY* pOut = &pOut_;
	APO_CONNECTION_DESCRIPTOR coDeskIn_;
	APO_CONNECTION_DESCRIPTOR* coDeskIn = &coDeskIn_;
	APO_CONNECTION_DESCRIPTOR coDeskOut_;
	APO_CONNECTION_DESCRIPTOR* coDeskOut = &coDeskOut_;
	APOInitSystemEffects2 initstruct = { 0 };
	IAudioMediaType* iAudType = 0;
	IMMDeviceEnumerator* pEnumerator = 0;
	IMMDeviceCollection* pCollection = 0;
	IMMDevice* pEndpoint = 0;
	IPropertyStore* pProps = 0;

#ifdef _IPROP_FX_INTERNAL
	IPropertyStoreFX* fxprop = 0;
#else
	IPropertyStore* fxprop = 0;
#endif

	APO_REG_PROPERTIES* APOInfo = 0;
	IAudioClient* iAudClient = 0;
	WAVEFORMATEX* scardformat = 0;

	//AudioSamples buffer
	float* bufferinput = 0;
	float* bufferoutput = 0;

};
#pragma AVRT_VTABLES_END
