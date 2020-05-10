//Kirill 
// 15 fev 2020
// VST3 pkugin wrapper

#pragma once

#include "IFilter.h"
#include "stdafx.h"
#include <memory>
#include <wincrypt.h>
#include "FilterEngine.h"
#include "..//helpers/RegistryHelper.h"

#include "public.sdk/source/vst/hosting/optional.h"
#include "public.sdk/source/vst/hosting/hostclasses.h"
#include "public.sdk/source/vst/hosting/stringconvert.h"
//#include "base/source/fcommandline.h"
#include "pluginterfaces/base/funknown.h"
//#include "pluginterfaces/gui/iplugview.h"
//#include "pluginterfaces/gui/iplugviewcontentscalesupport.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/ivstprocesscontext.h"
#include "pluginterfaces/vst/ivstunits.h"
#include "pluginterfaces/vst/ivstnoteexpression.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivsthostapplication.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/vst/vsttypes.h"
#include "public.sdk/source/vst/hosting/connectionproxy.h"
#include "pluginterfaces/base/ibstream.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/vstspeaker.h"

//#include <cstdio>
//#include <iostream>

using namespace Steinberg;
using namespace Steinberg::Vst;
//using namespace VST3::Hosting;
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
		if (buf)
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

	//Read bytes from steam buffer
	virtual tresult PLUGIN_API read(void* buffer, int32 numBytes, int32* numBytesRead = 0) override {

		int delta = 0;
		int num = 0;

		__try {

			if (buffer && numBytes != 0)
			{
				char* b = reinterpret_cast<char*>(buffer);

				if (seekbuf < numBytes)
				{
					if (numBytes > s)
					{
						delta = (numBytes - s);
						numBytes = numBytes - delta;
					}

					for (size_t i = 0; i < numBytes; i++)
					{
						b[i] = buf[seekbuf + i];
						num++;
					}

					seekbuf += num;
				}

				if (numBytesRead)
					* numBytesRead = num;

				return kResultTrue;
			}

		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			if (numBytesRead)
				* numBytesRead = 0;
			return kResultFalse;
		}
		
		return kResultFalse;
	};

	//Write to stream buffer
	virtual tresult PLUGIN_API write(void* buffer, int32 numBytes, int32* numBytesWritten = 0) override {

		int num = 0;
		int size = numBytes + s;

		__try {
			if (buffer && numBytes)
			{
				char* b = reinterpret_cast<char*>(buffer);

				buf = (char*)realloc(buf, size);
				if (!buf)
					return kResultFalse;

				//memset(buf + seekbuf, 0, numBytes);
				//memcpy(buf + seekbuf, buffer, numBytes);

				
				for (size_t i = 0; i < numBytes; i++)
				{
					buf[seekbuf + i] = b[i];
					s++;
					num++;
				}
				
				seekbuf += num;

				if (numBytesWritten)
					* numBytesWritten = num;

				return kResultTrue;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			if (numBytesWritten)
				* numBytesWritten = 0;
			return kResultFalse;
		}

		return kResultFalse;
	};

	//Set current position in the stream
	virtual tresult PLUGIN_API seek(int64 pos, int32 mode, int64* result = 0) override {

		switch (mode)
		{
		case kIBSeekSet:

			seekbuf = pos;

			if (result)
				* result = seekbuf;
			break;
		case kIBSeekCur:

			seekbuf += pos;
			if (result)
				* result = seekbuf;
			break;
		case kIBSeekEnd:
			seekbuf = s;
			if (result)
				* result = seekbuf;
		default:
			break;
		}
		return kResultTrue;
	};

	virtual tresult PLUGIN_API tell(int64* pos) override {
		*pos = seekbuf;
		return kResultTrue;
	};

	virtual tresult PLUGIN_API getStreamSize(int64& size) override {

		size = s;
		return kResultTrue;

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

class hosthandler : public IComponentHandler, IComponentHandler2, IComponentHandlerBusActivation
{
public:

	virtual tresult PLUGIN_API queryInterface(const TUID _iid, void** obj) override {
		QUERY_INTERFACE(_iid, obj, FUnknown::iid, IComponentHandler)
			QUERY_INTERFACE(_iid, obj, IComponentHandler::iid, IComponentHandler)
			QUERY_INTERFACE(_iid, obj, IComponentHandler2::iid, IComponentHandler2)
			QUERY_INTERFACE(_iid, obj, IComponentHandlerBusActivation::iid, IComponentHandlerBusActivation)

			* obj = nullptr;
		return kResultFalse;
	};

	virtual uint32 PLUGIN_API addRef() override {
		return 1;
	};

	virtual uint32 PLUGIN_API release() override {
		return 1;
	};

	//------------------------------------------------------------------------
		/** To be called before calling a performEdit (e.g. on mouse-click-down event).
		This must be called in the UI-Thread context!  */
	virtual tresult PLUGIN_API beginEdit(ParamID id) override {
		return kResultTrue;
	};

	/** Called between beginEdit and endEdit to inform the handler that a given parameter has a new
	 * value. This must be called in the UI-Thread context! */
	virtual tresult PLUGIN_API performEdit(ParamID id, ParamValue valueNormalized) override {
		return kResultTrue;
	};

	/** To be called after calling a performEdit (e.g. on mouse-click-up event).
	This must be called in the UI-Thread context! */
	virtual tresult PLUGIN_API endEdit(ParamID id) override {
		return kResultTrue;
	};

	/** Instructs host to restart the component. This must be called in the UI-Thread context!
	\param flags is a combination of RestartFlags */
	virtual tresult PLUGIN_API restartComponent(int32 flags) override {
		return kResultTrue;
	};

	//------------------------------------------------------------------------
	/** Tells host that the Plug-in is dirty (something besides parameters has changed since last save),
	if true the host should apply a save before quitting. */
	virtual tresult PLUGIN_API setDirty(TBool state) override {
		return kResultTrue;
	};

	/** Tells host that it should open the Plug-in editor the next time it's possible.
	You should use this instead of showing an alert and blocking the program flow (especially on loading projects). */
	virtual tresult PLUGIN_API requestOpenEditor(FIDString name = ViewType::kEditor) override {
		return kResultTrue;
	};

	//------------------------------------------------------------------------
	/** Starts the group editing (call before a \ref IComponentHandler::beginEdit),
	the host will keep the current timestamp at this call and will use it for all \ref IComponentHandler::beginEdit
	/ \ref IComponentHandler::performEdit / \ref IComponentHandler::endEdit calls until a \ref finishGroupEdit (). */
	virtual tresult PLUGIN_API startGroupEdit() override {
		return kResultTrue;
	};

	/** Finishes the group editing started by a \ref startGroupEdit (call after a \ref IComponentHandler::endEdit). */
	virtual tresult PLUGIN_API finishGroupEdit() override {
		return kResultTrue;
	};

	//------------------------------------------------------------------------
	/** request the host to activate or deactivate a specific bus. */
	virtual tresult PLUGIN_API requestBusActivation(MediaType type, BusDirection dir, int32 index,
		TBool state) override {
		return kResultTrue;
	};

};

class pr : public IParameterChanges
{
public:

	virtual tresult PLUGIN_API queryInterface(const TUID _iid, void** obj) override {
		QUERY_INTERFACE(_iid, obj, FUnknown::iid, IParameterChanges)
			QUERY_INTERFACE(_iid, obj, IParameterChanges::iid, IParameterChanges)

			* obj = nullptr;
		return kResultFalse;
	};

	virtual uint32 PLUGIN_API addRef() override {
		return 1;
	};
	
	virtual uint32 PLUGIN_API release() override {
		return 1;
	};

	//------------------------------------------------------------------------
		/** Returns count of Parameter changes in the list. */
	virtual int32 PLUGIN_API getParameterCount() override {

		return p.size();
	};

	/** Returns the queue at a given index. */
	virtual IParamValueQueue* PLUGIN_API getParameterData(int32 index) override {

		return p[index];
	};

	/** Adds a new parameter queue with a given ID at the end of the list,
	returns it and its index in the parameter changes list. */
	virtual IParamValueQueue* PLUGIN_API addParameterData(const Vst::ParamID& id, int32& index /*out*/) override {

		return 0;
	};

	void addparam(IParamValueQueue* q) {
		if (q)
		p.push_back(q);
	};

private:
	std::vector<IParamValueQueue*> p;
};

class ValueQueue : public IParamValueQueue
{
public:

	ValueQueue(ParamID p,float _val)
		:_P(p),val(_val)
	{};

	~ValueQueue() {};

	virtual tresult PLUGIN_API queryInterface(const TUID _iid, void** obj) override {
		QUERY_INTERFACE(_iid, obj, FUnknown::iid, IParamValueQueue)
			QUERY_INTERFACE(_iid, obj, IParamValueQueue::iid, IParamValueQueue)

			* obj = nullptr;
		return kResultFalse;
	};

	virtual uint32 PLUGIN_API addRef() override {
		return 1;
	};

	virtual uint32 PLUGIN_API release() override {
		return 1;
	};

	//------------------------------------------------------------------------
		/** Returns its associated ID. */
	virtual ParamID PLUGIN_API getParameterId() override {
		return _P;
	};

	/** Returns count of points in the queue. */
	virtual int32 PLUGIN_API getPointCount() override {
		return 1;
	};

	/** Gets the value and offset at a given index. */
	virtual tresult PLUGIN_API getPoint(int32 index, int32& sampleOffset /*out*/, ParamValue& value /*out*/) override {
		
		sampleOffset = 0;

		value = val;

		return kResultTrue;
	};

	/** Adds a new value at the end of the queue, its index is returned. */
	virtual tresult PLUGIN_API addPoint(int32 sampleOffset, ParamValue value, int32& index /*out*/) override {
		return kResultFalse;
	};

private:
	ParamID _P = 0;
	float val = 0;
};



//Event handler class
class inpev : public IEventList
{
public:
	inpev() {};
	~inpev() {};

	virtual tresult PLUGIN_API queryInterface(const TUID _iid, void** obj) override {
		QUERY_INTERFACE(_iid, obj, FUnknown::iid, IEventList)
			QUERY_INTERFACE(_iid, obj, IEventList::iid, IEventList)

			* obj = nullptr;
		return kResultFalse;
	};

	virtual uint32 PLUGIN_API addRef() override {
		return 1;
	};

	virtual uint32 PLUGIN_API release() override {
		return 1;
	};

	/** Returns the count of events. */
	virtual int32 PLUGIN_API getEventCount() override {
		OutputDebugStringA("getEventCount");
		//OOOOPS!
		return 0;
	};

	/** Gets parameter by index. */
	virtual tresult PLUGIN_API getEvent(int32 index, Event& e /*out*/) override {
		//OOOOPS!
		OutputDebugStringA("getEvent");
		return kResultFalse;
	};

	/** Adds a new event. */
	virtual tresult PLUGIN_API addEvent(Event& e /*in*/) override {
		//OOOOPS!
		OutputDebugStringA("addEvent");
		return kResultFalse;
	};

private:

};

#pragma AVRT_VTABLES_BEGIN
class VST3PluginFilter : public IFilter
{
public:

		typedef bool (*InitModuleFunc) ();
		typedef Steinberg::IPluginFactory* (*GetPluginFactory) ();
		typedef bool (*ExitDll) ();

	VST3PluginFilter(FilterEngine* e, std::wstring path,std::wstring settings);
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

	//ConnectionProxy* componentCP;
	//ConnectionProxy* controllerCP;
	
	ProcessData pcd = {};
	Steinberg::Vst::ProcessContext cont = {};
	FUnknown* host = new MyDAW();
	pr* paramch = new pr();
	inpev* ivent = new inpev();
	//hosthandler* hhand = new hosthandler();

	//InitModuleFunc _InitDll;
	//GetPluginFactory _GetPluginFactory;
	//ExitDll _ExitDll;

	HMODULE Plugindll;

	bool bypass = true;
	bool reportCrash = true;
};
#pragma AVRT_VTABLES_END
