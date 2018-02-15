inline long DxSequenceRenderer::ScaleVolume(int iVolume)
{
    long lScaledVol = (long)((iVolume - Audio::MIN_VOL) * 
        VOLSCALEFACTOR + APATHVOLMIN);

    return lScaledVol;
}
