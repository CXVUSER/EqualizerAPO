#include "stdafx.h"
#include "APOFilterFactory.h"

vector<IFilter*> APOFilterFactory::createFilter(const wstring& configPath, wstring& command, wstring& parameters)
{
	APOProxyFilter* filter = NULL;

	if (command == L"APO")
	{
		GUID fx_guid = GUID_NULL;
		unordered_map<wstring, float> paramMap;
		vector<wstring> parts = StringHelper::splitQuoted(parameters, ' ');
		for (unsigned i = 0; i + 1 < parts.size(); i += 2)
		{
			wstring key = parts[i];
			wstring value = parts[i + 1];
	
			if (key == L"FX")
				CLSIDFromString(value.c_str(), &fx_guid);
		}
			void* mem = MemoryHelper::alloc(sizeof(APOProxyFilter));
			filter = new(mem) APOProxyFilter(fx_guid,filterEngine);
	}

	if (filter == NULL)
		return vector<IFilter*>(0);
	return vector<IFilter*>(1, filter);
}

void APOFilterFactory::initialize(FilterEngine* engine) { filterEngine = engine; }