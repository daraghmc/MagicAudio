#ifndef MADXSEGMENTINFO_H
#define MADXSEGMENTINFO_H

#include <dsound.h>
#include <dmusics.h>

namespace MindGames
{
class SegmentInfo
{

public:
    SegmentInfo();
    ~SegmentInfo();

    IDirectMusicSegment8* m_pqSegment;
    IDirectMusicAudioPath8* m_pqPath;
    IDirectSoundBuffer8* m_pqBuffer;
    IDirectSound3DBuffer8* m_pq3DBuffer;
};

} // namespace MindGames

#endif // MADXSEGMENTINFO_H 
