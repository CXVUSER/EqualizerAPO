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
 *	 APOFilter
 *	 24 April 2019
 *	 Class for chaining APO lib's
 */

#include "stdafx.h"
#include <functional>
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "APOTabProvider.h"

HRESULT APOTabProvider::AddPages(LPFNADDPROPSHEETPAGE pfnAddPage, LPARAM lParam)
{
	if (!pfnAddPage || !lParam) {
		return E_INVALIDARG;
	}

	wstring localconfigPath = RegistryHelper::readValue(APP_REGPATH, L"ConfigPath");
	if (localconfigPath.empty()) {
		return E_FAIL;
	}

	bool firstConfig = true;
	bool DeviceExcl = false;
	wstring configPath = {};

	function<HRESULT()> doJob = [&]() {
		if (firstConfig) {
			configPath += localconfigPath + L"\\config.txt";
			firstConfig = false;
		}
		else
		{
			if (PathIsRelative(configPath.c_str()))
				configPath = localconfigPath + L"\\" + configPath;
		}

		HANDLE hFile = CreateFileW(configPath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (!hFile) {
			return E_FAIL;
		}

		stringstream inputStream;

		char buf[8192];
		unsigned long bytesRead = -1;

		while (ReadFile(hFile, buf, sizeof(buf), &bytesRead, 0) && bytesRead != 0) {
			inputStream.write(buf, bytesRead);
		}

		CloseHandle(hFile);
		inputStream.seekg(0);

		while (inputStream.good()) {
			string encodedLine;
			getline(inputStream, encodedLine);

			if (!encodedLine.empty() && encodedLine.back() == '\r') {
				encodedLine.pop_back();
			}

			wstring line = StringHelper::toWString(encodedLine, CP_UTF8);

			if (line.find(L'\uFFFD') != -1) {
				line = StringHelper::toWString(encodedLine, CP_ACP);
			}

			size_t pos = line.find(L':');
			if (pos != -1) {
				wstring key = StringHelper::trim(line.substr(0, pos));
				wstring value = line.substr(pos + 1);

				if (key == L"Include") {
					configPath = value.c_str() + 1;
					doJob();
				}

				if (key == L"Device") {
					AudioFXExtensionParams* fx = (AudioFXExtensionParams*) lParam;

					if (fx->pwstrEndpointID && !value.empty()) {
						if (value.find(L"all") != -1)
							DeviceExcl = false;
						else
							DeviceExcl = (value.find(wcsrchr(fx->pwstrEndpointID, L'{')) == -1);
					}
				}

				if (!DeviceExcl && key == L"APO") {
					vector<wstring> parts = StringHelper::splitQuoted(value, ' ');

					for (unsigned i = 0; i + 1 < parts.size(); i += 2) {
						wstring subKey = parts[i];
						wstring subValue = parts[i + 1];

						if (subKey == L"UI") {
							try {
								GUID g;

								if (SUCCEEDED(CLSIDFromString(subValue.c_str(), &g)) && g != GUID_NULL) {
									IShellPropSheetExt* ish = 0;

									if (SUCCEEDED(CoCreateInstance(g, 0, CLSCTX_INPROC_SERVER, IID_IShellPropSheetExt, (void**)&ish))) {
										if (ish != 0) {
											ish->AddPages(pfnAddPage, lParam);
											ish->Release();
										}
									}
								}
							}
							catch (...) {
								TraceFStatic(L"APOProxy: UI library crashed name: %s", subValue.c_str());
							}
						}
					}
				}
			}
		}

		return S_OK;
		};

	return doJob();
}

HRESULT APOTabProvider::ReplacePage(UINT uPageID, LPFNADDPROPSHEETPAGE pfnReplacePage, LPARAM lParam)
{
	return E_NOTIMPL;
}