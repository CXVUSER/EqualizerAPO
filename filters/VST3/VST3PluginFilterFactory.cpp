#include "stdafx.h"
#include "VST3PluginFilterFactory.h"

vector<IFilter*> VST3PluginFilterFactory::createFilter(const wstring& configPath, wstring& command, wstring& parameters)
{
	VST3PluginFilter* filter = NULL;

	if (command == L"VST3")
	{	
		std::wstring plugin;
		std::wstring settings;

		unordered_map<wstring, float> paramMap;
		vector<wstring> parts = StringHelper::splitQuoted(parameters, ' ');
		for (unsigned i = 0; i + 1 < parts.size(); i += 2)
		{
			wstring key = parts[i];
			wstring value = parts[i + 1];

			if (key == L"Dll")
				plugin = value;

			if (key == L"Data")
				settings = value;

			//Load VST3 plugin DLL
		}
		void* mem = MemoryHelper::alloc(sizeof(VST3PluginFilter));
		filter = new(mem) VST3PluginFilter(filterEngine,plugin,settings);
	}

	if (filter == NULL)
		return vector<IFilter*>(0);
	return vector<IFilter*>(1, filter);
}

void VST3PluginFilterFactory::initialize(FilterEngine* engine) { filterEngine = engine; }