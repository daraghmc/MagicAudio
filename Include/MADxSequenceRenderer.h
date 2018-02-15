#ifndef MGDXSEQUENCERENDERER_H
#define MGDXSEQUENCERENDERER_H

#include "MADxAudioRenderer.h"
#include "MAAudioRenderer.h"
#include "MADxSegmentInfo.h"

#define APATHVOLMIN -9600
#define APATHVOLMAX 0

#include <map>

namespace MagicAudio
{

class DxSequenceRenderer : public SequenceRenderer, public DxAudioRenderer
{
public:
    DxSequenceRenderer ();
    virtual ~DxSequenceRenderer ();
 
    // General methods
    virtual void Initialize (int iWindowID, AudioFormat* pkFormat = NULL);
    virtual void SetPath (char* acPath);
    virtual void ScanPath ();
    virtual void Unload (Audio* pkAudio);
    virtual void Play (Audio* pkAudio);
    virtual bool IsPlaying (Audio* pkAudio);
    virtual void Stop (Audio *pkAudio);
    virtual void Pause (Audio* pkAudio){};
    virtual void SetLoop (Audio* pkAudio);
    virtual void SetVolume (Audio* pkAudio);

    // Sequence methods
    virtual void Load (Sequence* pkSequence);

    // Realtime effects methods
    virtual bool UpdateEffects (Audio* pkAudio, 
        AudioEffect::TYPE eType = AudioEffect::NONE);

protected:
    IDirectMusicSegment8* GetSegmentFromFile (Audio* pkAudio);
    SegmentInfo* FindSegment (Audio* pkAudio);
    void Stop (IDirectMusicSegment8* pqSegment);
    bool IsPlaying (IDirectMusicSegment8* pqSegment);
    void Unload (SegmentInfo* pkSegInfo);
    long ScaleVolume(int iVolume);

    static CComPtr<IDirectMusicLoader8> ms_pqLoader;
    static CComPtr<IDirectMusicPerformance8> ms_pqPerform;
    static wchar_t ms_awcPath[DMUS_MAX_FILENAME];
    std::map<int, SegmentInfo *> m_kSegMap;
    typedef map<int, SegmentInfo *>::iterator SEGMAPITERATOR;
    static const float VOLSCALEFACTOR;
};

#include "MADxSequenceRenderer.inl"

} // namespace MagicAudio

#endif // #define MADXSEQUENCERENDERER_H