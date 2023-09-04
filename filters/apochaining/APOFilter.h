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
 *	 Class for chaining APO lib's
 */

#pragma once

#include "IFilter.h"
#include "FilterEngine.h"
#include "helpers/LogHelper.h"
#include "IPropStore.h"

//KS_NODETYPE				{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},0

// WIN 7 or VISTA
//GUID LFX; // Pre-Mix		{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},1
//GUID GFX; // Post-Mix		{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},2
//UI						{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},3
//Reserved					{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},4

// WIN 8 and 10/11
//GUID SFX; // Stream FX	{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},5
//GUID MFX; // Mode FX		{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},6
//GUID EFX; // Endpoint FX	{d04e05a6-594b-4fb6-a80d-01af5eed7d1d},7

//Composite fx for Windows 10/11 only
// mode MFX   {D04E05A6-594B-4fb6-A80D-01AF5EED7D1D},14
// stream SFX {D04E05A6-594B-4fb6-A80D-01AF5EED7D1D},13
// end EFX	  {D04E05A6-594B-4fb6-A80D-01AF5EED7D1D},15

#define SAFE_RELEASE(punk)  \
              if (punk != NULL)  \
                { punk->Release(); (punk) = NULL; }

#define MH_RELEASE(mem)  \
			  if (mem != NULL)  \
				{ MemoryHelper::free(mem); }

#define CM_RELEASE(mem)  \
			  if (mem != NULL)  \
				{ CoTaskMemFree(mem); }

using namespace std;

#pragma AVRT_VTABLES_BEGIN
class APOProxyFilter : public IFilter
{
public:
	APOProxyFilter(GUID efguid,FilterEngine* e);
	~APOProxyFilter();

	bool getInPlace() override { return false; }
	std::vector<std::wstring> initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames) override;
	void process(float** output, float** input, unsigned frameCount) override;
	
private:
	
	GUID m_Eguid = GUID_NULL;
	FilterEngine* m_Eapo = 0;
	size_t m_ch_cnt = 0;

	IAudioProcessingObject* m_IAudObj = 0;
	IAudioProcessingObjectRT* m_IAudRT = 0;
	IAudioProcessingObjectConfiguration* m_IAudConf = 0;

	APO_CONNECTION_PROPERTY m_cp_in = {};
	APO_CONNECTION_PROPERTY* m_cp_in_p = &m_cp_in;
	APO_CONNECTION_PROPERTY m_cp_out = {};
	APO_CONNECTION_PROPERTY* m_cp_out_p = &m_cp_out;
	APO_CONNECTION_DESCRIPTOR m_cd_in;
	APO_CONNECTION_DESCRIPTOR* m_cd_in_p = &m_cd_in;
	APO_CONNECTION_DESCRIPTOR m_cd_out;
	APO_CONNECTION_DESCRIPTOR* m_cd_out_p = &m_cd_out;

	APOInitSystemEffects2 m_initstruct = {};
	IAudioMediaType* m_iAudType = 0;
	IMMDeviceEnumerator* m_pEnumerator = 0;
	IMMDeviceCollection* m_pCollection = 0;
	IMMDevice* m_pEndpoint = 0;
	IPropertyStore* m_pProps = 0;
	IPropertyStoreFX* m_IFXProp = 0;
	APO_REG_PROPERTIES* m_aProp = 0;
	IAudioClient* m_iAudClient = 0;
	
	//AudioSamples buffer
	float* m_bIn = 0;
	float* m_bOut = 0;

	bool bypass = true;
	bool reportCrash = true;
};
#pragma AVRT_VTABLES_END
