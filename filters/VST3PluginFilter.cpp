//Kirill 
// 15 fev 2020
// VST3 pkugin wrapper

#include "stdafx.h"
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "VST3PluginFilter.h"


using namespace std;

VST3PluginFilter::VST3PluginFilter(FilterEngine* e,std::wstring path, std::wstring settings)
:	_eapo(e),_path(path),_settings(settings) {
}

std::vector<std::wstring> VST3PluginFilter::initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames)
{

#define LEAVE_(b)  \
		 bypass = b; return channelNames;

	InitModuleFunc _InitDll = nullptr;
	GetPluginFactory _GetPluginFactory = nullptr;

	channelCount = channelNames.size();

	if (channelCount == 0) { LEAVE_(true) }

	if (_path != L"") {
		Plugindll = LoadLibraryW(_path.data());
		if (!Plugindll) {
			LEAVE_(true)
		}

		//get global functions
		_InitDll = reinterpret_cast<InitModuleFunc>(GetProcAddress(Plugindll, "InitDll"));
		_GetPluginFactory = reinterpret_cast<GetPluginFactory>(GetProcAddress(Plugindll, "GetPluginFactory"));

		//Initialize Plugin

		if (_InitDll && _GetPluginFactory && _InitDll() != 0) {
			if (fact = _GetPluginFactory())
			{
				/*
				IPluginFactory3* fd;

				if (fact->queryInterface(IPluginFactory3::iid, (void**)& fd) == kResultOk)
				{
					fd->setHostContext(host);
				}
				*/
				int classes = fact->countClasses();

				for (size_t i = 0; i < classes; i++)
				{
					PClassInfo cl;
					fact->getClassInfo(i, &cl);

					std::string classname = VST3::StringConvert::convert(cl.category, PClassInfo::kCategorySize);

					if (classname == kVstAudioEffectClass)
					{
						fact->createInstance(cl.cid, IComponent::iid, reinterpret_cast<void**> (&component));

						if (component)
						{
							component->initialize(host);
							/*
							if (component->queryInterface(IEditController::iid, reinterpret_cast<void**> (&controller)) != 0)
							{
								TUID controlID;

								component->getControllerClassId(controlID);
								fact->createInstance(controlID, IEditController::iid, reinterpret_cast<void**> (&controller));

								if (controller)
								{
									controller->initialize(host);
								}
							}

							component->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cm));
							controller->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cnt));

							cm->connect(cnt);
							cnt->connect(cm);
							*/
						}
						break;
					}
				}
			}
			component->queryInterface(IAudioProcessor::iid, reinterpret_cast<void**> (&processor));
			
			if (processor)
			{
				int buscountinp = component->getBusCount(kAudio, kInput);
				int buscountout = component->getBusCount(kAudio, kOutput);

				//cont = {};
				cont.tempo = 120; //BPM def temp
				cont.sampleRate = sampleRate; //samplerate in hZ (44100 48000 96000 192000 etc...)
				cont.state = ProcessContext::StatesAndFlags::kPlaying;
				
				//das = {};
				das.processContext = &cont;
				das.numInputs = buscountinp;
				das.numOutputs = buscountout;
				//das.numSamples = 0;
				das.processMode = kRealtime;
				das.symbolicSampleSize = kSample32;

				//das.inputParameterChanges = paramch;
				/*
				int pcount = controller->getParameterCount();
				ParamID bypassid;

				for (size_t i = 0; i < pcount; i++)
				{
					ParameterInfo pinfo;

					controller->getParameterInfo(i, pinfo);

						switch (pinfo.flags)
						{
						case ParameterInfo::kIsBypass:
							//Get bypass parameter id
							bypassid = pinfo.id;
							break;
						default:
							break;
						}
				}

				ValueQueue* Queue = new ValueQueue(bypassid,0);
				paramch->addparam(Queue);
				*/
				//setting channels
				//input_ = {};
				input_.numChannels = channelCount;
				//input_.silenceFlags = 0;
				//output_ = {};
				output_.numChannels = channelCount;
				//output_.silenceFlags = 0;

				das.inputs = &input_;
				das.outputs = &output_;

				processor->setProcessing(false);
				component->setActive(false);

				ProcessSetup setup{ kRealtime, kSample32,(maxFrameCount * channelCount), sampleRate };

				processor->setupProcessing(setup);

				SpeakerArrangement* arr = (SpeakerArrangement*)malloc(sizeof(SpeakerArrangement) * channelCount);
				SpeakerArrangement* arrout = (SpeakerArrangement*)malloc(sizeof(SpeakerArrangement) * channelCount);

				for (size_t i = 0; i < buscountinp; i++)
				{
					switch (channelCount)
					{
					case 2:
						arr[i] = kStereo;
						arrout[i] = kStereo;
						break;
					case 4:
						arr[i] = kStereo;
						arrout[i] = k40Music;
						break;
					case 5:
						arr[i] = kStereo;
						arrout[i] = k50;
						break;
					case 6:
						arr[i] = kStereo;
						arrout[i] = k51;
						break;
					case 8:
						arr[i] = kStereo;
						arrout[i] = k71Cine;
					default:
						break;
					}
				}

				processor->setBusArrangements(arr, buscountinp, arrout, buscountout);
				component->setActive(true);
				component->setIoMode(kAdvanced);
				processor->setProcessing(true);
				
				for (size_t i = 0; i < buscountinp; i++)
				{
					component->activateBus(kAudio, kInput, i, true);
				}

				for (size_t i = 0; i < buscountout; i++)
				{
					component->activateBus(kAudio, kOutput, i, true);
				}

				if (_settings != L"")
				{
					settings set;
					int64 seek;

					DWORD bufSize = 0;
					CryptStringToBinaryW(_settings.data(), 0, CRYPT_STRING_BASE64, NULL, &bufSize, NULL, NULL);
					BYTE* buf = new BYTE[bufSize];
					if (CryptStringToBinaryW(_settings.data(), 0, CRYPT_STRING_BASE64, buf, &bufSize, NULL, NULL) == TRUE)
					{
						set.write(buf, bufSize, 0);

						try
						{
							component->setState(&set);
						} catch (...)
						{
							TraceF(L"VST3 setState plugin failed!");
						}
					}
					delete buf;
				}

				free(arr);
				free(arrout);
				
				LEAVE_(false)
			}
		}
	}
	LEAVE_(true)
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
		das.numSamples = frameCount;
		processor->process(das);
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

VST3PluginFilter::~VST3PluginFilter()
{
	//Unload plugin
	try {
		ExitDll _ExitDll = nullptr;

		//cm->disconnect(cnt);
		//cnt->disconnect(cm);

		if (processor)
			processor->setProcessing(false);
		
		if (component)
		{
			component->setActive(false);
			
			//controller->terminate();
			component->terminate();
			
			/*
			while (true)
			{
				if (!controller->release())
					break;
			}
			*/
			/*
			while (true)
			{
				if (component->release() <= 0)
					break;
			}
			*/
		}

		/*
		if (fact) {
			while (true)
			{
				if (fact->release() <= 0)
					break;
			}
		}
		*/

		if (host)
			delete host;

		//if (paramch)
		//	delete paramch;

		//if (hhand)
		//	delete hhand;

		_ExitDll = reinterpret_cast<ExitDll>(GetProcAddress(Plugindll, "ExitDll"));
		if (_ExitDll) {
			_ExitDll();
		}
			FreeLibrary(Plugindll);
	}
	catch (...) {}
}