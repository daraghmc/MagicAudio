#ifndef _MAAUDIO_H
#define _MAAUDIO_H

#include "MAAudioEffects.h"

#include <vector>
using namespace std;

namespace MagicAudio
{

class Audio
{
public:
    Audio();
	Audio(const wchar_t* pName);

    virtual ~Audio();

	void SetName(const wchar_t* pName);
	const wchar_t* GetName();

    virtual void SetVolume (unsigned int uiVolume);
    virtual unsigned int GetVolume ();
    virtual void SetLooping (bool bLoop);
    virtual bool GetLooping ();
    virtual void SetStreaming (bool bStream);
    virtual bool GetStreaming ();
    void SetEffect (AudioEffect* pkEffect);
    void RemoveEffect (AudioEffect::TYPE eType);
    void RemoveEffects ();
    vector<AudioEffect*>& GetEffects ();
    AudioEffect* GetEffect (AudioEffect::TYPE eType);
    int GetEffectQuantity ();
	int GetID() { return m_myID;  }

    static const unsigned int MIN_VOL;
    static const unsigned int MAX_VOL;

protected:
	void CommonConstruct(const wchar_t* szName);

protected:
	static int ms_ID;
	int m_myID;
	wchar_t* m_pName;

    vector<AudioEffect*>::iterator FindEffect (AudioEffect::TYPE);

    vector<AudioEffect*> m_kEffects;
    unsigned int m_uiVolume;
    bool m_bLooping;
    bool m_bStreaming;
};

#include "MAAudio.inl"

} // namespace MagicAudio

#endif // _MAAUDIO_H