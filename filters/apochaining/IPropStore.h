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
 *	 IPropertyStore
 *	 Class for gathering APO properties from registry (APOFilter.h)
 */

#pragma once

#include <Unknwn.h>
#include "strsafe.h"
#include <propvarutil.h>
#include <mmdeviceapi.h>
#include <Functiondiscoverykeys_devpkey.h>
#include "helpers/RegistryHelper.h"

#define MM_DEV_AUD_REG_PATH L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\MMDevices\\Audio\\"

class IPropertyStoreFX : public IUnknown
{
public:
	IPropertyStoreFX::IPropertyStoreFX(std::wstring& Device, REGSAM dwAccess);
	~IPropertyStoreFX();

	virtual HRESULT QueryInterface(const IID& riid, void** ppvObject) { return E_NOINTERFACE; };
	virtual ULONG AddRef() { return 0; };
	virtual ULONG Release() { return 0; };

	//IPropertyStore
	virtual HRESULT Getcount() { return E_NOTIMPL; };
	virtual HRESULT Getat() { return E_NOTIMPL; };
	virtual HRESULT Getvalue(REFPROPERTYKEY key, PROPVARIANT* pv);
	virtual HRESULT Setvalue() { return E_NOTIMPL; };
	virtual bool TryOpenPropertyStoreRegKey();
	HRESULT DeserializePropVarinat(int type, void* src, size_t cb, PROPVARIANT* dest);
private:

	long m_Ref = 1;
	HKEY m_Reg = 0;
	//HKEY regProp;
	REGSAM m_dwAcc;
	//wchar_t dev[520];
	std::wstring m_guid;
	CRITICAL_SECTION m_cr;
};