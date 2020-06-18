/**Kirill
* 24 April 2019
* IPropertyStore
* Class for gathering APO properties from registry (APOFilter.h)
*/

#include "stdafx.h"
#include "IPropStore.h"

IPropertyStoreFX::IPropertyStoreFX(std::wstring& Device, REGSAM dwAccess)
	:_guid(Device), _dwAcc(dwAccess)
{
	reg = 0;
	//regProp = 0;
	ref = 1;
	InitializeCriticalSection(&cr);
};

IPropertyStoreFX::~IPropertyStoreFX() {
	DeleteCriticalSection(&cr);
	RegCloseKey(reg);
	//RegCloseKey(regProp);
}

HRESULT IPropertyStoreFX::QueryInterface(const IID& riid, void** ppvObject) {
	if (riid == GUID_NULL)
		return S_OK;
	return E_NOINTERFACE;
};

ULONG IPropertyStoreFX::AddRef() {
	return InterlockedIncrement(&ref);
};

ULONG IPropertyStoreFX::Release() {
	if (InterlockedDecrement(&ref) == 1) {
		(this)->~IPropertyStoreFX();
		return 0;
	}
	return ref;
};

//IPropertyStore

/*
#pragma optimize("",off)
bool IPropertyStoreFX::IsBadPtr(char* mem, size_t size)
{
	bool error = false;

	if (mem)
	{
		__try
		{
			char byte;

			for (size_t i = 0; i < size; i+=4)
			{
				byte = mem[i];
				byte = mem[i+1];
				byte = mem[i+2];
				byte = mem[i+3];
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			error = true;
		}
	}
	else { error = true; };

	return error;
};
#pragma optimize("",on)
*/

HRESULT IPropertyStoreFX::Getvalue(REFPROPERTYKEY key,
	PROPVARIANT* pv) {

#define LEAVE_(p)	\
		LeaveCriticalSection(&cr);	\
		return p;

#define RET_DEV_STRING(p)	\
		wchar_t* name = reinterpret_cast<wchar_t*> (CoTaskMemAlloc(240));	\
		memset(name,0,240); \
		wcscpy(name, p);	\
		pv->vt = VT_LPWSTR;	\
		pv->pwszVal = name;	\
		LEAVE_(S_OK)

	EnterCriticalSection(&cr);

	HRESULT hr = E_FAIL;

	if (pv == 0)
	{
		LEAVE_(E_POINTER)
	}

	wchar_t keystr[128] = { 0 };

	memset(pv, 0, sizeof(PROPVARIANT));

	if (key == PKEY_AudioEndpoint_GUID)
	{
		CLSID cl = GUID_NULL;
		LPOLESTR gd = 0;

		if (!FAILED(CLSIDFromString((this->_guid).c_str(), &cl)) |
			!FAILED(StringFromCLSID(cl, &gd)))
		{
			pv->vt = VT_LPWSTR;
			pv->pwszVal = gd;
			LEAVE_(S_OK)
		}
		else {
			CoTaskMemFree(gd);
			LEAVE_(E_FAIL)
		}
	}

	if (key == PKEY_DeviceInterface_FriendlyName) //soundcard name
	{
		RET_DEV_STRING(L"ESI Juli@")
	} //...

	if (key == PKEY_Device_FriendlyName) //interface name
	{
		RET_DEV_STRING(L"Speakers (ESI Juli@)")
	} //...

	//Convert CLSID to GUID string
	hr = StringCchPrintf(keystr, 128, L"{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x},%d", key.fmtid.Data1,
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
		key.pid);

	if (FAILED(hr)) {
		LEAVE_(E_FAIL)
	}

	DWORD type = 0;
	DWORD size = 0;

	LSTATUS status = RegQueryValueExW(reg, keystr, 0, &type, 0, &size);

	if (status) {
		LEAVE_(E_FAIL)
	}

	if (type == REG_NONE) {
		LEAVE_(E_FAIL)
	}

		if (type == REG_SZ)
		{
			DWORD sdata = size;

			wchar_t* x = reinterpret_cast<wchar_t*>(CoTaskMemAlloc(size));

			LSTATUS status = RegGetValueW(reg, 0, keystr, RRF_RT_REG_SZ, 0, x, &sdata);

			if (!status) {
				pv->vt = VT_LPWSTR;
				pv->pwszVal = x;
				hr = S_OK;
			}
			LEAVE_(hr)
		}

	if (type == REG_DWORD)
	{
		DWORD sdata = size;

		if (size == 4)
		{
			LSTATUS status = RegGetValueW(reg, 0, keystr, RRF_RT_REG_DWORD, 0, &pv->ulVal, &sdata);

			if (!status) {
				pv->vt = VT_UI4;
				hr = S_OK;
			}
		}
		LEAVE_(hr)
	}

	if (type == REG_BINARY)
	{
		DWORD sdata = size;
		PROPVARIANT pvdata = { 0 };

		LSTATUS status = RegGetValueW(reg, 0, keystr, RRF_RT_REG_BINARY, 0, &pvdata, &sdata);

		if (!status)
		{
			HRESULT h = DeserializePropVarinat(REG_BINARY, &pvdata, size, pv);
			if (!h)
				hr = S_OK;
		}
		LEAVE_(hr)
	}

	if (type == REG_MULTI_SZ)
	{
		DWORD sdata = size;
		LPVOID str = CoTaskMemAlloc(size);
		LSTATUS status = RegGetValueW(reg, 0, keystr, RRF_RT_REG_MULTI_SZ, 0, str, &sdata);

		if (!status) {
			hr = InitPropVariantFromStringAsVector((PCWSTR)str, pv);

			if (FAILED(hr))
				hr = E_FAIL;

			CoTaskMemFree(str);
			hr = S_OK;
		}
		LEAVE_(hr)
	}

	if (type == REG_EXPAND_SZ) {
		size_t s = size + 2;
		DWORD sdata;

		void* vm = CoTaskMemAlloc(s);

		if (vm)
		{
			IMalloc* ml;
			size_t s2 = 0;

			if (!FAILED(CoGetMalloc(true, &ml)))
			{
				s2 = ml->GetSize(vm);
				ml->Release();
			}

			memset(vm, 0, s2);

			LSTATUS status = RegGetValueW(reg, 0, keystr, 0x6, 0, vm, &sdata);

			if (status != ERROR_FILE_NOT_FOUND) {
				if (status == ERROR_SUCCESS)
				{
					wchar_t buf[520];
					memset(buf, 0, 208);

					if (SHLoadIndirectString((PCWSTR)vm, buf, 260, 0) != E_FAIL)
					{
						pv->vt = VT_LPWSTR; // 0x1F
						pv->pwszVal = (LPWSTR)buf;
						LEAVE_(S_OK)
					}
					else
					{
						if (GetLastError() == ERROR_ACCESS_DENIED) {
							LEAVE_(E_FAIL)
						}
					}
				}
				else
				{
					LEAVE_(E_FAIL)
				}
			}
		}
		LEAVE_(hr)
	}

	LEAVE_(hr)
};

HRESULT IPropertyStoreFX::TryOpenPropertyStoreRegKey(bool* result)
{
	(bool*)(result);

	HRESULT hr = S_OK;
	EDataFlow devicetype = eAll;
	IMMDeviceEnumerator* enumemator = 0;

	EnterCriticalSection(&cr);

	std::wstring regfx = MM_DEV_AUD_REG_PATH;
	//std::wstring regprop = MM_DEV_AUD_REG_PATH;

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		reinterpret_cast<void**> (&enumemator));
	if (!FAILED(hr) || enumemator)
	{
		IMMDevice* imd = 0;
		IMMEndpoint* ime = 0;
		std::wstring fulldevice = L"{0.0.0.00000000}.";
		fulldevice += (this->_guid);

		hr = enumemator->GetDevice(fulldevice.c_str(), &imd);
		if (!FAILED(hr) || imd)
		{
			if (imd->QueryInterface(__uuidof(IMMEndpoint), reinterpret_cast<void**>(&ime)) ||
				ime == 0 || FAILED(ime->GetDataFlow(&devicetype)))
				return E_FAIL;

			switch (devicetype)
			{
			case eRender:
				regfx += L"Render\\" + (this->_guid) + L"\\FxProperties";

				/*
				regprop += L"Render\\" + (this->_guid) + L"\\Properties";
				*/
				break;
			case eCapture:
				regfx += L"Capture\\" + (this->_guid) + L"\\FxProperties";

				/*
				regprop += L"Capture\\" + (this->_guid) + L"\\Properties";
				*/
				break;
			case eAll:
				hr = E_FAIL;
				break;
			default:
				break;
			}

			ime->Release();
			imd->Release();
		}
	}

	if (!((this->reg) = RegistryHelper::openKey(regfx, (this->_dwAcc))))
		hr = E_FAIL;

	/*
	if (!((this->regProp) = RegistryHelper::openKey(regProp, (this->_dwAcc))))
		hr = E_FAIL;
	*/

	LeaveCriticalSection(&(this->cr));

	return hr;
}

HRESULT IPropertyStoreFX::DeserializePropVarinat(int type, PROPVARIANT* src, size_t cb, PROPVARIANT* dest)
{
	if (!src)
		return E_FAIL;
	if (!cb)
		return E_FAIL;

	dest->vt = VT_EMPTY;

	if (type == 4)
	{
		dest->vt = VT_UI4;
		dest->lVal = src->lVal;
		return S_OK;
	}

	switch (src->vt)
	{
	case VT_I1:
		dest->cVal = src->cVal;
		break;
	case VT_I4:
		dest->lVal = src->lVal;
		break;
	case VT_UI1:
		dest->bVal = src->bVal;
		break;
	case VT_BOOL:
		dest->boolVal = src->boolVal;
		break;
	case VT_BSTR:
	case VT_R4:
		dest->fltVal = src->fltVal;
		break;
	case VT_UI4:
		dest->ulVal = src->ulVal;
	case VT_DECIMAL:
		dest->decVal = src->decVal;
		break;
	case VT_EMPTY:

		break;
	default:
		break;
	}

	dest->vt = src->vt;

	return false;
};