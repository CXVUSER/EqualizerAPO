/**Kirill
* 24 April 2019
* IPropertyStore 
* Class for gathering APO properties from registry (APOFilter.h)
*/

#pragma once

#include <Unknwn.h>
#include <audioenginebaseapo.h>
#include <BaseAudioProcessingObject.h>
#include <audioclient.h>
#include <propvarutil.h>
#include <Unknwn.h>
#include <Functiondiscoverykeys_devpkey.h>

#include "helpers/RegistryHelper.h"

#ifndef _IPROP_FX_
#define _IPROP_FX_

#define MM_DEV_AUD_REG_PATH L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\MMDevices\\Audio\\"

class IPropertyStoreFX : public IUnknown
{
public:

	//const IID unknw_gd = { 0x886D8EEB, 0x8CF2, 0x4446, { 0x8D,0x02,0xCD,0xBA,0x1D,0xBD,0xCF,0x99 } };

	//IPropertyStoreFX(const wchar_t* device, REGSAM dwAccess);
	IPropertyStoreFX::IPropertyStoreFX(std::wstring& Device, REGSAM dwAccess);
	~IPropertyStoreFX();

	virtual HRESULT QueryInterface(const IID& riid, void** ppvObject);
	virtual ULONG AddRef();
	virtual ULONG Release();

	//IPropertyStore
	virtual HRESULT Getcount();
	virtual HRESULT Getat();
	virtual HRESULT Getvalue(REFPROPERTYKEY key, PROPVARIANT* pv);
	virtual HRESULT Setvalue();
	virtual HRESULT TryOpenPropertyStoreRegKey(bool* result);
	HRESULT DeserializePropVarinat(int type, PROPVARIANT* src, size_t cb, PROPVARIANT* dest);
	//__declspec(noinline) static bool IsBadPtr(char* mem, size_t size);
private:

	long ref;
	HKEY reg;
	//HKEY regProp;
	REGSAM _dwAcc;
	//wchar_t dev[520];
	std::wstring _guid;
	CRITICAL_SECTION cr;
};
#else
#error IPropertyStore.h already defined
#endif