#ifndef MAFMAKER_H
#define MAFMAKER_H

#include <windows.h>
#include <mmsystem.h>
#include "MAAudioFile.h"
#include "WavToMafException.h"
#include <string>
using namespace std;

#define WAVTOMAF_MSG_PROGRESS (WM_APP + 1)
#define WAVTOMAF_MSG_DONE (WM_APP + 2)
#define WAVTOMAF_PROGRESSSCALE 32
 
class MafMaker
{
public:
    MafMaker(HWND hWndProgress);
    ~MafMaker();
    void Convert(wstring& rstrInputPath, wstring& rstrOutputPath, wstring& rstrFile);

private:
    void Open(wstring& rstrFile);
    void CreateOutputFile(wstring& rstrFile);
    void WriteHeader ();
    void WriteData ();

    FILE* m_pkOutputFile;
    HMMIO m_hMMIO;
    WAVEFORMATEX* m_pkWaveFormat;
    MMCKINFO m_kChunkInfo;
    HWND m_hWnd;
};

#endif