#include "MADxSoundRenderer.h"
#include "MADxAudioStream.h"
#include "MADxAudioUtil.h"

using namespace MagicAudio;

void DxSoundRenderer::Load (Sound2D* pkSound)
{
    SoundInfo* pkInfo = new SoundInfo;
    
    try
    {
        pkInfo->m_pkStream = new DxAudioStream;
        pkInfo->m_pkStream->Open(pkSound,pkInfo);
        m_kSoundMap[pkSound->GetID()] = pkInfo;
        SetVolume(pkSound);
        SetPan(pkSound);
    }
    catch( AudioException* pkAudEx)
    {
        delete pkInfo;
        throw pkAudEx;
    }
}
