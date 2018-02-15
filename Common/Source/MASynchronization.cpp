#include "MASynchronization.h"

namespace MagicAudio
{

// CCriticalSection(): Initialise the CRITICAL_SECTION member

CCriticalSection::CCriticalSection()
{
	InitializeCriticalSection(&m_CritSect);
}

// ~CCriticalSection(): Delete the CRITICAL_SECTION

CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(&m_CritSect);
}

// Lock(): Enter the critical section

void CCriticalSection::Lock()
{
	EnterCriticalSection(&m_CritSect);
}

// Unlock(): Leave the critical section

void CCriticalSection::Unlock()
{
	LeaveCriticalSection(&m_CritSect);
}

} // namespace MagicAudio

