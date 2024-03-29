﻿/***
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
 *	 VST3 pkugin wrapper
 */

#pragma once

#include <wincrypt.h>
#include "IFilter.h"
#include "FilterEngine.h"
#include "helpers/RegistryHelper.h"
#include "helpers/LogHelper.h"

//VST3_SDK
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstprocesscontext.h"
#include "pluginterfaces/vst/ivstunits.h"
#include "public.sdk/source/vst/hosting/connectionproxy.h"
#include "pluginterfaces/vst/vsttypes.h"

#include "VST3PluginSettings.h"

using namespace std;
using namespace Steinberg;
using namespace Steinberg::Vst;

#pragma AVRT_VTABLES_BEGIN
class VST3PluginFilter : public IFilter
{
public:

	VST3PluginFilter(FilterEngine* e, std::wstring path, std::wstring settings);
	~VST3PluginFilter();

	bool getInPlace() override { return false; }
	std::vector<std::wstring> initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames) override;
	void process(float** output, float** input, unsigned frameCount) override;
	bool AudioEffectClassInit(PClassInfo cl);
	void resetPlugin();
private:

	FilterEngine* m_Eapo = {};
	std::wstring m_Path;
	std::wstring m_Settings;
	size_t m_ChannelCount = {};

	IComponent* m_IComponent;
	IAudioProcessor* m_IAudprocessor;
	IPluginFactory* m_Ifact;
	IEditController* m_IEcontroller;

	//Audio bus
	AudioBusBuffers m_In = {};
	AudioBusBuffers m_Out = {};

	//Conenction
	Steinberg::Vst::IConnectionPoint* m_Icn_comp;
	Steinberg::Vst::IConnectionPoint* m_Icn_contr;

	ProcessData m_Pcd = {};

	Steinberg::Vst::ProcessContext m_p_ctx = {};

	HMODULE m_Plugindll;

	bool bypass = true;
	bool reportCrash = true;
};
#pragma AVRT_VTABLES_END
