template <typename T>
Pointer<T>::Pointer (T* data) : PointerBase()
{
	msMutex.Lock();

    mData = data;
    if (mData)
    {
        RMIterator iter = msMap.find(mData);
        if (iter != msMap.end())
        {
            ++iter->second;
        }
        else
        {
            msMap[mData] = 1;
        }
    }

	msMutex.Unlock();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer<T>::Pointer(const Pointer& pointer) : PointerBase()
{
    msMutex.Lock();

    mData = pointer.mData;
    if (mData)
    {
        RMIterator iter = msMap.find(mData);
        if (iter != msMap.end())
        {
            ++iter->second;
        }
        else
        {
            _ASSERT_EXPR(false, "pointer.mData must be in the map\n");
        }
    }

    msMutex.Unlock();
}
//----------------------------------------------------------------------------
template <typename T>
Pointer<T>::~Pointer ()
{
    msMutex.Lock();

    if (mData)
    {
        RMIterator iter = msMap.find(mData);
        if (iter != msMap.end())
        {
            if (--iter->second == 0)
            {
                msMap.erase(mData);
                delete mData;
            }
        }
        else
        {
            _ASSERT_EXPR(false, "mData must be in the map\n");
        }
    }

    msMutex.Unlock();
}
//----------------------------------------------------------------------------
template <typename T>
inline Pointer<T>::operator T* () const
{
    return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T& Pointer<T>::operator* () const
{
    return *mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T* Pointer<T>::operator-> () const
{
    return mData;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer<T>& Pointer<T>::operator= (T* data)
{
    msMutex.Lock();

    if (mData != data)
    {
        RMIterator iter;

        if (data)
        {
            iter = msMap.find(data);
            if (iter != msMap.end())
            {
                ++iter->second;
            }
            else
            {
                msMap[data] = 1;
            }
        }

        if (mData)
        {
            iter = msMap.find(mData);
            if (iter != msMap.end())
            {
                if (--iter->second == 0)
                {
                    msMap.erase(mData);
                    delete mData;
                }
            }
            else
            {
                _ASSERT_EXPR(false, "mData must be in the map\n");
            }
        }

        mData = data;
    }

    msMutex.Unlock();
    return *this;
}
//----------------------------------------------------------------------------
template <typename T>
Pointer<T>& Pointer<T>::operator= (const Pointer& pointer)
{
    msMutex.Lock();

    if (mData != pointer.mData)
    {
        RMIterator iter;

        if (pointer.mData)
        {
            iter = msMap.find(pointer.mData);
            if (iter != msMap.end())
            {
                ++iter->second;
            }
            else
            {
                _ASSERT_EXPR(false, "pointer.mData must be in the map\n");
            }
        }

        if (mData)
        {
            iter = msMap.find(mData);
            if (iter != msMap.end())
            {
                if (--iter->second == 0)
                {
                    msMap.erase(mData);
                    delete mData;
                }
            }
            else
            {
                _ASSERT_EXPR(false, "mData must be in the map\n");
            }
        }

        mData = pointer.mData;
    }

    msMutex.Unlock();
    return *this;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer<T>::operator== (T* data) const
{
    return mData == data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer<T>::operator!= (T* data) const
{
    return mData != data;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer<T>::operator== (const Pointer& pointer) const
{
    return mData == pointer.mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline bool Pointer<T>::operator!= (const Pointer& pointer) const
{
    return mData != pointer.mData;
}
