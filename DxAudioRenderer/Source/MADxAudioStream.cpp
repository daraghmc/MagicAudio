#include "MADxAudioStream.h"
#include "MADxAudioUtil.h"
#include "MAAudioFile.h"

using namespace MagicAudio;

#define MINSTREAMTIME 5

wchar_t DxAudioStream::ms_acPath[] = {'\0'};
CComPtr<IDirectSound8> DxAudioStream::ms_pqDirectSound;

DxAudioStream::DxAudioStream()
{
    m_pkStream = NULL;
    m_ulSampleCount = 0;
    m_pvStreamBuff = NULL;
    m_ulBuffSize = m_ulHalfBuffSize = 0;
    m_hStreamThread = NULL;
    m_pkSoundInfo = NULL;
}

DxAudioStream::~DxAudioStream()
{
    StopStream();
    Close();
}

void DxAudioStream::Initialize (IDirectSound8* pqDirectSound)
{
    ms_pqDirectSound = pqDirectSound;
}

void DxAudioStream::Open (Sound1D* pkSound, SoundInfo* pkInfo)
{
    m_pkSoundInfo = pkInfo;
    AudioFormat kFormat;
    Open(pkSound,&kFormat);
    if ( kFormat.iChannels != 1 )
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_NOTMONO);

    CreateBuffer(kFormat);
    InitializeStream(kFormat,pkSound->GetLooping());
}

void DxAudioStream::Open (Sound2D* pkSound, SoundInfo* pkInfo)
{
    m_pkSoundInfo = pkInfo;
    AudioFormat kFormat;
    Open(pkSound,&kFormat);
    if ( kFormat.iChannels != 2 )
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_NOTSTEREO);
    
    CreateBuffer(kFormat);
    InitializeStream(kFormat,pkSound->GetLooping());
}

void DxAudioStream::Open (Sound3D* pkSound, SoundInfo* pkInfo)
{
    m_pkSoundInfo = pkInfo;
    AudioFormat kFormat;
    Open(pkSound,&kFormat);
    if ( kFormat.iChannels != 1 )
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_NOTMONO);

    Create3DBuffer(kFormat);
    InitializeStream(kFormat,pkSound->GetLooping());
}

void DxAudioStream::Open (Audio* pkAudio, AudioFormat* pkFormat)
{
    _ASSERTE ( pkAudio->GetName() != NULL );

    wchar_t acFile[FILENAME_MAX];
    *acFile = L'\0';
    if ( ms_acPath != NULL )
        wcscpy(acFile,ms_acPath);
    wcscat(acFile, pkAudio->GetName());

    if ( (m_pkStream = _wfopen(acFile,L"rb" )) == NULL )
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_OPEN);

    char acBuff[30];
    if ( fscanf(m_pkStream,"%[^#]s",acBuff) != 1 
            || strcmp(acBuff,MA_MAF_IDENTIFIER) != 0 )
    {   
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_BADHEADER);
    }

    int iMajor, iMinor;
    if ( fscanf(m_pkStream,"#%u#%u#",&iMajor,&iMinor) != 2
        || iMajor != MA_MAF_VERSION_MAJOR
        || iMinor != MA_MAF_VERSION_MINOR )
    {
       MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_BADVERSION);
    }

    if ( fscanf(m_pkStream,"%u#%u#%u#%lu#",&pkFormat->iSampleRate,
        &pkFormat->iBytesPerSample,&pkFormat->iChannels,&m_ulSampleCount) != 4 )
    {
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_BADFORMAT);
    }

    if ( pkAudio->GetStreaming() && (m_ulSampleCount / pkFormat->iSampleRate) > 
        MINSTREAMTIME )
    {
        m_ulBuffSize = pkFormat->iSampleRate * pkFormat->iChannels * 
            pkFormat->iBytesPerSample; 
        if ( m_ulBuffSize & 0x1 )
            m_ulBuffSize++;

        m_ulHalfBuffSize = m_ulBuffSize / 2;
        m_pvStreamBuff = new char[m_ulBuffSize];
    }
    else
    {
        m_ulBuffSize = m_ulSampleCount * pkFormat->iChannels * 
            pkFormat->iBytesPerSample;
    }
}

void DxAudioStream::Close ()
{
    if ( m_pkStream != NULL )
        fclose(m_pkStream);

    if ( m_pvStreamBuff != NULL )
    {
        delete [] m_pvStreamBuff;
        m_pvStreamBuff = NULL;
    }
}

void DxAudioStream::CreateBuffer (AudioFormat& rkFormat)
{
    WAVEFORMATEX kWaveFormat;
    GenerateWaveFormat(kWaveFormat,rkFormat);
    
    DSBUFFERDESC kBuffDesc;  
    memset(&kBuffDesc,0,sizeof(DSBUFFERDESC));
    kBuffDesc.dwSize = sizeof(DSBUFFERDESC);
    kBuffDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFX | 
    DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_LOCSOFTWARE;
    kBuffDesc.lpwfxFormat = &kWaveFormat;
    kBuffDesc.guid3DAlgorithm = GUID_NULL;
    kBuffDesc.dwBufferBytes = m_ulBuffSize;
    CComPtr<IDirectSoundBuffer> pqBuffer;
    HRESULT hr = ms_pqDirectSound->CreateSoundBuffer(&kBuffDesc,&pqBuffer,NULL);
    MA_DXAUDIO_ERR(hr);
    hr = pqBuffer->QueryInterface(IID_IDirectSoundBuffer8, 
        (void**)&m_pkSoundInfo->m_pqBuffer);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioStream::Create3DBuffer (AudioFormat& rkFormat)
{
    WAVEFORMATEX kWaveFormat;
    GenerateWaveFormat(kWaveFormat,rkFormat);
    
    DSBUFFERDESC kBuffDesc;  
    memset(&kBuffDesc,0,sizeof(DSBUFFERDESC));
    kBuffDesc.dwSize = sizeof(DSBUFFERDESC);
    kBuffDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_LOCSOFTWARE | 
        DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_MUTE3DATMAXDISTANCE;
    kBuffDesc.lpwfxFormat = &kWaveFormat;
    kBuffDesc.guid3DAlgorithm = DS3DALG_HRTF_LIGHT;
    kBuffDesc.dwBufferBytes = m_ulBuffSize;

    CComPtr<IDirectSoundBuffer> pqBuffer;
    HRESULT hr = ms_pqDirectSound->CreateSoundBuffer(&kBuffDesc,&pqBuffer,NULL);
    MA_DXAUDIO_ERR(hr);
    hr = pqBuffer->QueryInterface(IID_IDirectSoundBuffer8, 
        (void**)&m_pkSoundInfo->m_pqBuffer);
    MA_DXAUDIO_ERR(hr);
    hr = m_pkSoundInfo->m_pqBuffer->QueryInterface(IID_IDirectSound3DBuffer8, 
        (void**)&m_pkSoundInfo->m_pq3DBuffer);
    MA_DXAUDIO_ERR(hr);
}

void DxAudioStream::GenerateWaveFormat (WAVEFORMATEX& rkWaveFormat, 
    AudioFormat& rkFormat)
{
    memset(&rkWaveFormat,0,sizeof(WAVEFORMATEX));
    rkWaveFormat.cbSize = sizeof(WAVEFORMATEX);
    rkWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
    rkWaveFormat.nSamplesPerSec = rkFormat.iSampleRate;
    rkWaveFormat.wBitsPerSample = 8 * rkFormat.iBytesPerSample;
    rkWaveFormat.nChannels = rkFormat.iChannels;
    rkWaveFormat.nBlockAlign = rkFormat.iBytesPerSample * rkWaveFormat.nChannels;
    rkWaveFormat.nAvgBytesPerSec = rkWaveFormat.nBlockAlign * 
    rkWaveFormat.nSamplesPerSec; 
}

void DxAudioStream::InitializeStream (AudioFormat& rkFormat, bool bLoopStream)
{

    if ( m_pvStreamBuff == NULL )
    {
        m_pvStreamBuff = (void *)new unsigned char[m_ulBuffSize];
        try
        {
            ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
                m_ulBuffSize,0);
        }
        catch ( AudioException* pkEx )
        {
            delete m_pvStreamBuff;
            m_pvStreamBuff = NULL;
            throw pkEx;
        }
        delete [] m_pvStreamBuff;
        m_pvStreamBuff = NULL;
    }
    else
    {
        HRESULT hr;
        IDirectSoundNotify8 *pqNotify;
        hr = m_pkSoundInfo->m_pqBuffer->QueryInterface(IID_IDirectSoundNotify8,
            (void**)&pqNotify); 
        MA_DXAUDIO_ERR(hr);
        
        m_kThreadParams.m_hKillEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
        m_kThreadParams.m_hHalfBuffEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
        m_kThreadParams.m_hEndBuffEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
        m_kThreadParams.m_iBuffSize = m_ulBuffSize;
        m_kThreadParams.m_pkStream = m_pkStream;
        m_kThreadParams.m_pqSoundBuff = m_pkSoundInfo->m_pqBuffer;
        m_kThreadParams.m_pvStreamBuff = m_pvStreamBuff;

        DSBPOSITIONNOTIFY akDSBNotify[2];
        akDSBNotify[0].dwOffset = m_ulHalfBuffSize - 1;
        akDSBNotify[0].hEventNotify = m_kThreadParams.m_hHalfBuffEvent;
        akDSBNotify[1].dwOffset = m_ulBuffSize - 1;
        akDSBNotify[1].hEventNotify = m_kThreadParams.m_hEndBuffEvent;

        hr = pqNotify->SetNotificationPositions(2,akDSBNotify);
        MA_DXAUDIO_ERR(hr);
        pqNotify->Release();

        ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
            m_ulHalfBuffSize,0,bLoopStream);
        ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
            m_ulHalfBuffSize,m_ulHalfBuffSize,bLoopStream);
    }
}

void DxAudioStream::StopStream (bool bCue)
{
    if (m_hStreamThread != NULL )
    {
        SetEvent(m_kThreadParams.m_hKillEvent);
        if ( WaitForSingleObject(m_hStreamThread,1000) == WAIT_TIMEOUT )
            MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_KILLTHREAD);

        CloseHandle(m_hStreamThread);
        m_hStreamThread = NULL;
    }

    if ( bCue && m_pvStreamBuff != NULL )
    {
        rewind(m_pkStream);
        DWORD dwPlay,dwWrite;
        HRESULT hr = m_pkSoundInfo->m_pqBuffer->GetCurrentPosition(&dwPlay,&dwWrite);
        MA_DXAUDIO_ERR(hr);
        if ( dwWrite >= m_ulHalfBuffSize )
        {
            ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
                m_ulBuffSize - dwWrite - 1,dwWrite+1);
            ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
                m_ulHalfBuffSize,0);
        }
        else
        {
            ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
                m_ulHalfBuffSize - dwWrite - 1,dwWrite+1);
            ReadStream(m_pkStream,m_pvStreamBuff,m_pkSoundInfo->m_pqBuffer,
                m_ulHalfBuffSize,m_ulHalfBuffSize);
        }
        hr = m_pkSoundInfo->m_pqBuffer->SetCurrentPosition(dwWrite);
        MA_DXAUDIO_WARN(hr);
    }
    else if ( bCue ) 
    {
        HRESULT hr = m_pkSoundInfo->m_pqBuffer->SetCurrentPosition(0);  
        MA_DXAUDIO_WARN(hr);
    }
}

void DxAudioStream::StartStream ()
{
    if ( (m_hStreamThread = CreateThread(NULL,0,StreamThreadProc,
        (void*)&m_kThreadParams,0,NULL)) == NULL )
    {
        MA_DXAUDIO_ERR_MSG(MA_DXAUDIO_ERRSTRING_CREATETHREAD);  
    }
}

void DxAudioStream::ReadStream (FILE* pkStream, void* pvStreamBuffer, 
    IDirectSoundBuffer8* pqSoundBuffer, int iBytes, int iOffset, bool bLoopStream)
{
    HRESULT hr;
    void* pvWrite;
    DWORD dwLength;

    hr = pqSoundBuffer->Lock(iOffset,iBytes,&pvWrite,&dwLength,NULL,NULL,0);
    MA_DXAUDIO_ERR(hr);
    size_t stRead = fread(pvStreamBuffer,sizeof(unsigned char),dwLength,pkStream);

    if ( stRead != dwLength )
        memset((unsigned char*)pvWrite + stRead,0,(dwLength - stRead) * sizeof(unsigned char));

    if ( feof(pkStream) && bLoopStream )
        rewind(pkStream);
    memcpy(pvWrite,pvStreamBuffer,dwLength);
    hr = pqSoundBuffer->Unlock(pvWrite,dwLength,NULL,0);
    MA_DXAUDIO_ERR(hr);     
}

void DxAudioStream::SetPath (wchar_t* acPath)
{
    wcscpy(ms_acPath,acPath);
}

DWORD WINAPI DxAudioStream::StreamThreadProc (void* pvParam)
{
    StreamThreadParams* pkParams = (StreamThreadParams*)pvParam;
    HANDLE hEvents[3] = {pkParams->m_hHalfBuffEvent, pkParams->m_hEndBuffEvent, 
        pkParams->m_hKillEvent};
    int iHalfBuffSize = pkParams->m_iBuffSize / 2;
    DWORD dwWhich;

    while ( (dwWhich = WaitForMultipleObjects(3,hEvents,FALSE,INFINITE)) != 
        WAIT_OBJECT_0 + 2 )
    {
        try
        {
            switch ( dwWhich )
            {
            case WAIT_OBJECT_0:
                DxAudioStream::ReadStream(pkParams->m_pkStream,
                    pkParams->m_pvStreamBuff,pkParams->m_pqSoundBuff,
                    iHalfBuffSize,0,pkParams->m_bLoopStream);
                break;
            case WAIT_OBJECT_0 + 1:
                DxAudioStream::ReadStream(pkParams->m_pkStream,
                    pkParams->m_pvStreamBuff,pkParams->m_pqSoundBuff,
                    iHalfBuffSize,iHalfBuffSize,pkParams->m_bLoopStream);
                break;
            }
        }
        catch ( AudioException* pkEx )
        {
            pkParams->m_pqSoundBuff->Stop();
            pkEx->Show();
            delete pkEx;
        }
    }

    return 0;
}
