/**Kirill
* 4 nov 2019
* Plugin loader
*/

#include "stdafx.h"
#include "PluginFactory.h"
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "FilterEngine.h"
#include "..//helpers/RegistryHelper.h"

std::vector<IFilter*> PluginFactory::createFilter(const std::wstring& configPath, std::wstring& command, std::wstring& parameters)
{
	(const std::wstring&)(configPath);

	typedef IPluginFilter* (*proc) ();
	IPluginFilter* filter = 0;
	std::wstring path = L"";
	std::wstring Data = L"";
	int type = PLUGIN_UNK;
	CLSID clsid = GUID_NULL;
	const GUID IFilter_riid = { 0xec1cc9ce, 0xfaed, 0x4822, {0x82, 0x8a, 0x82, 0x8d, 0x1a, 0x7a, 0xd3, 0x8a} }; //{EC1CC9CE-FAED-4822-828A-828D1A7Ad38A}

	if (command == L"Plugin")
	{
		std::unordered_map<std::wstring, float> paramMap;
		std::vector<std::wstring> parts = StringHelper::splitQuoted(parameters, ' ');
		for (unsigned i = 0; i + 1 < parts.size(); i += 2)
		{
			std::wstring key = parts[i];
			std::wstring value = parts[i + 1];

			if (key == L"DLL")
			{		
				type = PLUGIN_DLL;
				if (PathIsRelative(value.c_str()))
					{
						path = RegistryHelper::readValue(APP_REGPATH, L"InstallPath");
						path.append(L"\\");
						path.append(value.c_str());
					}
					else {
						path = value;
					}
			}
			else if (key == L"GUID")
			{
				type = PLUGIN_COM;
				CLSIDFromString(value.c_str(), &clsid);
			}
			else if (key == L"param")
			{
				Data = value;
			}
		}

		try
		{
			if (type == PLUGIN_DLL)
			{
				HMODULE hm = LoadLibraryW(path.c_str());
				proc CoCreatePluginInstance = reinterpret_cast<proc>(GetProcAddress(hm, "CoCreatePluginInstance"));
				if (CoCreatePluginInstance) {
					filter = CoCreatePluginInstance();
				}
			}
			else if (type == PLUGIN_COM)
			{
				HRESULT hr = CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, IFilter_riid, reinterpret_cast<void**>(&filter));
			}

			if (filter) {
				filter->setSettings(Data.c_str());
				filter->setDeviceGuid(f->getDeviceGuid().c_str());
			}
		}
		catch (...)
		{
			TraceF(L"Plugin not loaded");
			return std::vector<IFilter*>(0);
		}
	}

	if (filter == 0)
		return std::vector<IFilter*>(0);
	return std::vector<IFilter*>(1,reinterpret_cast<IFilter*>(filter));
}

void PluginFactory::initialize(FilterEngine* engine) { f = engine; }