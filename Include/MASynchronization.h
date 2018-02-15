// Synchronization.h - Declares and defines helper classes to facilitate
// thread synchronization. 
// CLockableObject is an abstract base class which all synchronization objects 
// must derive from. It exposes two methods - Lock() and Unlock() which must be 
// overriden in any derived class. 
// CLock locks a CLockableObject object, by calling the lockable object's Lock()
// method. It automatically unlocks the object again in its destructor, when 
// it goes out of scope. 
// CCriticalSection derives from CLockable object, and wraps a Win32 CRITICAL_SECTION.
// Its Lock() method enters the critical section, while its Unlock() method leaves the
// critical section.

#pragma once

#ifndef _MASYNCHRONIZATION_H
#define _MASYNCHRONIZATION_H

#include <windows.h>

namespace MagicAudio
{
	///////////////////////////////////////////////////////////
	//	CLockableObject
	///////////////////////////////////////////////////////////

	// Abstract base class from which all synchronization objects derive

	class CLockableObject
	{
	public:
		CLockableObject() { };
		virtual ~CLockableObject() { };
		// Lock the underlying synchronization object
		virtual void Lock() = 0;
		// Unlock the underlying synchronization object
		virtual void Unlock() = 0;
	};

	///////////////////////////////////////////////////////////
	// CLock
	///////////////////////////////////////////////////////////

	// Locks a synchronization object, and automatically unlocks it again, when
	// the CLock object goes out of scope

	class CLock
	{
	public:
		CLock(CLockableObject *pLockableObject);
		~CLock();

	private:
		CLockableObject * m_pLockableObject;
	};

	// CLock() - Lock the lockable object passed as a pointer to the constructor
	// Arguments:
	// [IN] pLockableObject: Pointer to object to lock

	inline CLock::CLock(CLockableObject *pLockableObject)
	{
		m_pLockableObject = pLockableObject;
		m_pLockableObject->Lock();
	}

	// ~CLock() - Automatically unlock the lockable object, when the CLock object goes
	// out of scope
	inline CLock::~CLock()
	{
		m_pLockableObject->Unlock();
	}
	///////////////////////////////////////////////////////////
	// CCriticalSection
	///////////////////////////////////////////////////////////

	// Wraps a Win32 CRITICAL_SECTION

	class CCriticalSection : public CLockableObject
	{
	public:
		CCriticalSection();
		virtual ~CCriticalSection();
		// Enter the critical section
		virtual void Lock();
		// Leave the critical section
		virtual void Unlock();
		void Noop() {}

	private:
		// The CRITICAL_SECTION being wrapped
		CRITICAL_SECTION m_CritSect;
	};

} // namespace MagicAudio

#endif // _MASYNCHRONIZATION_H
