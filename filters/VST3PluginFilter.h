
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

#pragma once

#include "IFilter.h"
#include "stdafx.h"
#include <memory>
#include <wincrypt.h>
#include "FilterEngine.h"
#include "..//helpers/RegistryHelper.h"

#include "public.sdk/source/vst/hosting/hostclasses.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
#include "pluginterfaces/base/funknown.h"
//#include "pluginterfaces/gui/iplugview.h"
//#include "pluginterfaces/gui/iplugviewcontentscalesupport.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstprocesscontext.h"
#include "pluginterfaces/vst/ivstunits.h"
//#include "pluginterfaces/vst/ivstnoteexpression.h"
//#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivsthostapplication.h"
//#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/vst/hosting/connectionproxy.h"
#include "pluginterfaces/base/ibstream.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/vstspeaker.h"

//#include <cstdio>
//#include <iostream>

using namespace Steinberg;
using namespace Steinberg::Vst;
using namespace VST3;
using namespace Steinberg::Vst::SpeakerArr;

class MyDAW : public IHostApplication
{
public:
	MyDAW() {
		FUNKNOWN_CTOR

			mPlugInterfaceSupport = owned(NEW PlugInterfaceSupport);
	};
	virtual ~MyDAW() {};

	//--- IHostApplication ---------------
	tresult PLUGIN_API getName(String128 name) SMTG_OVERRIDE
	{
		String str("EqualizerAPO Digital Audio Workstation");
		str.copyTo16(name, 0, 127);
		return kResultTrue;
	};

	tresult PLUGIN_API createInstance(TUID cid, TUID _iid, void** obj) SMTG_OVERRIDE
	{
		FUID classID(FUID::fromTUID(cid));
		FUID interfaceID(FUID::fromTUID(_iid));
		if (classID == IMessage::iid && interfaceID == IMessage::iid)
		{
			*obj = new HostMessage;
			return kResultTrue;
		}
		else if (classID == IAttributeList::iid && interfaceID == IAttributeList::iid)
		{
			*obj = new HostAttributeList;
			return kResultTrue;
		}
		*obj = nullptr;
		return kResultFalse;
	};

	virtual tresult PLUGIN_API queryInterface(const ::Steinberg::TUID _iid, void** obj) SMTG_OVERRIDE
	{
		QUERY_INTERFACE(_iid, obj, FUnknown::iid, IHostApplication)
			QUERY_INTERFACE(_iid, obj, IHostApplication::iid, IHostApplication)

			if (mPlugInterfaceSupport && mPlugInterfaceSupport->queryInterface(iid, obj) == kResultTrue)
				return kResultOk;

		*obj = nullptr;
		return kResultFalse;
	};

	virtual uint32 PLUGIN_API addRef() SMTG_OVERRIDE
	{
		return 1;
	};

	virtual uint32 PLUGIN_API release() SMTG_OVERRIDE
	{
		return 1;
	};

	PlugInterfaceSupport* getPlugInterfaceSupport() const { return mPlugInterfaceSupport; }

protected:
	IPtr<PlugInterfaceSupport> mPlugInterfaceSupport;
	int __funknownRefCount;

private:
};

class settings : public IBStream, ISizeableStream
{
public:

	settings() {};
	~settings() {
			buf != 0 ? free(buf) : 0;
	};

	virtual tresult PLUGIN_API queryInterface(const TUID _iid, void** obj) override {
		QUERY_INTERFACE(_iid, obj, FUnknown::iid, IBStream)
			QUERY_INTERFACE(_iid, obj, IBStream::iid, IBStream)
			QUERY_INTERFACE(_iid, obj, ISizeableStream::iid, ISizeableStream)

			* obj = nullptr;
		return kResultFalse;
	};

	virtual uint32 PLUGIN_API addRef() override {
		return 1;
	};

	virtual uint32 PLUGIN_API release() override {
		return 1;
	};

	//Read bytes from stream buffer
	virtual tresult PLUGIN_API read(void* buffer, int32 numBytes, int32* numBytesRead = 0) override {
		int delta = 0;
		int num = 0;

		__try {
			if (buffer != 0 && numBytes != 0)
			{
				char* b = reinterpret_cast<char*>(buffer);

				if (seekbuf < numBytes)
				{
					if (numBytes > s)
					{
						delta = (numBytes - s);
						numBytes -= delta;
					}

					memcpy(b, &buf[seekbuf], numBytes);
					num += numBytes;

					seekbuf += num;
				}

				if (numBytesRead)
					*numBytesRead = num;

				return kResultTrue;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			if (numBytesRead)
				*numBytesRead = 0;
			return kResultFalse;
		}

		return kResultFalse;
	};

	//Write to stream buffer
	virtual tresult PLUGIN_API write(void* buffer, int32 numBytes, int32* numBytesWritten = 0) override {
		int num = 0;
		int size = numBytes + s;

		__try {
			if (buffer != 0 && numBytes != 0)
			{
				char* b = reinterpret_cast<char*>(buffer);

				buf = reinterpret_cast<char*>(realloc(buf, size));
				if (buf == NULL)
					return kResultFalse;

				memcpy(buf + seekbuf, buffer, numBytes);

				s += numBytes;
				num += numBytes;

				seekbuf += num;

				if (numBytesWritten)
					*numBytesWritten = num;

				return kResultTrue;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			if (numBytesWritten)
				*numBytesWritten = 0;
			return kResultFalse;
		}

		return kResultFalse;
	};

	//Set current position in the stream
	virtual tresult PLUGIN_API seek(int64 pos, int32 mode, int64* result = 0) override {
		if (mode == kIBSeekSet)
			seekbuf = pos;

		if (mode == kIBSeekCur)
			seekbuf += pos;

		if (mode == kIBSeekEnd)
			seekbuf = s;

		if (result != 0)
			*result = seekbuf;

		return kResultTrue;
	};

	virtual tresult PLUGIN_API tell(int64* pos) override {
		if (pos != 0) {
			*pos = seekbuf;
			return kResultTrue;
		}
		return kResultFalse;
	};

	virtual tresult PLUGIN_API getStreamSize(int64& size) override {
		if (size != 0) {
			size = s;
			return kResultTrue;
		}
		return kResultFalse;
	};

	virtual tresult PLUGIN_API setStreamSize(int64 size) override {
		s = size;
		return kResultTrue;
	};

private:
	char* buf = 0;
	int64 seekbuf = 0;
	int64 s = 0;
};

#pragma AVRT_VTABLES_BEGIN
class VST3PluginFilter : public IFilter
{
public:

	typedef bool (*InitModuleFunc) ();
	typedef Steinberg::IPluginFactory* (*GetPluginFactory) ();
	typedef bool (*ExitDll) ();

	VST3PluginFilter(FilterEngine* e, std::wstring path, std::wstring settings);
	~VST3PluginFilter();

	bool getInPlace() override { return false; }
	std::vector<std::wstring> initialize(float sampleRate, unsigned maxFrameCount, std::vector<std::wstring> channelNames) override;
	void process(float** output, float** input, unsigned frameCount) override;

private:

	FilterEngine* _eapo = 0;
	std::wstring _path;
	std::wstring _settings;
	size_t channelCount = 0;

	IComponent* component;
	IAudioProcessor* processor;
	IPluginFactory* fact;
	IEditController* controller;

	//Audio bus
	AudioBusBuffers input_ = {};
	AudioBusBuffers output_ = {};

	//Conenction
	Steinberg::Vst::IConnectionPoint* cm;
	Steinberg::Vst::IConnectionPoint* cnt;
	//Steinberg::Vst::IConnectionPoint* cpr;

	ProcessData pcd = {};

	Steinberg::Vst::ProcessContext cont = {};
	FUnknown* host = new MyDAW();
	//hosthandler* hhand = new hosthandler();

	HMODULE Plugindll;

	bool bypass = true;
	bool reportCrash = true;
};
#pragma AVRT_VTABLES_END
