inline long DxSoundRenderer::ScaleVolume(int iVolume)
{
    long lScaledVol = (long)((iVolume - Audio::MIN_VOL) * 
        VOLSCALEFACTOR + DSBVOLUME_MIN);

    return lScaledVol;
}

inline long DxSoundRenderer::ScalePan(int iPan)
{
    long lScaledPan = (long)(iPan * PANSCALEFACTOR);
    return lScaledPan;
}