#ifndef _MASMARTPOINTER_H
#define _MASMARTPOINTER_H

#include "MASynchronization.h"

#include <map>
namespace MagicAudio
{

//----------------------------------------------------------------------------
class PointerBase
{
public:
	typedef std::map<void*, int> ReferenceMap;
	typedef ReferenceMap::iterator RMIterator;
	typedef ReferenceMap::const_iterator RMCIterator;

protected:
	PointerBase();
    // The map key (void*) is the address of the shared object.  The map
    // value (int) is the number of references.
    typedef std::map<void*,int> ReferenceMap;
    typedef ReferenceMap::iterator RMIterator;
    typedef ReferenceMap::const_iterator RMCIterator;

    ReferenceMap msMap;
	CCriticalSection msMutex;
};

//----------------------------------------------------------------------------
template <typename T>
class Pointer : public PointerBase
{
public:
    // Construction and destruction.
    Pointer (T* data = 0);
    Pointer (const Pointer& pointer);
    ~Pointer ();

    // Implicit conversions.
    inline operator T* () const;
    inline T& operator* () const;
    inline T* operator-> () const;

    // Assignment.
    Pointer& operator= (T* data);
    Pointer& operator= (const Pointer& pointer);

    // Comparisons.
    inline bool operator== (T* data) const;
    inline bool operator!= (T* data) const;
    inline bool operator== (const Pointer& pointer) const;
    inline bool operator!= (const Pointer& pointer) const;

protected:
    T* mData;
};


//----------------------------------------------------------------------------

#include "MASmartPointer.inl"

}

#endif
