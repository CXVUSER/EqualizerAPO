
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
#include "VST3PluginFilterFactory.h"
#include "FilterEngine.h"

using namespace std;

vector<IFilter*> VST3PluginFilterFactory::createFilter(const wstring& configPath, wstring& command, wstring& parameters)
{
	(const wstring&)(configPath);

	VST3PluginFilter* filter = NULL;
	std::wstring plugin;
	std::wstring settings;

	if (command == L"VST3")
	{
		unordered_map<wstring, float> paramMap;
		vector<wstring> parts = StringHelper::splitQuoted(parameters, ' ');
		for (unsigned i = 0; i + 1 < parts.size(); i += 2)
		{
			wstring key = parts[i];
			wstring value = parts[i + 1];

			if (key == L"Dll")
			{
				plugin = value;
			}
			else if (key == L"Data")
			{
				settings = value;
			}

			//Load VST3 plugin DLL
		}
		void* mem = MemoryHelper::alloc(sizeof(VST3PluginFilter));
		filter = new(mem) VST3PluginFilter(en,plugin,settings);
	}

	if (filter == NULL)
		return vector<IFilter*>(0);
	return vector<IFilter*>(1, filter);
}

void VST3PluginFilterFactory::initialize(FilterEngine* engine) { en = engine; }