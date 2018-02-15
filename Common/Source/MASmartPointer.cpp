#include "MASmartPointer.h"

namespace MagicAudio
{

static CCriticalSection& GetMutex()
{
	static CCriticalSection mutex;
	return mutex;
}

static PointerBase::ReferenceMap& GetMap()
{
	static PointerBase::ReferenceMap map;
	return map;
}

PointerBase::PointerBase()
{
	msMap = GetMap();
}
	
} // namespace MagicAudio
