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
 *	 Class for chaining APO lib's
 */

#pragma once

#include <functional>
#include <ShObjIdl_core.h>
#include "audioenginebaseapo.h"
#include "helpers/StringHelper.h"
#include "helpers/LogHelper.h"
#include "helpers/RegistryHelper.h"

namespace APOTabProvider {
	using namespace std;

	HRESULT AddPages(
		LPFNADDPROPSHEETPAGE pfnAddPage,
		LPARAM lParam);

	HRESULT ReplacePage(
		UINT uPageID,
		LPFNADDPROPSHEETPAGE pfnReplacePage,
		LPARAM lParam);
};