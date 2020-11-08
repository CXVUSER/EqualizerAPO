
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
#include "IPropStore.h"

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

#define SAFE_RELEASE(punk)  \
              if (punk != NULL)  \
                { punk->Release(); (punk) = NULL; }

#define SAFE_MEM_RELEASE(punk)  \
              if (punk != NULL)  \
                { delete punk; (punk) = NULL; }

#define MH_RELEASE(mem)  \
			  if (mem != NULL)  \
				{ MemoryHelper::free(mem); }

#define CM_RELEASE(mem)  \
			  if (mem != NULL)  \
				{ CoTaskMemFree(mem); }

#define func(T,h,str)	\
		reinterpret_cast<T>(GetProcAddress(h, str))

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

	IPropertyStoreFX* fxprop = 0;

	APO_REG_PROPERTIES* APOInfo = 0;
	IAudioClient* iAudClient = 0;
	
	//AudioSamples buffer
	float* bufferinput = 0;
	float* bufferoutput = 0;

};
#pragma AVRT_VTABLES_END
