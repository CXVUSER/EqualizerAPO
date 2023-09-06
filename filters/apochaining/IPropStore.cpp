#include "stdafx.h"
#include "IPropStore.h"

IPropertyStoreFX::IPropertyStoreFX(std::wstring& Device, REGSAM dwAccess)
	:m_guid(Device), m_dwAcc(dwAccess)
{
	InitializeCriticalSection(&m_cr);
};

IPropertyStoreFX::~IPropertyStoreFX() {
	DeleteCriticalSection(&m_cr);
	RegCloseKey(m_Reg);
	//RegCloseKey(regProp);
};

HRESULT IPropertyStoreFX::Getvalue(REFPROPERTYKEY key,
	PROPVARIANT* pv) {

	auto RET_DEVICE_STRING = [&](wchar_t* dev_name) {
		if (!dev_name)
			return E_FAIL;
		size_t size = wcslen(dev_name);
		auto name = (wchar_t*)CoTaskMemAlloc(sizeof(wchar_t) * size);
		if (!name)
			return E_OUTOFMEMORY;

		memset(name, 0, sizeof(wchar_t) * size);
		wcscpy_s(name, size, dev_name);
		pv->vt = VT_LPWSTR;
		pv->pwszVal = name;
		return S_OK;
		};

	EnterCriticalSection(&m_cr);

	HRESULT hr = E_FAIL;

	if (pv == 0) {
		hr = E_POINTER;
		goto LEAVE_;
	}

	memset(pv, 0, sizeof(PROPVARIANT));

	if (key == PKEY_AudioEndpoint_GUID)
	{
		auto cl = GUID_NULL;
		LPOLESTR gd = 0;

		if (FAILED(CLSIDFromString(m_guid.c_str(), &cl)))
		{
			goto LEAVE_;
		}
		if (SUCCEEDED(StringFromCLSID(cl, &gd)))
		{
			pv->vt = VT_LPWSTR;
			pv->pwszVal = gd;
			hr = S_OK;
			goto LEAVE_;
		}
		else {
			CoTaskMemFree(gd);
			goto LEAVE_;
		}
	}

	if (key == PKEY_DeviceInterface_FriendlyName) //soundcard name
	{
		hr = RET_DEVICE_STRING(L"Realtek High Definition Audio");
		goto LEAVE_;
	}

	if (key == PKEY_Device_FriendlyName) //interface name
	{
		hr = RET_DEVICE_STRING(L"Speakers (Realtek High Definition Audio)");
		goto LEAVE_;
	}

	wchar_t keystr[128] = { 0 };

	//Convert CLSID to GUID string
	if (FAILED(StringCchPrintf(keystr, 128, L"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x},%d", key.fmtid.Data1,
		key.fmtid.Data2,
		key.fmtid.Data3,
		key.fmtid.Data4[0],
		key.fmtid.Data4[1],
		key.fmtid.Data4[2],
		key.fmtid.Data4[3],
		key.fmtid.Data4[4],
		key.fmtid.Data4[5],
		key.fmtid.Data4[6],
		key.fmtid.Data4[7],
		key.pid)))
	{
		goto LEAVE_;
	}

	DWORD type = 0;
	DWORD size = 0;

	if (RegQueryValueExW(m_Reg, keystr, 0, &type, 0, &size)) {
		goto LEAVE_;
	}

	switch (type)
	{
	case REG_NONE:
		break;
	case REG_SZ: {
		auto str = (wchar_t*)CoTaskMemAlloc(size);

		if (str) {
			memset(str, 0, size);
			if (!RegGetValueW(m_Reg, 0, keystr, RRF_RT_REG_SZ, 0, str, &size)) {
				pv->vt = VT_LPWSTR;
				pv->pwszVal = str;
				hr = S_OK;
			}
		}
		break;
	}
	case REG_EXPAND_SZ: {
		size_t s = size + 2;

		auto reg_expandstring = (void*) CoTaskMemAlloc(s);

		if (!reg_expandstring)
			break;

		IMalloc* gMalloc;
		size_t realsize = 0;

		if (SUCCEEDED(CoGetMalloc(true, &gMalloc)))
		{
			realsize = gMalloc->GetSize(reg_expandstring);
			gMalloc->Release();
		}
		else {
			goto LEAVE_FREE;
		}

		memset(reg_expandstring, 0, realsize);

		if (RegGetValueW(m_Reg, 0, keystr, 0x6, 0, reg_expandstring, &size) == ERROR_SUCCESS)
		{
			wchar_t strbuf[520];
			memset(strbuf, 0, 520);

			if (SHLoadIndirectString((PCWSTR)reg_expandstring, strbuf, 260, 0) != E_FAIL)
			{
				if (strbuf[0]) {
					size_t s = (sizeof(wchar_t) * wcslen(strbuf)) + 1;
					pv->pwszVal = 0;

					auto data = (LPWSTR)CoTaskMemAlloc(s);

					if (data)
					{
						memset(data, 0, s);
						wcscpy(data, strbuf);

						pv->pwszVal = data;
						pv->vt = VT_LPWSTR;
						hr = S_OK;
					}
				}
			}
		}

	LEAVE_FREE:
		CoTaskMemFree(reg_expandstring);
		break;
	}
	case REG_BINARY: {
		auto pvdata = (LPVOID)CoTaskMemAlloc(size);

		if (pvdata) {
			memset(pvdata, 0, size);
			if (!RegGetValueW(m_Reg, 0, keystr, RRF_RT_REG_BINARY, 0, pvdata, &size))
				hr = DeserializePropVarinat(type, pvdata, size, pv);
			CoTaskMemFree(pvdata);
		}
		break;
	}
	case REG_DWORD: {
		if (size == sizeof(DWORD))
		{
			if (!RegGetValueW(m_Reg, 0, keystr, RRF_RT_REG_DWORD, 0, &pv->ulVal, &size)) {
				pv->vt = VT_UI4;
				hr = S_OK;
			}
		}
		break;
	}
	case REG_MULTI_SZ: {
		auto str = (LPVOID)CoTaskMemAlloc(size);

		if (str) {
			memset(str, 0, size);
			if (!RegGetValueW(m_Reg, 0, keystr, RRF_RT_REG_MULTI_SZ, 0, str, &size)) {
				if (FAILED(InitPropVariantFromStringAsVector((PCWSTR)str, pv))) {
					break;
				}
				else {
					hr = S_OK;
				}
			}
		}
		break;
	}
	};

LEAVE_:
	LeaveCriticalSection(&m_cr);
	return hr;
};

bool IPropertyStoreFX::TryOpenPropertyStoreRegKey()
{
	auto hr = S_OK;
	auto result = false;
	auto devicetype = eRender;
	IMMDeviceEnumerator* enumemator = 0;

	EnterCriticalSection(&m_cr);

	hr = CoCreateInstance(CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		(void**)&enumemator);

	if (SUCCEEDED(hr)) {
		if (enumemator != 0)
		{
			IMMDevice* imd = 0;
			IMMEndpoint* ime = 0;
			std::wstring fulldevice = L"{0.0.0.00000000}.";
			fulldevice += m_guid;

			hr = enumemator->GetDevice(fulldevice.c_str(), &imd);
			if ((SUCCEEDED(hr)))
			{
				if (imd == 0)
					return false;

				if (SUCCEEDED(imd->QueryInterface(__uuidof(IMMEndpoint), (void**)&ime)))
				{
					std::wstring regfx = MM_DEV_AUD_REG_PATH;
					//std::wstring regprop = MM_DEV_AUD_REG_PATH;

					if (ime == 0)
						return false;
					if (FAILED(ime->GetDataFlow(&devicetype)))
						return false;

					ime->Release();
					imd->Release();

					switch (devicetype)
					{
					case eAll:
						return false;
					case eRender:
						regfx += L"Render\\" + m_guid + L"\\FxProperties";
						break;
					case eCapture:
						regfx += L"Capture\\" + m_guid + L"\\FxProperties";
						break;
					default:
						break;
					}

					if (m_Reg = RegistryHelper::openKey(regfx, m_dwAcc))
						result = true;
					/*
					if (!(regProp = RegistryHelper::openKey(regProp, _dwAcc)))
						return false;
					*/
					/*
					regprop += L"Render\\" + _guid + L"\\Properties";
					regprop += L"Capture\\" + _guid + L"\\Properties";
					*/
				}
			}
		}
	}

	LeaveCriticalSection(&m_cr);
	return result;
};

HRESULT IPropertyStoreFX::DeserializePropVarinat(int type, void* src, size_t cb, PROPVARIANT* dest)
{
	if (!src)
		return E_FAIL;
	if (!cb)
		return E_FAIL;
	if (!dest)
		return E_FAIL;

	*dest = { 0 };

	if (type == REG_DWORD)
	{
		dest->vt = VT_UI4;
		dest->lVal = *((LONG*)src);
		return S_OK;
	}
	else if (type == REG_SZ) {
		auto s = sizeof(wchar_t) * wcslen((wchar_t*)src);
		auto mem = (LPWSTR)CoTaskMemAlloc(s);
		if (!mem)
			return E_FAIL;

		memcpy(mem, src, s);

		dest->vt = VT_LPWSTR;
		dest->pwszVal = mem;
		return S_OK;
	}

	auto p = (PROPVARIANT*)src;
	auto t = p->vt;

	if (t == VT_EMPTY) {
		size_t s = cb - 8;

		auto mem = CoTaskMemAlloc(s);
		if (!mem)
			return E_FAIL;

		dest->blob.cbSize = p->wReserved2;
		dest->blob.pBlobData = (BYTE*)mem;

		memcpy(mem, &p->pbstrVal, s);
		dest->vt = p->vt;
		return S_OK;
	}
	else if (t == VT_BLOB) {
		size_t s = cb - 8;
		auto mem = CoTaskMemAlloc(s);
		if (!mem)
			return E_FAIL;

		dest->blob.pBlobData = (BYTE*)mem;
		dest->blob.cbSize = cb;

		memcpy(mem, &p->blob, s);
		dest->vt = t;
		return S_OK;
	}
	else if (t == VT_UI8 || t == VT_FILETIME) {
		size_t s = cb - 8;
		memcpy(&dest->pbVal, &p->pbVal, s);
		return S_OK;
	}

	switch (p->vt)
	{
	case VT_I2:
	case VT_I4:
	case VT_R4:
	case VT_R8:
	case VT_CY:
	case VT_DATE:
	case VT_ERROR:
	case VT_BOOL:
	case VT_UI1:
	case VT_UI2:
	case VT_I8:
	{
		memcpy(&dest->pbVal, &p->pbVal, 16);
		dest->vt = t;
	}
	break;
	case VT_LPSTR:
	{
		auto str = (char*)&p->pbVal;
		auto s = strlen(str);
		auto val = (char*)CoTaskMemAlloc(s);
		if (!val)
			return E_FAIL;

		memcpy(val, str, s);
		dest->pszVal = val;
		dest->vt = t;
	}
	break;
	case VT_BSTR:
	{
		auto s = wcslen(p->bstrVal + 1);
		auto mem = CoTaskMemAlloc(s * 2);
		if (!mem)
			return E_FAIL;
		memcpy(mem, &p->bstrVal, s * 2);

		dest->pbstrVal = (BSTR*)mem;
		dest->vt = t;
	}
	break;
	case VT_CLSID:
	{
		auto g = (GUID*)CoTaskMemAlloc(sizeof(GUID));
		if (!g)
			return E_FAIL;
		memcpy(g, &p->pbVal, sizeof(GUID));
		dest->puuid = g;
		dest->vt = t;
	}
	break;
	};

	return S_OK;
};