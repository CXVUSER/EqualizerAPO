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
	: _eapo(e), _path(path), _settings(settings) {
}

bool VST3PluginFilter::InitPlugin(PClassInfo cl) {

	__try {
		if (fact->createInstance(cl.cid, FUnknown::iid, (void**)&component) == kResultTrue)
		{
			if (component == 0)

				component->initialize(0);

			if (component->queryInterface(IEditController::iid, (void**)&controller) != kResultTrue)
			{
				TUID controlID = { 0 };

				if (component->getControllerClassId(controlID) == kResultOk)
					if (fact->createInstance(controlID, IEditController::iid, (void**)&controller) == kResultTrue)
						if (controller != NULL) {
							if (component->queryInterface(Vst::IConnectionPoint::iid, (void**)&cm) == kResultTrue) {
								if (cm != NULL)
									if (controller->queryInterface(Vst::IConnectionPoint::iid, (void**)&cnt) == kResultTrue)
									{
										if (cnt != NULL)
										{
											cm->connect(cnt);
											cnt->connect(cm);
										}
									}
							}
							controller->initialize(0);
						}
			}
		}
		else {
			return false;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}

	return true;
}

void VST3PluginFilter::resetPlugin()
{
	if (controller == NULL) {
		return;
	}

	int pcount = controller->getParameterCount();

	for (size_t i = 0; i < pcount; i++)
	{
		ParameterInfo pinfo;
		int c = 0;
		controller->getParameterInfo(i, pinfo);

		if (wcscmp(pinfo.title, L"Bypass") == 0)
		{
			controller->setParamNormalized(pinfo.id, 0);
		}
	}

	IUnitInfo* unit = 0;
	if (component->queryInterface(IUnitInfo::iid, (void**)&unit) == kResultOk)
	{
		if (unit != NULL)
		{
			long uc = unit->getUnitCount();
			for (size_t i = 0; i < uc; i++)
			{
				long lc = unit->getProgramListCount();
				for (size_t i = 0; i < lc; i++)
				{
					ProgramListInfo inf = { 0 };
					unit->getProgramListInfo(i, inf);

					long lp = inf.programCount;
					for (size_t i = 0; i < lp; i++)
					{
						String128 pn;
						unit->getProgramName(inf.id, i, pn);

						if (wcscmp(pn, L"Default") == 0)
						{
							for (size_t o = 0; o < pcount; o++)
							{
								ParameterInfo pinfo = { 0 };
								controller->getParameterInfo(o, pinfo);

								if (wcscmp(pinfo.title, L"Program") == 0)
								{
									//Reset program parameter to default value
									controller->setParamNormalized(pinfo.id, i);
								}
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
	channelCount = channelNames.size();
	ProcessSetup setup{ kRealtime, kSample32,0, sampleRate };

	if (channelCount == 0 || _path == L"") {
		goto LEAVE_;
	}

	Plugindll = LoadLibraryW(_path.data());
	if (Plugindll != 0) {
		TraceF(L"VST3: Load plugin: %s", _path.data());
	}
	else {
		goto LEAVE_;
	}

	unsigned int frameCount = sampleRate / 100;

	//get global functions
	auto _InitDll = func(InitModuleFunc, Plugindll, "InitDll");
	auto _GetPluginFactory = func(GetPluginFactory, Plugindll, "GetPluginFactory");

	//Initialize Plugin
	if ((!_InitDll || !_GetPluginFactory) || _InitDll() == 0) {
		goto LEAVE_;
	}

	if ((fact = _GetPluginFactory()) == 0) {
		goto LEAVE_;
	}

	int classes = fact->countClasses();

	if (classes == 0) {
		goto LEAVE_;
	}

	for (size_t i = 0; i < classes; i++)
	{
		PClassInfo cl;
		fact->getClassInfo(i, &cl);

		if (strcmp(cl.category, kVstAudioEffectClass) == 0)
		{
			if (!InitPlugin(cl))
				goto LEAVE_;
			break;
		}
	}

	if (component->queryInterface(IAudioProcessor::iid, (void**) &processor) == kResultFalse) {
		if (processor == 0)
			goto LEAVE_;
	}

	int buscountinp = component->getBusCount(kAudio, kInput);
	int buscountout = component->getBusCount(kAudio, kOutput);

	processor->setProcessing(false);
	component->setActive(false);

	cont.tempo = 120; //BPM def temp
	cont.sampleRate = sampleRate; //samplerate in hZ (44100 48000 96000 192000 etc...)

	cont.state = ProcessContext::StatesAndFlags::kPlaying;

	pcd.processContext = &cont;
	pcd.numInputs = buscountinp;
	pcd.numOutputs = buscountout;

	pcd.processMode = kRealtime;
	pcd.symbolicSampleSize = kSample32;

	pcd.inputs = &input_;
	pcd.outputs = &output_;

	//setting channels
	SpeakerArrangement arr = _eapo->getChannelMask();
	SpeakerArrangement fake = KSAUDIO_SPEAKER_STEREO;

	if (processor->setBusArrangements(&arr, 1, 0, 0) != kResultOk)
	{
		processor->setBusArrangements(&fake, 1, 0, 0);
		input_.numChannels = 2;
	}
	else
	{
		input_.numChannels = channelCount;
	}

	if (processor->setBusArrangements(0, 0, &arr, 1) != kResultOk)
	{
		processor->setBusArrangements(0, 0, &fake, 1);
		output_.numChannels = 2;
	}
	else
	{
		output_.numChannels = channelCount;
	}

	setup.maxSamplesPerBlock = (input_.numChannels != channelCount) ? (frameCount * 2) :
		(frameCount * channelCount);

	if (processor->setupProcessing(setup) == kResultFalse) {
		goto LEAVE_;
	}

	if (component->setActive(true) == kResultFalse) {
		goto LEAVE_;
	}

	if (processor->setProcessing(true) == kResultFalse) {
		goto LEAVE_;
	}

	auto actbus = [](IComponent* component, int i,int d) {
		BusInfo inf = { 0 };
		component->getBusInfo(kAudio, d, i, inf);

		(inf.flags & BusInfo::kDefaultActive) == false ? component->activateBus(kAudio, d, i, true) :
			component->activateBus(kAudio, d, i, false);
	};

	for (size_t i = 0; i < buscountinp; i++)
		actbus(component, buscountinp, kInput);
	for (size_t i = 0; i < buscountout; i++)
		actbus(component, buscountout,kOutput);

	if (_settings.size() > 0)
	{
		settings set;
		DWORD bufSize = 0;

		CryptStringToBinaryW(_settings.data(), 0, CRYPT_STRING_BASE64, NULL, &bufSize, NULL, NULL);
		BYTE* buf = reinterpret_cast<BYTE*>(malloc(bufSize));
		if (buf) {
			if (CryptStringToBinaryW(_settings.data(), 0, CRYPT_STRING_BASE64, buf, &bufSize, NULL, NULL) == TRUE)
			{
				set.write(buf, bufSize, 0);

				try
				{
					component->setState(&set);
				}
				catch (...)
				{
					TraceF(L"VST3: setState plugin failed!");
				}
			}
			if (buf)
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
		for (unsigned i = 0; i < channelCount; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		return;
	}

	__try
	{
		output_.channelBuffers32 = output;
		input_.channelBuffers32 = input;
		pcd.numSamples = frameCount;
		processor->process(pcd);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		if (reportCrash)
		{
			TraceF(L"The VST3 plugin crashed during audio processing.");
			reportCrash = false;
		}

		for (unsigned i = 0; i < channelCount; i++)
			memcpy(output[i], input[i], frameCount * sizeof(float));
		bypass = true;
	}
}
#pragma AVRT_CODE_END

VST3PluginFilter::~VST3PluginFilter()
{
	//Unload plugin
	try {
		if (cm != 0)
		{
			if (cnt != 0)
			{
				cm->disconnect(cnt);
				cnt->disconnect(cm);
			}
		}

		if (processor != 0)
			processor->setProcessing(false);

		if (component != 0)
		{
			component->setActive(false);

			if (controller != 0)
				controller->terminate();

			component->terminate();
		}

		auto _ExitDll = func(ExitDll, Plugindll, "ExitDll");
		if (_ExitDll) {
			_ExitDll();
		}
		FreeLibrary(Plugindll);
	}
	catch (...) {}
}