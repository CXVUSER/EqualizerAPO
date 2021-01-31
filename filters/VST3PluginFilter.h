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
 *	 15 fev 2020
 */

#pragma once

#include "IFilter.h"
#include "stdafx.h"
#include <memory>
#include <wincrypt.h>
//#include <functional>
#include "FilterEngine.h"
#include "..//helpers/RegistryHelper.h"

//VST3_SDK
#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstprocesscontext.h"
#include "pluginterfaces/vst/ivstunits.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/vst/hosting/connectionproxy.h"
#include "pluginterfaces/base/ibstream.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/vstspeaker.h"

using namespace Steinberg;
using namespace Steinberg::Vst;
using namespace Steinberg::Vst::SpeakerArr;

#define func(T,h,str)	\
		reinterpret_cast<T>(GetProcAddress(h, str))
/*
template <typename ret, typename ...arg> std::function<ret(arg...)> call(HMODULE h,LPCSTR func) {
	auto addr = GetProcAddress(h, func);
	typedef ret(*fc)(arg...);
	fc f = reinterpret_cast<fc>(addr);
	std::function<ret(arg...)> x = f;
	return x;
}
*/

class settings : public IBStream, ISizeableStream
{
public:

	settings() {};
	~settings() {
		if (buf != 0)
			free(buf);
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
		if (buffer == NULL && numBytes == NULL)
			goto LEAVE_;
		if (!buf)
			goto LEAVE_;
		if (sk > numBytes)
			goto LEAVE_;
		if (numBytes > s)
			numBytes -= (numBytes - s);

		__try {
			memcpy(buffer, &buf[sk], numBytes);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}
		sk += numBytes;
			
		__try {
			if (numBytesRead)
				*numBytesRead = numBytes;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}

		return kResultTrue;
		
		LEAVE_:
		return kResultFalse;
	};

	//Write to stream buffer
	virtual tresult PLUGIN_API write(void* buffer, int32 numBytes, int32* numBytesWritten = 0) override {
		if (buffer == NULL && numBytes == NULL)
			goto LEAVE_;
		
		buf = (char*) realloc(buf, numBytes + s);
		if (buf == NULL)
			goto LEAVE_;
		__try {
			memcpy(buf + sk, buffer, numBytes);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}

		s += numBytes;
		sk += numBytes;
		__try {
			if (numBytesWritten)
				*numBytesWritten = numBytes;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}
		return kResultTrue;
		
		LEAVE_:
		return kResultFalse;
	};

	//Set current position in the stream
	virtual tresult PLUGIN_API seek(int64 pos, int32 mode, int64* result = 0) override {
		if (mode == kIBSeekSet)
			sk = pos;
		else if(mode == kIBSeekCur)
			sk += pos;
		else if(mode == kIBSeekEnd)
			sk = s;

		__try {
			if (result != 0)
				*result = sk;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return kResultFalse;
		}
		return kResultTrue;
	};

	virtual tresult PLUGIN_API tell(int64* pos) override {
		if (pos != 0) {
			__try {
				*pos = sk;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				goto LEAVE_;
			}
			return kResultTrue;
		}
		LEAVE_:
		return kResultFalse;
	};

	virtual tresult PLUGIN_API getStreamSize(int64& size) override {
		if (&size != 0) {
			__try {
				size = s;
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				goto LEAVE_;
			}
			return kResultTrue;
		}
		LEAVE_:
		return kResultFalse;
	};

	virtual tresult PLUGIN_API setStreamSize(int64 size) override {
		s = size;
		return kResultTrue;
	};

private:
	char* buf = 0;
	int64 sk = 0;
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
	bool InitPlugin(PClassInfo cl);
	void resetPlugin();
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

	ProcessData pcd = {};

	Steinberg::Vst::ProcessContext cont = {};

	HMODULE Plugindll;

	bool bypass = true;
	bool reportCrash = true;
};
#pragma AVRT_VTABLES_END
