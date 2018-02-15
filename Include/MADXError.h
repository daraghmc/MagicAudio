// MADXError.h - Convenience macros for throwing exceptions in DirectX code

#ifndef MADXERROR_H
#define MADXERROR_H

#include "dxerr.h"

wchar_t* GetDXErrorDescription(HRESULT hr);

#define MA_DX_WARN(ExceptionClass, hr)\
	if( !SUCCEEDED(hr) ) \
		MA_THROW_WARN(ExceptionClass, GetDXErrorDescription(hr));

#define MA_DX_ERR(ExceptionClass, hr)\
	if( !SUCCEEDED(hr) ) \
		MA_THROW_ERR(ExceptionClass, GetDXErrorDescription(hr));

#endif // MADXERROR_H