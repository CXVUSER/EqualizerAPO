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
		if (m_buf != 0)
			free(m_buf);
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
		if (!m_buf)
			goto LEAVE_;
		if (m_sk > numBytes)
			goto LEAVE_;
		if (numBytes > m_s)
			numBytes -= (numBytes - m_s);

		__try {
			memcpy(buffer, &m_buf[m_sk], numBytes);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}
		m_sk += numBytes;
			
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
		
		m_buf = (char*) realloc(m_buf, numBytes + m_s);
		if (m_buf == NULL)
			goto LEAVE_;
		__try {
			memcpy(m_buf + m_sk, buffer, numBytes);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			goto LEAVE_;
		}

		m_s += numBytes;
		m_sk += numBytes;
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
			m_sk = pos;
		else if(mode == kIBSeekCur)
			m_sk += pos;
		else if(mode == kIBSeekEnd)
			m_sk = m_s;

		__try {
			if (result != 0)
				*result = m_sk;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return kResultFalse;
		}
		return kResultTrue;
	};

	virtual tresult PLUGIN_API tell(int64* pos) override {
		if (pos != 0) {
			__try {
				*pos = m_sk;
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
				size = m_s;
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
		m_s = size;
		return kResultTrue;
	};

private:
	char* m_buf = 0;
	int64 m_sk = 0;
	int64 m_s = 0;
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
