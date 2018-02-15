// CGlobalPointerCache - simple template to temporarily store a pointer in global memory
// Usage:
// Call SetPtr() to store your pointer, GetPtr() to retrieve it again
// Note that the calls to GetPtr() and SetPtr() are thread safe. Access to the underlying
// pointer is locked when SetPtr() is called, and unlocked when GetPtr() is called. Hence:
// (1) The time between calls to SetPtr() and GetPtr() should be as short as possible
// (2) Each SetPtr() call should be matched by exactly one GetPtr() call 

#pragma once

#ifndef _MAGLOBALPTRCACHE_H
#define _MAGLOBALPTRCACHE_H

namespace MagicAudio
{

template <class T>
class CGlobalPtrCache
{
private:
// Pointer to be stored
	T *m_ptr;
// Critical section object for synchronized access to pointer
	CCriticalSection m_critSect;
	
public:
	CGlobalPtrCache():m_ptr(0){}
	CGlobalPtrCache(T *ptr):m_ptr(ptr){ }

// SetPtr() - Store a pointer
	void SetPtr(T *ptr)
	{
// Lock access to the pointer
		m_critSect.Lock();
		m_ptr = ptr;
	}

	void GetPtr(T **ptr)
	{
		*ptr = m_ptr;
// Unlock access to the pointer
		m_critSect.Unlock();
	}
};

}; // namespace MagicAudio

#endif // _MAGLOBALPTRCACHE_H