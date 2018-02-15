#ifndef _MAEXCEPTION_H
#define _MAEXCEPTION_H

#include <stdio.h>
#include <string.h>

#define MA_MAX_ERROR_MESSAGE_LENGTH 512

namespace MagicAudio
{
#ifdef _DEBUG

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)

#define MA_THROW_ERR(type, description)\
	throw new type(__WFILE__, __LINE__, (description), Exception::SEV_FATAL);

#define MA_THROW_WARN(type, description)\
	throw new type(__WFILE__, __LINE__, (description), Exception::SEV_WARN);

#else // #ifdef _DEBUG

#define MA_THROW_ERR(type, description)\
	throw new type(NULL, __LINE__, (description), Exception::SEV_FATAL);

#define MA_THROW_WARN(type, description)\
	throw new type(NULL, __LINE__, (description), Exception::SEV_WARN);

#endif // #ifdef _DEBUG

#define MA_IS_FATAL_EX(pkException)\
    (pkException->GetSeverity() == MindGames::Exception::SEV_FATAL)

//////////////////////////////////////////////////////////////
// Class Exception - base class for all exceptions
//////////////////////////////////////////////////////////////

class Exception
{
public:
	Exception(wchar_t* acContext = NULL, 
				int iCode = 0, 
				wchar_t* acDescription = NULL,
				int iSeverity = SEV_FATAL);

	virtual ~Exception();

	virtual void Show() = 0;
	
	virtual void SetName(wchar_t* acName);
	virtual const wchar_t* GetName();
	virtual void SetContext(wchar_t*acContext);
	virtual const wchar_t* GetContext();
	virtual void SetDescription(wchar_t* acDescription);
	virtual const wchar_t* GetDescription();
	virtual void SetCode(int iCode);
	virtual const int GetCode();
	virtual void SetSeverity(int iSeverity);
	virtual const int GetSeverity();
	virtual void MakeErrorMessage();
	virtual const wchar_t* GetErrorMessage();

	const enum
	{
		SEV_WARN = 0,
		SEV_FATAL
	};

protected:
	int m_iCode;
	int m_iSeverity;
	wchar_t* m_acName;
	wchar_t* m_acContext;
	wchar_t* m_acDescription;
	wchar_t m_acErrorMessage[MA_MAX_ERROR_MESSAGE_LENGTH];
};

}; // namespace MagicAudio

#endif // _MAEXCEPTION_H