#include "MADxSoundInfo.h"
#include "MADxAudioStream.h"

using namespace MagicAudio;

SoundInfo::SoundInfo()
{
    m_pqBuffer = NULL;
    m_pq3DBuffer = NULL;
    m_pkStream = NULL;
}

SoundInfo::~SoundInfo()
{
    if ( m_pqBuffer != NULL )
        m_pqBuffer->Release();
    if ( m_pq3DBuffer != NULL )
        m_pq3DBuffer->Release();
    if ( m_pkStream != NULL )
        delete m_pkStream;
}
