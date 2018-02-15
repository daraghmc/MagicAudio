#include "MAException.h"
 
namespace MagicAudio
{

//////////////////////////////////////////////////////////////
// Class Exception - base class for all exceptions
//////////////////////////////////////////////////////////////

Exception::Exception(wchar_t *acContext, int iCode, wchar_t *acDescription, int iSeverity):
	m_acContext(acContext),
	m_iCode(iCode), 
	m_acDescription(acDescription),
	m_iSeverity(iSeverity),
	m_acName(NULL)
{
	if (acContext)
	{
		m_acContext = new wchar_t[wcslen(acContext) + 1];
		wcscpy(m_acContext, acContext);
	}

	if (acDescription)
	{
		m_acDescription = new wchar_t[wcslen(acDescription) + 1];
		wcscpy(m_acDescription, acDescription);
	}
}

Exception::~Exception()
{
	if (m_acName) delete [] m_acName;
	if (m_acContext) delete [] m_acContext;
	if (m_acDescription) delete [] m_acDescription;
}

void Exception::MakeErrorMessage()
{
	wchar_t acCode[20];
	swprintf(acCode, 20, L"%d\n", m_iCode);

	*m_acErrorMessage = L'\0';

	if(m_acContext)
	{
		wcscat(m_acErrorMessage, m_acContext);
		wcscat(m_acErrorMessage, L"\n");
	}
	
	wcscat(m_acErrorMessage, acCode);
	
	if(m_acDescription)
	{
		wcscat(m_acErrorMessage, m_acDescription);
		wcscat(m_acErrorMessage, L"\n");
	}	
}

const wchar_t *Exception::GetErrorMessage()
{
	return m_acErrorMessage;
}

void Exception::SetName(wchar_t* acName)
{
	if (m_acName) delete [] m_acName;
	m_acName = new wchar_t[wcslen(acName) + 1];
	wcscpy(m_acName, acName);
}

const wchar_t *Exception::GetName()
{
	return m_acName;
}

void Exception::SetContext(wchar_t* acContext)
{
	if( m_acContext ) delete [] m_acContext;
	m_acContext = new wchar_t[wcslen(acContext) + 1];
	wcscpy(m_acContext, acContext);
}

const wchar_t *Exception::GetContext()
{
	return m_acContext; 
}

void Exception::SetDescription(wchar_t* acDescription)
{
	if( m_acDescription ) delete [] m_acDescription;
	m_acDescription = new wchar_t[wcslen(acDescription) + 1];
	wcscpy(m_acDescription, acDescription);
}

const wchar_t *Exception::GetDescription()
{
	return m_acDescription;
}

void Exception::SetCode(int iCode)
{
	m_iCode = iCode;
}

const int Exception::GetCode()
{
	return m_iCode;
}

void Exception::SetSeverity(int iSeverity)
{
	m_iSeverity = iSeverity;
}

const int Exception::GetSeverity()
{
	return m_iSeverity;
}

} // namespace MagicAudio




