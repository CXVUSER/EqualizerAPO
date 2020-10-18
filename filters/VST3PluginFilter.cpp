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
				int classes = fact->countClasses();

				for (size_t i = 0; i < classes; i++)
				{
					PClassInfo cl;
					fact->getClassInfo(i, &cl);

					std::string classname = VST3::StringConvert::convert(cl.category, PClassInfo::kCategorySize);

					if (classname == kVstAudioEffectClass)
					{
						try
						{
							fact->createInstance(cl.cid, FUnknown::iid, reinterpret_cast<void**> (&component));

							if (component)
							{
								//component->initialize(host);

								if (component->queryInterface(IEditController::iid, reinterpret_cast<void**> (&controller)) != 0)
								{
									TUID controlID;

									component->getControllerClassId(controlID);
									fact->createInstance(controlID, IEditController::iid, reinterpret_cast<void**> (&controller));

									/*
									if (controller)
									{
										controller->initialize(host);
									}
									*/
								}

								component->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cm));
								controller->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cnt));
								component->queryInterface(IAudioProcessor::iid, reinterpret_cast<void**> (&processor));
								//processor->queryInterface(Steinberg::Vst::IConnectionPoint::iid, reinterpret_cast<void**> (&cpr));

								cm->connect(cnt);
								cnt->connect(cm);
								//cpr->connect(cm);
								//cm->connect(cpr);

								component->initialize(host);

								if (controller)
								{
									controller->initialize(host);
								}
							}
						}
						catch (...)
						{
							TraceF(L"VST3: initialize crashed!");
							LEAVE_(true);
						}

						break;
					}
				}
			}
			
			if (processor)
			{
				int buscountinp = component->getBusCount(kAudio, kInput);
				int buscountout = component->getBusCount(kAudio, kOutput);

				processor->setProcessing(false);
				component->setActive(false);

				//cont = {};
				cont.tempo = 120; //BPM def temp
				cont.sampleRate = sampleRate; //samplerate in hZ (44100 48000 96000 192000 etc...)
				
				cont.state = ProcessContext::StatesAndFlags::kPlaying;
				
				cont.timeSigNumerator = 4;
				cont.timeSigDenominator = 4;

				//pcd = {};
				pcd.processContext = &cont;
				pcd.numInputs = buscountinp;
				pcd.numOutputs = buscountout;

				//pcd.numSamples = 0;
				pcd.processMode = kRealtime;
				pcd.symbolicSampleSize = kSample32;

				pcd.inputParameterChanges = paramch;
				pcd.outputParameterChanges = paramch;
				pcd.inputEvents = ivent;

				pcd.inputs = &input_;
				pcd.outputs = &output_;

				SpeakerArrangement arr[8] = {};
				
				//setting channels
				for (size_t i = 0; i < buscountinp; i++)
				{
					switch (channelCount)
					{
					case 2:
						arr[i] = kStereo;
						break;
					case 4:
						arr[i] = k40Music;
						break;
					case 5:
						arr[i] = k50;
						break;
					case 6:
						arr[i] = k51;
						break;
					case 7:
						arr[i] = k70Music;
						break;
					case 8:
						arr[i] = k71Music;
						break;
					default:
						break;
					}

					if (processor->setBusArrangements(arr, buscountinp, 0, 0) != kResultOk)
					{
						SpeakerArrangement fake[8] = {};
						fake[i] = kStereo;
						processor->setBusArrangements(fake, buscountinp, 0, 0);
						input_.numChannels = 2;
					}
					else
					{
						input_.numChannels = channelCount;
					}
					
					if (processor->setBusArrangements(0, 0, arr, buscountout) != kResultOk)
					{
						SpeakerArrangement fake[8] = {};
						fake[i] = kStereo;
						processor->setBusArrangements(0, 0, fake, buscountout);
						output_.numChannels = 2;
					}
					else
					{
						output_.numChannels = channelCount;
					}		
				}
			
				ProcessSetup setup{ kRealtime, kSample32,0, sampleRate };

				if (input_.numChannels != channelCount) {
					setup.maxSamplesPerBlock = (maxFrameCount * 2); //2.0 Stereo
				}
				else
				{
					setup.maxSamplesPerBlock = (maxFrameCount * channelCount); //Multichannel
				}
				
				processor->setupProcessing(setup);

				component->setActive(true);
				component->setIoMode(kAdvanced);
				processor->setProcessing(true);
				
				for (size_t i = 0; i < buscountinp; i++)
				{
					BusInfo inf;
					component->getBusInfo(kAudio, kInput, i, inf);
					
						if ((inf.flags & BusInfo::kDefaultActive) == false)
						{
							component->activateBus(kAudio, kInput, i, true);
						}
						else
						{
							component->activateBus(kAudio, kInput, i, false);
						}
				}

				for (size_t i = 0; i < buscountout; i++)
				{
					BusInfo inf;
					component->getBusInfo(kAudio, kOutput, i, inf);

					if ((inf.flags & BusInfo::kDefaultActive) == false)
					{
						component->activateBus(kAudio, kOutput, i, true);
					}
					else
					{
						component->activateBus(kAudio, kOutput, i, false);
					}
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
				else
				{
					//Reset all bypass 
					int pcount = controller->getParameterCount();
					//ParamID bypassid[10]; //bypass id
					//int bpcount = 0; //bypass parameter count

					for (size_t i = 0; i < pcount; i++)
					{
						ParameterInfo pinfo;
						int c = 0;
						controller->getParameterInfo(i, pinfo);

						std::string pname = VST3::StringConvert::convert(pinfo.title, 128);

						if (!pname.find("Bypass", 0))
						{
							controller->setParamNormalized(pinfo.id, 0);
						}
					}

					IUnitInfo* unit = 0;
					
					component->queryInterface(IUnitInfo::iid, (void**) &unit);

					if (unit)
					{
						int unitc = unit->getUnitCount();

						for (size_t i = 0; i < unitc; i++)
						{
							UnitInfo inf;
							unit->getUnitInfo(i, inf);
							int presets = unit->getProgramListCount();

							for (size_t i = 0; i < presets; i++)
							{
								ProgramListInfo inf;
								unit->getProgramListInfo(i, inf);

								for (size_t i = 0; i < inf.programCount; i++)
								{
									String128 pn;
									unit->getProgramName(inf.id,i,pn);

									std::string pname = VST3::StringConvert::convert(pn, 128);

									if (pname == "Default")
									{
										for (size_t o = 0; o < pcount; o++)
										{
											ParameterInfo pinfo;
											int c = 0;
											controller->getParameterInfo(o, pinfo);

											std::string pname = VST3::StringConvert::convert(pinfo.title, 128);

											if (!pname.find("Program", 0))
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
					
					/*
					for (size_t i = 0; i < bpcount; i++)
					{
						ValueQueue* Queue = new ValueQueue(bypassid[i], 0);
						//ValueQueue* Queue1 = new ValueQueue(bypassid[i], 1);
						//ValueQueue* Queue2 = new ValueQueue(bypassid[i], 0);
						paramch->addparam(Queue);
						//paramch->addparam(Queue1);
						//paramch->addparam(Queue2);

					};
					*/
				}

				//free(arr);
				//free(arrout);
				
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
		pcd.numSamples = frameCount;
		processor->process(pcd);
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

		cm->disconnect(cnt);
		cnt->disconnect(cm);

		if (processor)
			processor->setProcessing(false);
		
		if (component)
		{
			component->setActive(false);
			
			controller->terminate();
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

		if (paramch)
			delete paramch;

		//if (hhand)
		//	delete hhand;

		if (ivent)
			delete ivent;

		_ExitDll = reinterpret_cast<ExitDll>(GetProcAddress(Plugindll, "ExitDll"));
		if (_ExitDll) {
			_ExitDll();
		}
			FreeLibrary(Plugindll);
	}
	catch (...) {}
}