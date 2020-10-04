
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

std::vector<std::wstring> VST3PluginFilter::initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames)
{
#define LEAVE_(b)  \
		 bypass = b; return channelNames;

	InitModuleFunc _InitDll = nullptr;
	GetPluginFactory _GetPluginFactory = nullptr;
	ProcessSetup setup{ kRealtime, kSample32,0, sampleRate };

	channelCount = channelNames.size();

	if (channelCount == 0 || _path == L"") { 
		LEAVE_(true)
	}

	Plugindll = LoadLibraryW(_path.data());
	if (Plugindll != 0) {
		TraceF(L"Load VST3 plugin: %s", _path.data());
	}
	else { 
		LEAVE_(true)
	}

	//get global functions
	_InitDll = reinterpret_cast<InitModuleFunc>(GetProcAddress(Plugindll, "InitDll"));
	_GetPluginFactory = reinterpret_cast<GetPluginFactory>(GetProcAddress(Plugindll, "GetPluginFactory"));

	//Initialize Plugin

	if ((!_InitDll || !_GetPluginFactory) || _InitDll() == 0) {
		LEAVE_(true)
	}

	if ((fact = _GetPluginFactory()) == 0) {
		LEAVE_(true)
	}

	int classes = fact->countClasses();

	if (classes == 0) { 
		LEAVE_(true)
	}

	for (size_t i = 0; i < classes; i++)
	{
		PClassInfo cl;
		fact->getClassInfo(i, &cl);
		
		if (strcmp(cl.category, kVstAudioEffectClass) == 0)
		{
			try
			{
				if ((fact->createInstance(cl.cid, FUnknown::iid, reinterpret_cast<void**> (&component)) == kResultTrue) &
					component != 0)
				{
					if (component->queryInterface(IEditController::iid, reinterpret_cast<void**> (&controller)) != kResultTrue)
					{
						TUID controlID = { 0 };

						component->getControllerClassId(controlID);
						fact->createInstance(controlID, IEditController::iid, reinterpret_cast<void**> (&controller));
					}

					if (controller != NULL) {
						if ((component->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cm)) == kResultTrue) & cm != NULL) {
							if ((controller->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cnt)) == kResultTrue) & cnt != NULL)
							{
								cm->connect(cnt);
								cnt->connect(cm);
							}
						}
						controller->initialize(0);
					}
				} else { 
					LEAVE_(true)
				}
					component->initialize(0);
			}
			catch (...)
			{
				TraceF(L"VST3: initialize crashed!");
				LEAVE_(true);
			}
			break;
		}
	}

	if (component->queryInterface(IAudioProcessor::iid, reinterpret_cast<void**> (&processor)) == kResultFalse &
		processor == 0) {
		LEAVE_(true)
	}

	int buscountinp = component->getBusCount(kAudio, kInput);
	int buscountout = component->getBusCount(kAudio, kOutput);

	processor->setProcessing(false);
	component->setActive(false);

	//cont = {};
	cont.tempo = 120; //BPM def temp
	cont.sampleRate = sampleRate; //samplerate in hZ (44100 48000 96000 192000 etc...)

	cont.state = ProcessContext::StatesAndFlags::kPlaying;

	//pcd = {};
	pcd.processContext = &cont;
	pcd.numInputs = buscountinp;
	pcd.numOutputs = buscountout;

	//pcd.numSamples = 0;
	pcd.processMode = kRealtime;
	pcd.symbolicSampleSize = kSample32;

	pcd.inputs = &input_;
	pcd.outputs = &output_;

	//setting channels
	SpeakerArrangement arr[1] = {};

		switch (channelCount)
		{
		case 1:
			arr[0] = kMono;
			break;
		case 2:
			arr[0] = kStereo;
			break;
		case 4:
			arr[0] = k40Music;
			break;
		case 5:
			arr[0] = k50;
			break;
		case 6:
			arr[0] = k51;
			break;
		case 7:
			arr[0] = k70Music;
			break;
		case 8:
			arr[0] = k71Music;
			break;
		default:
			break;
		}

		if (processor->setBusArrangements(arr, 1, 0, 0) != kResultOk)
		{
			SpeakerArrangement fake[1] = {};
			fake[0] = kStereo;
			processor->setBusArrangements(fake, 1, 0, 0);
			input_.numChannels = 2;
		}
		else
		{
			input_.numChannels = channelCount;
		}

		if (processor->setBusArrangements(0, 0, arr, 1) != kResultOk)
		{
			SpeakerArrangement fake[1] = {};
			fake[0] = kStereo;
			processor->setBusArrangements(0, 0, fake, 1);
			output_.numChannels = 2;
		}
		else
		{
			output_.numChannels = channelCount;
		}

	(input_.numChannels != channelCount) ? setup.maxSamplesPerBlock = (maxFrameCount * 2) : 
		setup.maxSamplesPerBlock = (maxFrameCount * channelCount);
		
	if (processor->setupProcessing(setup) == kResultFalse) {
		LEAVE_(true)
	}

	if (component->setActive(true) == kResultFalse) {
		LEAVE_(true)
	}

	if (processor->setProcessing(true) == kResultFalse) {
		LEAVE_(true)
	}

	for (size_t i = 0; i < buscountinp; i++)
	{
		BusInfo inf = { 0 };
		component->getBusInfo(kAudio, kInput, i, inf);

		(inf.flags & BusInfo::kDefaultActive) == false ? component->activateBus(kAudio, kInput, i, true) :
			component->activateBus(kAudio, kInput, i, false);
	}

	for (size_t i = 0; i < buscountout; i++)
	{
		BusInfo inf = { 0 };
		component->getBusInfo(kAudio, kOutput, i, inf);

		(inf.flags & BusInfo::kDefaultActive) == false ? component->activateBus(kAudio, kOutput, i, true) :
			component->activateBus(kAudio, kOutput, i, false);
	}

	if (_settings.size() > 0)
	{
		settings set;
		DWORD bufSize = 0;

		CryptStringToBinaryW(_settings.data(), 0, CRYPT_STRING_BASE64, NULL, &bufSize, NULL, NULL);
		BYTE* buf = reinterpret_cast<BYTE*>(malloc(bufSize));
		if (CryptStringToBinaryW(_settings.data(), 0, CRYPT_STRING_BASE64, buf, &bufSize, NULL, NULL) == TRUE)
		{
			set.write(buf, bufSize, 0);

			try
			{
				component->setState(&set);
			}
			catch (...)
			{
				TraceF(L"VST3 setState plugin failed!");
			}
		}
		free(buf);
	}
	else
	{
		if (controller == NULL) {
			LEAVE_(false)
		}

		int pcount = controller->getParameterCount();

		for (size_t i = 0; i < pcount; i++)
		{
			ParameterInfo pinfo;
			int c = 0;
			controller->getParameterInfo(i, pinfo);

			if (wcscmp(pinfo.title,L"Bypass") == 0)
			{
				controller->setParamNormalized(pinfo.id, 0);
			}
		}

		IUnitInfo* unit = 0;
		if (component->queryInterface(IUnitInfo::iid, reinterpret_cast<void**>(&unit)) == kResultOk)
		{
			if (unit != NULL)
			{
				for (size_t i = 0; i < unit->getUnitCount(); i++)
				{
					for (size_t i = 0; i < unit->getProgramListCount(); i++)
					{
						ProgramListInfo inf = { 0 };
						unit->getProgramListInfo(i, inf);

						for (size_t i = 0; i < inf.programCount; i++)
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

	LEAVE_(false)
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
		ExitDll _ExitDll = nullptr;

		if (cm != 0 & cnt != 0)
		{
			cm->disconnect(cnt);
			cnt->disconnect(cm);
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

		_ExitDll = reinterpret_cast<ExitDll>(GetProcAddress(Plugindll, "ExitDll"));
		if (_ExitDll) {
			_ExitDll();
		}
		FreeLibrary(Plugindll);
	}
	catch (...) {}
}