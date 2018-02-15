#include "MADxSoundRenderer.h"
#include "MADxAudioStream.h"
#include "MADxAudioUtil.h"

using namespace MagicAudio;

wchar_t DxSoundRenderer::ms_acPath[FILENAME_MAX];
CComPtr<IDirectSound3DListener8> DxSoundRenderer::ms_pqListener;
const float DxSoundRenderer::VOLSCALEFACTOR = 
    (float)((DSBVOLUME_MAX - DSBVOLUME_MIN) / (Audio::MAX_VOL - Audio::MIN_VOL));
const float DxSoundRenderer::PANSCALEFACTOR = 
    (float)((DSBPAN_RIGHT - DSBPAN_LEFT) / (Panable::RIGHT - Panable::LEFT));

DxSoundRenderer::DxSoundRenderer ()
{
    CoInitialize(NULL);
    *ms_acPath = 0; 
}

DxSoundRenderer::~DxSoundRenderer ()
{
    for (SOUNDMAPITERATOR i = m_kSoundMap.begin(); i != m_kSoundMap.end(); i++)
        Unload((*i).second);

    if ( ms_pqListener != NULL )
        ms_pqListener.Release();

    DxAudioRenderer::ReleaseDirectSoundObject();

    CoUninitialize();
}
 
void DxSoundRenderer::Initialize (int iWindowID, AudioFormat* pkFormat)
{
    DxAudioRenderer::Initialize(iWindowID);

        DSBUFFERDESC kDesc;
        memset(&kDesc, 0, sizeof(DSBUFFERDESC));
        kDesc.dwSize = sizeof(DSBUFFERDESC); 
        kDesc.dwBufferBytes = 0; 
        kDesc.lpwfxFormat = NULL; 
        if ( pkFormat->b3D )
            kDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
        else
            kDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
        
    CComPtr<IDirectSoundBuffer> pqPrimary;
    HRESULT hr = DxAudioRenderer::GetDirectSoundObject()->CreateSoundBuffer(&kDesc,
        &pqPrimary,NULL); 
    MA_DXAUDIO_ERR(hr);
    
    if ( pkFormat->b3D )
    {
        hr = pqPrimary->QueryInterface(IID_IDirectSound3DListener8,
            (void**)&ms_pqListener);
        MA_DXAUDIO_ERR(hr);
    }

    WAVEFORMATEX kWaveFormat;       
    kWaveFormat.cbSize = sizeof(WAVEFORMATEX);
    kWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
    if ( pkFormat == NULL )
    {
        kWaveFormat.nChannels = 2;
        kWaveFormat.nSamplesPerSec = 22050;
        kWaveFormat.wBitsPerSample = 16;
        kWaveFormat.nBlockAlign = kWaveFormat.nChannels * 2;
    }
    else
    {
        kWaveFormat.nChannels = pkFormat->iChannels;
        kWaveFormat.nSamplesPerSec = pkFormat->iSampleRate;
        kWaveFormat.wBitsPerSample = 8 * pkFormat->iBytesPerSample; 
        kWaveFormat.nBlockAlign = kWaveFormat.nChannels * pkFormat->iBytesPerSample;
    }
    kWaveFormat.nAvgBytesPerSec = kWaveFormat.nSamplesPerSec * kWaveFormat.nBlockAlign;

    hr = pqPrimary->SetFormat(&kWaveFormat); 
    MA_DXAUDIO_ERR(hr);

    DxAudioStream::Initialize(DxAudioRenderer::GetDirectSoundObject());
} 

void DxSoundRenderer::SetPath (wchar_t* acPath)
{        
    wcscpy(ms_acPath,acPath);
    int iLen = wcslen(acPath);
    if ( acPath[iLen-1] != L'\\' )
        wcscat(ms_acPath,L"\\");
    
    DxAudioStream::SetPath(ms_acPath);
}

void DxSoundRenderer::ScanPath ()
{
}

void DxSoundRenderer::Unload (Audio* pkAudio)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL )
        return;

    Unload(pkInfo);
    m_kSoundMap.erase(pkAudio->GetID());
}

void DxSoundRenderer::Unload (SoundInfo* pkInfo)
{
    if( IsPlaying(pkInfo->m_pqBuffer) )
        Stop(pkInfo->m_pqBuffer);
    
    delete pkInfo;
}

void DxSoundRenderer::Play (Audio* pkAudio)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL || IsPlaying( pkInfo->m_pqBuffer ) )
        return;

    DWORD dwFlags = 0;
        
    if ( pkAudio->GetStreaming() )
    {
        pkInfo->m_pkStream->StartStream();
        dwFlags = DSBPLAY_LOOPING;
    }
    else if ( pkAudio->GetLooping() )
    {
        dwFlags = DSBPLAY_LOOPING;
    }

    HRESULT hr = pkInfo->m_pqBuffer->Play(0,0,dwFlags);
    MA_DXAUDIO_ERR(hr);
}

bool DxSoundRenderer::IsPlaying (IDirectSoundBuffer8* pqBuffer)
{
    DWORD dwStatus;
    HRESULT hr = pqBuffer->GetStatus(&dwStatus);
    if ( dwStatus & DSBSTATUS_PLAYING )
        return true;

    return false;
}

bool DxSoundRenderer::IsPlaying (Audio* pkAudio)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL )
        return false;

    return IsPlaying(pkInfo->m_pqBuffer);
}

void DxSoundRenderer::Stop (Audio* pkAudio)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL )
        return;
    Stop(pkInfo->m_pqBuffer);
    pkInfo->m_pkStream->StopStream(true);
}

void DxSoundRenderer::Stop (IDirectSoundBuffer8* pqBuffer)
{
    if ( IsPlaying(pqBuffer) )
    {
        HRESULT hr = pqBuffer->Stop();
        MA_DXAUDIO_ERR(hr);
    }
}

void DxSoundRenderer::Pause (Audio* pkAudio)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL )
        return;
    
    Stop(pkInfo->m_pqBuffer);
}

void DxSoundRenderer::SetVolume (Audio* pkAudio)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL )
        return;

    LONG lNewVol = ScaleVolume(pkAudio->GetVolume());   
    HRESULT hr = pkInfo->m_pqBuffer->SetVolume(lNewVol);
    MA_DXAUDIO_ERR(hr);
}

void DxSoundRenderer::SetLoop (Audio* pkAudio)
{
}

void DxSoundRenderer::SetPan (Panable* pkSound)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL )
        return;

    HRESULT hr = pkInfo->m_pqBuffer->SetPan(ScalePan(pkSound->GetPan()));
    MA_DXAUDIO_WARN(hr);
}

bool DxSoundRenderer::UpdateEffects (Audio* pkAudio, AudioEffect::TYPE eType)
{
    SoundInfo* pkInfo = FindSound(pkAudio);
    if ( pkInfo == NULL || IsPlaying(pkInfo->m_pqBuffer) )
        return false;

    return DxAudioRenderer::UpdateEffects(pkAudio,eType,pkInfo->m_pqBuffer,
        pkInfo->m_pq3DBuffer);
}
    
SoundInfo* DxSoundRenderer::FindSound (Audio* pkAudio)
{
    SOUNDMAPITERATOR i = m_kSoundMap.find(pkAudio->GetID());
    if ( i == m_kSoundMap.end() )
        return NULL;
    
    return (*i).second;
}
