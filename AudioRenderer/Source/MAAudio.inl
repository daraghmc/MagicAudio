inline const wchar_t* Audio::GetName()
{
	return m_pName;
}

inline unsigned int Audio::GetVolume () 
{ 
    return m_uiVolume; 
}

inline void Audio::SetLooping (bool bLooping) 
{ 
    m_bLooping = bLooping; 
}

inline bool Audio::GetLooping () 
{ 
    return m_bLooping; 
}

inline void Audio::SetStreaming (bool bStreaming)
{
    m_bStreaming = bStreaming;
}

inline bool Audio::GetStreaming () 
{ 
    return m_bStreaming; 
}

inline vector<AudioEffect*>& Audio::GetEffects ()
{
    return m_kEffects;
}

inline int Audio::GetEffectQuantity()
{
    return m_kEffects.size();
}


