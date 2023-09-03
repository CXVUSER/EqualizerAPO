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
 *	 24 April 2019
 *	 Class for gathering APO properties from registry (APOFilter.h)
 */

#pragma once

#include <Unknwn.h>
#include <audioenginebaseapo.h>
#include <BaseAudioProcessingObject.h>
#include <audioclient.h>
#include <propvarutil.h>
#include <Unknwn.h>
#include <mmdeviceapi.h>
#include <Functiondiscoverykeys_devpkey.h>
#include "helpers/RegistryHelper.h"

#define NOT_IMPL { return E_NOTIMPL; };
#define MM_DEV_AUD_REG_PATH L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\MMDevices\\Audio\\"

class IPropertyStoreFX : public IUnknown
{
public:
	//IPropertyStoreFX(const wchar_t* device, REGSAM dwAccess);
	IPropertyStoreFX::IPropertyStoreFX(std::wstring& Device, REGSAM dwAccess);
	~IPropertyStoreFX();

	virtual HRESULT QueryInterface(const IID& riid, void** ppvObject);
	virtual ULONG AddRef();
	virtual ULONG Release();

	//IPropertyStore
	virtual HRESULT Getcount() NOT_IMPL
	virtual HRESULT Getat() NOT_IMPL
	virtual HRESULT Getvalue(REFPROPERTYKEY key, PROPVARIANT* pv);
	virtual HRESULT Setvalue() NOT_IMPL
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