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

#ifndef _IPROP_FX_
#define _IPROP_FX_

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
	virtual HRESULT Getcount() { return E_NOTIMPL; };
	virtual HRESULT Getat() { return E_NOTIMPL; };
	virtual HRESULT Getvalue(REFPROPERTYKEY key, PROPVARIANT* pv);
	virtual HRESULT Setvalue() { return E_NOTIMPL; };
	virtual bool TryOpenPropertyStoreRegKey();
	HRESULT DeserializePropVarinat(int type, void* src, size_t cb, PROPVARIANT* dest);
private:

	long ref = 1;
	HKEY reg = 0;
	//HKEY regProp;
	REGSAM _dwAcc;
	//wchar_t dev[520];
	std::wstring _guid;
	CRITICAL_SECTION cr;
};
#endif