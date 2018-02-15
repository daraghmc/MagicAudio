#include "MADXError.h"

WCHAR DX_ERROR_DESC[1024];

wchar_t* GetDXErrorDescription(HRESULT hr)
{
	DXGetErrorDescription(hr, DX_ERROR_DESC, 1024);
	return (wchar_t*)DX_ERROR_DESC;
}
