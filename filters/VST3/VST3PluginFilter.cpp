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
 *	 VST3 pkugin wrapper
 *	 15 fev 2020
 */

#include "stdafx.h"
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "VST3PluginFilter.h"

using namespace std;

VST3PluginFilter::VST3PluginFilter(FilterEngine* e, std::wstring path, std::wstring settings)
	: m_Eapo(e), m_Path(path), m_Settings(settings) {
}

bool VST3PluginFilter::AudioEffectClassInit(PClassInfo cl) {

	__try {
		if (m_Ifact->createInstance(cl.cid, FUnknown::iid, (void**)&m_IComponent) == kResultFalse)
			return false;

		if (m_IComponent == nullptr)
			return false;

		if (m_IComponent->initialize(0) == kResultFalse)
			return false;

		if (m_IComponent->queryInterface(IEditController::iid, (void**)&m_IEcontroller) != kResultTrue)
		{
			TUID controlID = { 0 };

			if (m_IComponent->getControllerClassId(controlID) != kResultTrue)
				return false;

			if (m_Ifact->createInstance(controlID, IEditController::iid, (void**)&m_IEcontroller) != kResultTrue)
				return false;

			if (m_IEcontroller == NULL)
				return false;

			if (m_IComponent->queryInterface(Vst::IConnectionPoint::iid, (void**)&m_Icn_comp) == kResultTrue) {
				if (m_Icn_comp != NULL)
					if (m_IEcontroller->queryInterface(Vst::IConnectionPoint::iid, (void**)&m_Icn_contr) == kResultTrue)
						if (m_Icn_contr != NULL)
						{
							m_Icn_comp->connect(m_Icn_contr);
							m_Icn_contr->connect(m_Icn_comp);
							m_IEcontroller->initialize(0);
						}
			}
		}
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}

	return false;
}

void VST3PluginFilter::resetPlugin()
{
	if (m_IEcontroller == NULL)
		return;

	auto pcount = m_IEcontroller->getParameterCount();

	for (size_t i = 0; i < pcount; i++)
	{
		ParameterInfo pinfo;
		int c = 0;
		m_IEcontroller->getParameterInfo(i, pinfo);

		if (wcscmp(pinfo.title, L"Bypass") == 0)
			m_IEcontroller->setParamNormalized(pinfo.id, 0);
	}

	IUnitInfo* unit = 0;
	if (m_IComponent->queryInterface(IUnitInfo::iid, (void**)&unit) == kResultOk)
	{
		if (unit != NULL)
		{
			auto uc = unit->getUnitCount();
			for (size_t i = 0; i < uc; i++)
			{
				auto lc = unit->getProgramListCount();
				for (size_t i = 0; i < lc; i++)
				{
					ProgramListInfo inf = { 0 };
					unit->getProgramListInfo(i, inf);

					auto lp = inf.programCount;
					for (size_t i = 0; i < lp; i++)
					{
						String128 pn;
						unit->getProgramName(inf.id, i, pn);

						if (wcscmp(pn, L"Default") == 0)
						{
							for (size_t o = 0; o < pcount; o++)
							{
								ParameterInfo pinfo = { 0 };
								m_IEcontroller->getParameterInfo(o, pinfo);

								if (wcscmp(pinfo.title, L"Program") == 0)
									m_IEcontroller->setParamNormalized(pinfo.id, i);	//Reset program parameter to default value
							}
						}
					}
				}
			}
		}
	}
}

std::vector<std::wstring> VST3PluginFilter::initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames)
{
	m_ChannelCount = channelNames.size();
	ProcessSetup setup{ kRealtime, kSample32,0, sampleRate };

	if (m_ChannelCount == 0 || m_Path == L"")
		goto LEAVE_;

	m_Plugindll = LoadLibraryW(m_Path.data());
	if (m_Plugindll != 0) {
		TraceF(L"VST3: Load plugin: %s", m_Path.data());
	}
	else {
		goto LEAVE_;
	}

	//unsigned int frameCount = sampleRate / 100;

	//get global functions
	auto _InitDll = func(InitModuleFunc, m_Plugindll, "InitDll");
	auto _GetPluginFactory = func(GetPluginFactory, m_Plugindll, "GetPluginFactory");

	//Initialize Plugin
	if ((!_InitDll || !_GetPluginFactory) || _InitDll() == 0)
		goto LEAVE_;

	if ((m_Ifact = _GetPluginFactory()) == 0)
		goto LEAVE_;

	auto classes = m_Ifact->countClasses();

	if (classes == 0)
		goto LEAVE_;

	for (size_t i = 0; i < classes; i++)
	{
		PClassInfo cl;
		m_Ifact->getClassInfo(i, &cl);

		if (strcmp(cl.category, kVstAudioEffectClass) == 0)
		{
			if (!AudioEffectClassInit(cl))
				goto LEAVE_;
			break;
		}
	}

	if (m_IComponent->queryInterface(IAudioProcessor::iid, (void**)&m_IAudprocessor) != kResultTrue)
		goto LEAVE_;

	if (m_IAudprocessor == 0)
		goto LEAVE_;

	auto buscountinp = m_IComponent->getBusCount(kAudio, kInput);
	auto buscountout = m_IComponent->getBusCount(kAudio, kOutput);

	m_IAudprocessor->setProcessing(false);
	m_IComponent->setActive(false);

	m_p_ctx.tempo = 120; //BPM def temp
	m_p_ctx.sampleRate = sampleRate; //samplerate in hZ (44100 48000 96000 192000 etc...)

	m_p_ctx.state = ProcessContext::StatesAndFlags::kPlaying;

	m_Pcd.processContext = &m_p_ctx;
	m_Pcd.numInputs = buscountinp;
	m_Pcd.numOutputs = buscountout;

	m_Pcd.processMode = kRealtime;
	m_Pcd.symbolicSampleSize = kSample32;

	m_Pcd.inputs = &m_In;
	m_Pcd.outputs = &m_Out;

	//setting channels
	SpeakerArrangement arr = m_Eapo->getChannelMask();
	SpeakerArrangement fake = KSAUDIO_SPEAKER_STEREO;

	if (m_IAudprocessor->setBusArrangements(&arr, 1, 0, 0) != kResultOk)
	{
		m_IAudprocessor->setBusArrangements(&fake, 1, 0, 0);
		m_In.numChannels = 2;
	}
	else
	{
		m_In.numChannels = m_ChannelCount;
	}

	if (m_IAudprocessor->setBusArrangements(0, 0, &arr, 1) != kResultOk)
	{
		m_IAudprocessor->setBusArrangements(0, 0, &fake, 1);
		m_Out.numChannels = 2;
	}
	else
	{
		m_Out.numChannels = m_ChannelCount;
	}

	setup.maxSamplesPerBlock = (m_In.numChannels != m_ChannelCount) ? (maxFrameCount << 1) :
		(maxFrameCount * m_ChannelCount);

	if (m_IAudprocessor->setupProcessing(setup) == kResultFalse)
		goto LEAVE_;

	if (m_IComponent->setActive(true) == kResultFalse)
		goto LEAVE_;

	if (m_IAudprocessor->setProcessing(true) == kResultFalse)
		goto LEAVE_;

	auto actbus = [](IComponent* component, int i,int d) {
		BusInfo inf = { 0 };
		component->getBusInfo(kAudio, d, i, inf);

		(inf.flags & BusInfo::kDefaultActive) == false ? component->activateBus(kAudio, d, i, true) :
			component->activateBus(kAudio, d, i, false);
	};

	for (size_t i = 0; i < buscountinp; i++)
		actbus(m_IComponent, buscountinp, kInput);
	for (size_t i = 0; i < buscountout; i++)
		actbus(m_IComponent, buscountout,kOutput);

	if (m_Settings.size() > 0)
	{
		settings set;
		DWORD bufSize = 0;

		CryptStringToBinaryW(m_Settings.data(), 0, CRYPT_STRING_BASE64, NULL, &bufSize, NULL, NULL);
		auto buf = reinterpret_cast<BYTE*>(malloc(bufSize));
		if (buf) {
			if (CryptStringToBinaryW(m_Settings.data(), 0, CRYPT_STRING_BASE64, buf, &bufSize, NULL, NULL) == TRUE)
			{
				set.write(buf, bufSize, 0);

				try
				{
					m_IComponent->setState(&set);
				}
				catch (...)
				{
					TraceF(L"VST3: setState plugin failed!");
				}
			}
			free(buf);
		}
	}
	else
	{
		resetPlugin();
	}

	bypass = false;

LEAVE_:
	return channelNames;
}

#pragma AVRT_CODE_BEGIN
void VST3PluginFilter::process(float** output, float** input, unsigned frameCount)
{
	if (bypass)
	{
		for (unsigned i = 0; i < m_ChannelCount; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		return;
	}

	__try
	{
		m_Out.channelBuffers32 = output;
		m_In.channelBuffers32 = input;
		m_Pcd.numSamples = frameCount;
		m_IAudprocessor->process(m_Pcd);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		if (reportCrash)
		{
			TraceF(L"The VST3 plugin crashed during audio processing.");
			reportCrash = false;
		}

		for (unsigned i = 0; i < m_ChannelCount; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		bypass = true;
	}
}
#pragma AVRT_CODE_END

VST3PluginFilter::~VST3PluginFilter()
{
	//Unload plugin
	try {
		if (m_Icn_comp != 0)
		{
			if (m_Icn_contr != 0)
			{
				m_Icn_comp->disconnect(m_Icn_contr);
				m_Icn_contr->disconnect(m_Icn_comp);
			}
		}

		if (m_IAudprocessor != 0)
			m_IAudprocessor->setProcessing(false);

		if (m_IComponent != 0)
		{
			m_IComponent->setActive(false);

			if (m_IEcontroller != 0)
				m_IEcontroller->terminate();

			m_IComponent->terminate();
		}

		auto _ExitDll = func(ExitDll, m_Plugindll, "ExitDll");
		if (_ExitDll) {
			_ExitDll();
		}
		FreeLibrary(m_Plugindll);
	}
	catch (...) {}
}