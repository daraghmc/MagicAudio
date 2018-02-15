#include "MafMaker.h"

#define READBUFFSIZE 32768

MafMaker::MafMaker(HWND hWndProgress)
{
    m_pkWaveFormat = NULL;
    m_pkOutputFile = NULL;
    m_hMMIO = NULL;
    m_hWnd = hWndProgress;
}

MafMaker::~MafMaker()
{
    if ( m_pkWaveFormat )
        delete m_pkWaveFormat;

    if ( m_hMMIO != NULL )
        mmioClose(m_hMMIO,0);

    if ( m_pkOutputFile != NULL )
        fclose(m_pkOutputFile);
}

void MafMaker::Convert(wstring& rstrInputPath, wstring& rstrOutputPath, wstring& rstrFile)
{
    Open(rstrInputPath + L"\\" + rstrFile);
    CreateOutputFile(rstrOutputPath + L"\\" + rstrFile);
    WriteHeader();
    WriteData();
}

void MafMaker::Open(wstring& rstrFile)
{
    m_hMMIO = mmioOpen((wchar_t*)rstrFile.c_str(), NULL, MMIO_READ | MMIO_ALLOCBUF);
    
    if ( m_hMMIO == NULL )
        MAF_ERR(IDS_ERR_OPENINPUT);

    if ( mmioDescend( m_hMMIO, &m_kChunkInfo, NULL, 0 ) != 0 )
        MAF_ERR(IDS_ERR_OPENINPUT);

    MMCKINFO kChunkInfo;           

    if ( m_kChunkInfo.ckid != FOURCC_RIFF 
        || m_kChunkInfo.fccType != mmioFOURCC('W','A','V','E') )
    {
        MAF_ERR(IDS_ERR_NOTWAVEFILE);
    }

    kChunkInfo.ckid = mmioFOURCC('f','m','t',' ');
    if ( mmioDescend( m_hMMIO, &kChunkInfo, &m_kChunkInfo, MMIO_FINDCHUNK ) )
        MAF_ERR(IDS_ERR_NOFORMAT);

    if ( kChunkInfo.cksize < (LONG)sizeof(PCMWAVEFORMAT) )
        MAF_ERR(IDS_ERR_BADFORMAT);

    PCMWAVEFORMAT kWaveFormat;      

    if ( mmioRead( m_hMMIO, (HPSTR)&kWaveFormat, sizeof(kWaveFormat)) != sizeof(kWaveFormat) )
        MAF_ERR(IDS_ERR_READFORMAT);

    try
    {
        if ( kWaveFormat.wf.wFormatTag != WAVE_FORMAT_PCM )
            MAF_ERR(IDS_ERR_UNSUPPORTEDFORMAT);
        {
            m_pkWaveFormat = (WAVEFORMATEX*)new char[sizeof(WAVEFORMATEX)];
            memcpy(m_pkWaveFormat, &kWaveFormat, sizeof(kWaveFormat));
            m_pkWaveFormat->cbSize = 0;
        }

    }
    catch ( WavToMafException* pkEx ) 
    {
        if ( m_pkWaveFormat )
            delete m_pkWaveFormat;
        throw pkEx;
    }
}

void MafMaker::CreateOutputFile (wstring& rstrFile)
{
    int iIndex = (int)rstrFile.find_last_of('.');
    wstring strMafFile = rstrFile.substr(0,iIndex);
    strMafFile += MA_MAF_FILEEXT;

    if ( (m_pkOutputFile = _wfopen(strMafFile.c_str(), L"wb")) == NULL )
        MAF_ERR(IDS_ERR_OPENOUTPUT);
}

void MafMaker::WriteHeader ()
{
    if ( fprintf(m_pkOutputFile,"%s#",MA_MAF_IDENTIFIER) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);
    if ( fprintf(m_pkOutputFile,"%u#",MA_MAF_VERSION_MAJOR) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);
    if ( fprintf(m_pkOutputFile,"%u#",MA_MAF_VERSION_MINOR) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);
    if ( fprintf(m_pkOutputFile,"%u#",m_pkWaveFormat->nSamplesPerSec) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);
    if ( fprintf(m_pkOutputFile,"%u#",m_pkWaveFormat->wBitsPerSample / 8) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);
    if ( fprintf(m_pkOutputFile,"%u#",m_pkWaveFormat->nChannels) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);
}

void MafMaker::WriteData ()
{
    MMCKINFO kChunkInfo;
    kChunkInfo.ckid = mmioFOURCC('d','a','t','a'); 
    
    if ( mmioDescend(m_hMMIO, &kChunkInfo, &m_kChunkInfo, MMIO_FINDCHUNK) != 0 ) 
        MAF_ERR(IDS_ERR_NODATA);

    if ( kChunkInfo.cksize == 0 )
        MAF_ERR(IDS_ERR_NODATA);

    unsigned char acBuffer[READBUFFSIZE];
    memset(acBuffer,0,READBUFFSIZE);
    
    DWORD dwBytesLeft = kChunkInfo.cksize;
    DWORD dwBytesDone = 0;

    unsigned long ulSampleCount = dwBytesLeft / (m_pkWaveFormat->nChannels * m_pkWaveFormat->wBitsPerSample / 8);
    if ( fprintf(m_pkOutputFile,"%lu#",ulSampleCount) < 0 )
        MAF_ERR(IDS_ERR_BADWRITE);


    while ( dwBytesLeft > 0 )
    {
        DWORD dwBytesToRead = dwBytesLeft >=  READBUFFSIZE ? READBUFFSIZE : dwBytesLeft;
        if ( mmioRead(m_hMMIO,(HPSTR)acBuffer,dwBytesToRead) != dwBytesToRead )
            MAF_ERR(IDS_ERR_BADREAD);

        if ( fwrite(acBuffer,sizeof(unsigned char),dwBytesToRead,m_pkOutputFile) != (size_t)dwBytesToRead )
            MAF_ERR(IDS_ERR_BADWRITE);

        dwBytesLeft -= dwBytesToRead;
        dwBytesDone += dwBytesToRead;
        int iProgress = (int)(WAVTOMAF_PROGRESSSCALE * (float)dwBytesDone / kChunkInfo.cksize);  
        PostMessage(m_hWnd,WAVTOMAF_MSG_PROGRESS,(WPARAM)iProgress,0);

    }

    mmioClose(m_hMMIO,0);
    fclose(m_pkOutputFile);
    m_hMMIO = NULL;
}


