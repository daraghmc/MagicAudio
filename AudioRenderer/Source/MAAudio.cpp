#include "MAAudio.h"
#include "MAAudio.mcr"

using namespace MagicAudio;

///////////////////////////////////////////////////////////////////////////////

const unsigned int Audio::MIN_VOL = 0;
const unsigned int Audio::MAX_VOL = 100;

int Audio::ms_ID = 1;

void Audio::CommonConstruct(const wchar_t* pName)
{
	m_bLooping = false;
	m_bStreaming = false;
	m_uiVolume = 97;
	m_myID = ms_ID++;
	if (pName != NULL)
		SetName(pName);
	else
		m_pName = NULL;
}

Audio::Audio ()
{
	CommonConstruct(NULL);
}

Audio::Audio(const wchar_t* pName)
{
	CommonConstruct(pName);
}

Audio::~Audio ()
{
	if (m_pName != NULL)
		delete[] m_pName;

    vector<AudioEffect*>::iterator it;
    
    for (it = m_kEffects.begin(); it != m_kEffects.end(); ++it)
        delete (*it);
}

void Audio::SetName(const wchar_t* pName)
{
	if (m_pName != NULL)
		delete[] m_pName;

	m_pName = new wchar_t[wcslen(pName) + 1];
	wcscpy(m_pName, pName);
}

void Audio::SetVolume (unsigned int uiVolume)
{
    MAAUDIO_CLAMP(uiVolume,MIN_VOL,MAX_VOL);
    m_uiVolume = uiVolume;
}

void Audio::SetEffect (AudioEffect* pkEffect)
{
    vector<AudioEffect*>::iterator it;
    
    for (it = m_kEffects.begin(); it < m_kEffects.end(); it++)
    {
// If this Audio object already has this type of effect, then replace the 
// old with the new
        if ( (*it)->Type() == pkEffect->Type() )
        {
            delete (*it);
            m_kEffects.erase(it); 
            break;
        }
    }
    
    m_kEffects.push_back(pkEffect);
}

AudioEffect* Audio::GetEffect (AudioEffect::TYPE eType)
{
    vector<AudioEffect*>::iterator it = FindEffect(eType);
    if ( it != m_kEffects.end() )
        return (*it);

    return NULL;
}

void Audio::RemoveEffect (AudioEffect::TYPE eType)
{
    vector<AudioEffect*>::iterator it = FindEffect(eType);
    if ( it != m_kEffects.end() )
    {
        delete *it;
        m_kEffects.erase(it);
    }
}

void Audio::RemoveEffects ()
{
    vector<AudioEffect*>::iterator it;
    for (it = m_kEffects.begin(); it < m_kEffects.end(); it++)
    {
        delete *it;
        m_kEffects.erase(it);
    }
}

vector<AudioEffect*>::iterator Audio::FindEffect (AudioEffect::TYPE eType)
{
    vector<AudioEffect*>::iterator it;

    for (it = m_kEffects.begin(); it < m_kEffects.end(); it++)
    {
        if ( eType == (*it)->Type() )
            return it;    
    }

    return it;
}
