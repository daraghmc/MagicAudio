#ifndef MADXAUDIOSTREAM_H
#define MADXAUDIOSTREAM_H

#include <stdio.h>
#include <atlbase.h>
#include <dsound.h>
#include "MADxSoundInfo.h"
#include "MADxAudioErr.h"
#include "MAAudio.h"
#include "MASound1D.h"
#include "MASound2D.h"
#include "MASound3D.h"
#include "MAAudioRenderer.h"

namespace MagicAudio
{

class DxAudioStream
{
public:
    DxAudioStream ();
    ~DxAudioStream ();
    
    static void Initialize (IDirectSound8* pqDirectSound);
    static void SetPath (wchar_t* acPath);

    void Open (Sound1D* pkSound, SoundInfo* pkInfo);
    void Open (Sound2D* pkSound, SoundInfo* pkInfo);
    void Open (Sound3D* pkSound, SoundInfo* pkInfo);
    void StartStream ();
    void StopStream (bool bCue = false);
    void Close();

private:
    class StreamThreadParams
    {
    public:
        bool m_bLoopStream;
        HANDLE m_hKillEvent;
        HANDLE m_hHalfBuffEvent;
        HANDLE m_hEndBuffEvent;
        FILE* m_pkStream;
        CComPtr<IDirectSoundBuffer8> m_pqSoundBuff;
        void* m_pvStreamBuff;
        int m_iBuffSize;
    };

    void Open(Audio* pkAudio, AudioFormat* pkFormat);
    void CreateBuffer (AudioFormat& rkFormat);
    void Create3DBuffer (AudioFormat& rkFormat);
    void GenerateWaveFormat (WAVEFORMATEX& rkWaveFormat, AudioFormat& rkFormat);
    void InitializeStream (AudioFormat& rkFormat, bool bLoopStream);
    static void ReadStream (FILE* pkStream, void* pvStreamBuff, IDirectSoundBuffer8* pqSoundBuff, int iBytes, int iOffset, bool bLoopStream = false);
    static DWORD WINAPI StreamThreadProc (void* pvParam);

    FILE* m_pkStream;
    static wchar_t ms_acPath[FILENAME_MAX];
    static CComPtr<IDirectSound8> ms_pqDirectSound;
    unsigned long m_ulSampleCount;
    unsigned long m_ulBuffSize;
    unsigned long m_ulHalfBuffSize;
    void* m_pvStreamBuff;
    StreamThreadParams m_kThreadParams;
    HANDLE m_hStreamThread;
    SoundInfo* m_pkSoundInfo;
};

} // namespace MagicAudio

#endif // #define MADXAUDIOSTREAM_H