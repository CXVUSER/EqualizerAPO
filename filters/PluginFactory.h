
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
 *	4 nov 2019
 *	Plugin loader
 */

#pragma once

#include "IFilterFactory.h"
#include "IFilter.h"
#include <string>

/*
class ix
{

public:

	void setPreMix(bool preMix);
	void setDeviceInfo(bool capture, bool postMixInstalled, const std::wstring& deviceName, const std::wstring& connectionName, const std::wstring& deviceGuid, const std::wstring& deviceString);

	void loadConfig(const std::wstring& customPath = L"") {
	
		f->loadConfig(customPath);
	
	};
	void loadConfigFile(const std::wstring& path) {
	
		f->loadConfigFile(path);
	};
	void watchRegistryKey(const std::wstring& key) {
		
		f->watchRegistryKey(key);
	
	};
	
	virtual bool IsPreMix() {
		return  f->isPreMix();
	};

	virtual bool IsCapture() {
	
		return f->isCapture();
	};
	virtual bool IsPostMixInstalled() {
	
		f->isPostMixInstalled();
	
	};
	
	virtual std::wstring GetDeviceName() {
	
		return f->getDeviceName();
	
	};
	virtual std::wstring GetConnectionName() {
	
		return f->getConnectionName();
	
	};
	virtual std::wstring GetDeviceGuid() {
	
		return GetDeviceGuid();
	
	};
	virtual std::wstring GetDeviceString() {
	
		return GetDeviceString();

	};
	virtual unsigned GetInputChannelCount() {
	
		return f->getInputChannelCount();

	};
	virtual unsigned GetRealChannelCount() {
	
		return f->getRealChannelCount();
	
	};
	virtual unsigned GetOutputChannelCount() {
	
		return f->getOutputChannelCount();

	};
	virtual unsigned GetChannelMask() {
	
		return f->getChannelMask();
	
	};
	virtual float GetSampleRate() {
	
		return f->getSampleRate();
	
	};
	virtual unsigned GetMaxFrameCount() {
	
		return f->getMaxFrameCount();
	
	};
	virtual mup::ParserX* GetParser() {
	
		return f->getParser();

	};

private:
	FilterEngine* f;
};
*/

#pragma AVRT_VTABLES_BEGIN
class IPluginFilter : public IFilter
{
public:
	virtual bool setSettings(const wchar_t* param) = 0;
	virtual void setDeviceGuid(const wchar_t* guid) = 0;
protected:
};
#pragma AVRT_VTABLES_END

enum plgtype
{
	PLUGIN_DLL = 1,
	PLUGIN_COM,
	PLUGIN_UNK
};

class PluginFactory : public IFilterFactory
{
public:
	std::vector<IFilter*> createFilter(const std::wstring& configPath, std::wstring& command, std::wstring& parameters) override;
	void initialize(FilterEngine* engine) override;

private:
	FilterEngine* f;
};
