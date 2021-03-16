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

	if (command == L"Plugin")
	{
		std::vector<std::wstring> parts = StringHelper::splitQuoted(parameters, ' ');
		for (unsigned i = 0; i + 1 < parts.size(); i += 2)
		{
			std::wstring key = parts[i];
			std::wstring value = parts[i + 1];

			if (key == L"DLL")
			{
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
			else if (key == L"param")
			{
				Data = value;
			}
		}

		try
		{
			HMODULE hm = LoadLibraryW(path.c_str());
			auto CoCreatePluginInstance = reinterpret_cast<proc>(GetProcAddress(hm, "CoCreatePluginInstance"));
			if (CoCreatePluginInstance) {
				filter = CoCreatePluginInstance();

				if (filter) {
					filter->setSettings(Data.c_str());
					filter->setDeviceGuid(f->getDeviceGuid().c_str());
				}
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
	return std::vector<IFilter*>(1, reinterpret_cast<IFilter*>(filter));
}

void PluginFactory::initialize(FilterEngine* engine) { f = engine; }