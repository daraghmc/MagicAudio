#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "AudioFXDesignerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace MagicAudio;

Pointer<SoundRenderer> CAudioFXDesignerDlg::ms_spkSoundRenderer;

CAudioFXDesignerDlg::CAudioFXDesignerDlg(CWnd* pParent)
    : CDialog(CAudioFXDesignerDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_APPICON);
}

void CAudioFXDesignerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_PLAY, m_kPlayButton);
    DDX_Control(pDX, IDC_CHECK_DELAY, m_kCheckDelay);
    DDX_Control(pDX, IDC_CHECK_AMPMOD, m_kCheckAmpMod);
    DDX_Control(pDX, IDC_CHECK_CHORUS, m_kCheckChorus);
    DDX_Control(pDX, IDC_CHECK_COMPRESSOR, m_kCheckCompressor);
    DDX_Control(pDX, IDC_CHECK_ENVERB, m_kCheckEnVerb);
    DDX_Control(pDX, IDC_CHECK_FLANGER, m_kCheckFlanger);
    DDX_Control(pDX, IDC_CHECK_REVERB, m_kCheckReverb);
    DDX_Control(pDX, IDC_CHECK_PARAMEQ, m_kCheckParamEQ);
    DDX_Control(pDX, IDC_BUTTON_SAVE, m_kSaveButton);
    DDX_Control(pDX, IDC_BUTTON_STOP, m_kStopButton);
    DDX_Control(pDX, IDC_BUTTON_LOAD, m_kLoadButton);
    DDX_Control(pDX, IDC_CHECK_DISTORTION, m_kCheckDistortion);
}

BOOL CAudioFXDesignerDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    CoInitialize(0);
    WindowedException::SetWindow((int)m_hWnd);

    m_kPlayButton.EnableWindow(false);
    m_kStopButton.EnableWindow(false);
    m_kSaveButton.EnableWindow(false);
    DeselectAllEffects(true);
    
    m_kPropSheet.AddPage(&m_kAmpModPage);
    m_kPropSheet.AddPage(&m_kChorusPage);
    m_kPropSheet.AddPage(&m_kCompressorPage);
    m_kPropSheet.AddPage(&m_kDelayPage);
    m_kPropSheet.AddPage(&m_kDistortionPage);
    m_kPropSheet.AddPage(&m_kEnVerbPage);
    m_kPropSheet.AddPage(&m_kFlangerPage);
    m_kPropSheet.AddPage(&m_kParamEQPage);
    m_kPropSheet.AddPage(&m_kReverbPage);
    
    m_kPropSheet.Create(this,WS_CHILD|WS_VISIBLE);
    m_kPropSheet.SetWindowPos(NULL,170,3,0,0,SWP_NOSIZE|SWP_NOZORDER);
    
    AudioFormat kFormat;
    kFormat.iSampleRate = 22050;
    kFormat.iChannels = 2;
    kFormat.iBytesPerSample = 2;
    kFormat.b3D = false;

    ms_spkSoundRenderer = new DxSoundRenderer;
    
    try
    {
        ms_spkSoundRenderer->Initialize((int)m_hWnd,&kFormat);
    }
    catch (AudioException* pkAudEx)
    {
        ms_spkSoundRenderer = NULL;
        pkAudEx->Show();
        delete pkAudEx;
        EndDialog(-1);
    }

    return TRUE;
}

///////////////////////////////////////////////////////////

void CAudioFXDesignerDlg::DeselectAllEffects(bool bDisable)
{
    m_kCheckAmpMod.SetCheck(BST_UNCHECKED);    
    m_kCheckAmpMod.EnableWindow(!bDisable);
    m_kCheckChorus.SetCheck(BST_UNCHECKED);    
    m_kCheckChorus.EnableWindow(!bDisable);
    m_kCheckCompressor.SetCheck(BST_UNCHECKED);    
    m_kCheckCompressor.EnableWindow(!bDisable);
    m_kCheckDelay.SetCheck(BST_UNCHECKED);    
    m_kCheckDelay.EnableWindow(!bDisable);
    m_kCheckDistortion.SetCheck(BST_UNCHECKED);    
    m_kCheckDistortion.EnableWindow(!bDisable);
    m_kCheckEnVerb.SetCheck(BST_UNCHECKED);    
    m_kCheckEnVerb.EnableWindow(!bDisable);
    m_kCheckFlanger.SetCheck(BST_UNCHECKED);    
    m_kCheckFlanger.EnableWindow(!bDisable);
    m_kCheckParamEQ.SetCheck(BST_UNCHECKED);    
    m_kCheckParamEQ.EnableWindow(!bDisable);
    m_kCheckReverb.SetCheck(BST_UNCHECKED);    
    m_kCheckReverb.EnableWindow(!bDisable);
}

///////////////////////////////////////////////////////////

void CAudioFXDesignerDlg::GetCurrentEffectSettings ()
{
    GetAmpModSettings();
    GetChorusSettings();
    GetCompressorSettings();
    GetDelaySettings();
    GetDistortionSettings();
    GetEnVerbSettings();
    GetFlangerSettings();
    GetParamEQSettings();
    GetReverbSettings();
}

void CAudioFXDesignerDlg::GetAmpModSettings ()
{
    if ( m_kCheckAmpMod.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::AMPMOD);
        return;
    }

    AmpModEffect* pkAmpMod = 
        (AmpModEffect*)m_spkAudio->GetEffect(AudioEffect::AMPMOD);

    if ( pkAmpMod == NULL )
    {
        pkAmpMod = new AmpModEffect;
        m_spkAudio->SetEffect(pkAmpMod);   
    }  
    
    pkAmpMod->SetFrequency(m_kAmpModPage.GetFrequency());
    pkAmpMod->SetWaveform(m_kAmpModPage.GetWaveform());
}

void CAudioFXDesignerDlg::GetChorusSettings ()
{
    if ( m_kCheckChorus.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::CHORUS);
        return;
    }

    ChorusEffect* pkChorus = 
        (ChorusEffect*)m_spkAudio->GetEffect(AudioEffect::CHORUS);

    if ( pkChorus == NULL )
    {
        pkChorus = new ChorusEffect;
        m_spkAudio->SetEffect(pkChorus);   
    }  

    pkChorus->SetMix(m_kChorusPage.GetMix());
    pkChorus->SetFeedback(m_kChorusPage.GetFeedback());
    pkChorus->SetDelay(m_kChorusPage.GetDelay());
    pkChorus->SetDepth(m_kChorusPage.GetDepth());
    pkChorus->SetFrequency(m_kChorusPage.GetFrequency());
    pkChorus->SetPhase(m_kChorusPage.GetPhase());
    pkChorus->SetWaveform(m_kChorusPage.GetWaveform());
}

void CAudioFXDesignerDlg::GetCompressorSettings ()
{
    if ( m_kCheckCompressor.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::COMPRESSOR);
        return;
    }

    CompressorEffect* pkCompressor = 
        (CompressorEffect*)m_spkAudio->GetEffect(AudioEffect::COMPRESSOR);

    if ( pkCompressor == NULL )
    {
        pkCompressor = new CompressorEffect;
        m_spkAudio->SetEffect(pkCompressor);   
    }

    pkCompressor->SetGain(m_kCompressorPage.GetGain());
    pkCompressor->SetRatio(m_kCompressorPage.GetRatio());
    pkCompressor->SetAttack(m_kCompressorPage.GetAttack());
    pkCompressor->SetRelease(m_kCompressorPage.GetRelease());
    pkCompressor->SetDelay(m_kCompressorPage.GetDelay());
    pkCompressor->SetThreshold(m_kCompressorPage.GetThreshold());
}

void CAudioFXDesignerDlg::GetDelaySettings ()
{
    if ( m_kCheckDelay.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::DELAY);
        return;
    }

    DelayEffect* pkDelay = 
        (DelayEffect*)m_spkAudio->GetEffect(AudioEffect::DELAY);

    if ( pkDelay == NULL )
    {
        pkDelay = new DelayEffect;
        m_spkAudio->SetEffect(pkDelay);   
    }
      
    pkDelay->SetMix(m_kDelayPage.GetMix()); 
    pkDelay->SetFeedback(m_kDelayPage.GetFeedback());
    pkDelay->SetRightDelay(m_kDelayPage.GetRightDelay());
    pkDelay->SetLeftDelay(m_kDelayPage.GetLeftDelay());
    pkDelay->SetPan(m_kDelayPage.GetPan());
}

void CAudioFXDesignerDlg::GetDistortionSettings ()
{
    if ( m_kCheckDistortion.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::DISTORTION);
        return;
    }

    DistortionEffect* pkDistortion = 
        (DistortionEffect*)m_spkAudio->GetEffect(AudioEffect::DISTORTION);

    if ( pkDistortion == NULL )
    {
        pkDistortion = new DistortionEffect;
        m_spkAudio->SetEffect(pkDistortion);   
    }
      
    pkDistortion->SetGain(m_kDistortionPage.GetGain());
    pkDistortion->SetIntensity(m_kDistortionPage.GetIntensity());
    pkDistortion->SetCenter(m_kDistortionPage.GetCenter());
    pkDistortion->SetBandwidth(m_kDistortionPage.GetBandwidth());
    pkDistortion->SetCutoff(m_kDistortionPage.GetCutoff());
}

void CAudioFXDesignerDlg::GetEnVerbSettings ()
{
    if ( m_kCheckEnVerb.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::ENVERB);
        return;
    }

    EnVerbEffect* pkEnVerb = 
        (EnVerbEffect*)m_spkAudio->GetEffect(AudioEffect::ENVERB);

    if ( pkEnVerb == NULL )
    {
        pkEnVerb = new EnVerbEffect;
        m_spkAudio->SetEffect(pkEnVerb);   
    }  

    if ( m_kEnVerbPage.GetPreset() != EnVerbEffect::NONE )
    {
        pkEnVerb->SetPreset(m_kEnVerbPage.GetPreset());
        return;
    }

    pkEnVerb->SetRoomAtten(m_kEnVerbPage.GetRoomAtten());
    pkEnVerb->SetRoomHFAtten(m_kEnVerbPage.GetHFAtten());
    pkEnVerb->SetReflectAtten(m_kEnVerbPage.GetReflectAtten());
    pkEnVerb->SetReverbAtten(m_kEnVerbPage.GetReverbAtten());
    pkEnVerb->SetDecayTime(m_kEnVerbPage.GetDecayTime());
    pkEnVerb->SetDecayTimeHFRatio(m_kEnVerbPage.GetDecayTimeHFRatio());
    pkEnVerb->SetReflectDelay(m_kEnVerbPage.GetReflectDelay());
    pkEnVerb->SetReverbDelay(m_kEnVerbPage.GetReverbDelay());
    pkEnVerb->SetRolloff(m_kEnVerbPage.GetRolloff());
    pkEnVerb->SetDiffusion(m_kEnVerbPage.GetDiffusion());
    pkEnVerb->SetDensity(m_kEnVerbPage.GetDensity());
    pkEnVerb->SetHFRef(m_kEnVerbPage.GetHFRef());
}

void CAudioFXDesignerDlg::GetFlangerSettings ()
{
    if ( m_kCheckFlanger.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::FLANGER);
        return;
    }

    FlangerEffect* pkFlanger = 
       (FlangerEffect*)m_spkAudio->GetEffect(AudioEffect::FLANGER);

    if ( pkFlanger == NULL )
    {
        pkFlanger = new FlangerEffect;
        m_spkAudio->SetEffect(pkFlanger);   
    }  

    pkFlanger->SetMix(m_kFlangerPage.GetMix());
    pkFlanger->SetFeedback(m_kFlangerPage.GetFeedback());
    pkFlanger->SetDelay(m_kFlangerPage.GetDelay());
    pkFlanger->SetDepth(m_kFlangerPage.GetDepth());
    pkFlanger->SetFrequency(m_kFlangerPage.GetFrequency());
    pkFlanger->SetPhase(m_kFlangerPage.GetPhase());
    pkFlanger->SetWaveform(m_kFlangerPage.GetWaveform());
}

void CAudioFXDesignerDlg::GetParamEQSettings ()
{
    if ( m_kCheckParamEQ.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::PARAMEQ);
        return;
    }

    ParametricEqEffect* pkParamEq = 
        (ParametricEqEffect*)m_spkAudio->GetEffect(AudioEffect::PARAMEQ);

    if ( pkParamEq == NULL )
    {
        pkParamEq = new ParametricEqEffect;
        m_spkAudio->SetEffect(pkParamEq);   
    }   

    pkParamEq->SetGain(m_kParamEQPage.GetGain());
    pkParamEq->SetCenter(m_kParamEQPage.GetCenter());
    pkParamEq->SetBandwidth(m_kParamEQPage.GetBandwidth());
}

void CAudioFXDesignerDlg::GetReverbSettings ()
{
    if ( m_kCheckReverb.GetCheck() != BST_CHECKED )
    {
        m_spkAudio->RemoveEffect(AudioEffect::REVERB);
        return;
    }

    ReverbEffect* pkReverb = 
        (ReverbEffect*)m_spkAudio->GetEffect(AudioEffect::REVERB);

    if ( pkReverb == NULL )
    {
        pkReverb = new ReverbEffect;
        m_spkAudio->SetEffect(pkReverb);   
    }  

    pkReverb->SetMix(m_kReverbPage.GetMix());
    pkReverb->SetInputGain(m_kReverbPage.GetGain());
    pkReverb->SetTime(m_kReverbPage.GetTime());
    pkReverb->SetHFRatio(m_kReverbPage.GetHFRatio());
}

///////////////////////////////////////////////////////////

void CAudioFXDesignerDlg::OnCancel()
{
    DestroyWindow();
}

void CAudioFXDesignerDlg::OnIdle ()
{
    if ( m_spkAudio != NULL )
    {
        if ( !ms_spkSoundRenderer->IsPlaying(m_spkAudio) &&
            m_kStopButton.IsWindowEnabled() )
        {
            UpdateUIOnStop();
        }
    }
}

void CAudioFXDesignerDlg::OnOK()
{
    DestroyWindow();
}

void CAudioFXDesignerDlg::PostNcDestroy()
{
    CDialog::PostNcDestroy();

    ms_spkSoundRenderer = NULL;    
    m_spkAudio = NULL;

    CoUninitialize();
    PostQuitMessage(0);
}

///////////////////////////////////////////////////////////

void CAudioFXDesignerDlg::SaveEffectParams (FILE*pkFile, AmpModEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_AMPMOD);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_FREQ);
    fwprintf(pkFile,L"%s = %d Hz\n", (LPCTSTR)strText,pkEffect->GetFrequency());
    strText.LoadString(IDS_TEXT_WAVEFORM);
    fwprintf(pkFile,L"%s = ", (LPCTSTR)strText);
    switch( pkEffect->GetWaveform() )
    {
    case AmpModEffect::TRIANGLE:
        strText.LoadString(IDS_TEXT_TRIANGLE);
        break;
    case AmpModEffect::SQUARE:
        strText.LoadString(IDS_TEXT_SQUARE);
        break;
    }
    fwprintf(pkFile,L"%s\n\n", (LPCTSTR)strText);
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, ChorusEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_CHORUS);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_MIX);
    fwprintf(pkFile,L"%s = %.0f\n", (LPCTSTR)strText,pkEffect->GetMix());
    strText.LoadString(IDS_TEXT_DEPTH);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetDepth());
    strText.LoadString(IDS_TEXT_DELAY);
    fwprintf(pkFile,L"%s = %.1f ms\n", (LPCTSTR)strText,pkEffect->GetDelay());
    strText.LoadString(IDS_TEXT_FREQ);
    fwprintf(pkFile,L"%s = %.1f Hz\n", (LPCTSTR)strText,pkEffect->GetFrequency());
    strText.LoadString(IDS_TEXT_FEEDBACK);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetFeedback());

    strText.LoadString(IDS_TEXT_WAVEFORM);
    fwprintf(pkFile,L"%s = ", (LPCTSTR)strText);
    switch ( pkEffect->GetWaveform() )
    {
    case ChorusEffect::SINE:
        strText.LoadString(IDS_TEXT_SINE);
        break;
    case ChorusEffect::TRIANGLE:
        strText.LoadString(IDS_TEXT_TRIANGLE);
        break;
    }
    fwprintf(pkFile,L"%s\n", (LPCTSTR)strText);
    
    strText.LoadString(IDS_TEXT_PHASE);
    fwprintf(pkFile,L"%s = ", (LPCTSTR)strText);

    switch ( pkEffect->GetPhase() )
    {
    case ChorusEffect::NEG_180:
        strText.Format(L"%d",-180);
        break;
    case ChorusEffect::NEG_90:
        strText.Format(L"%d",-90);
        break;
    case ChorusEffect::ZERO:
        strText.Format(L"%d",0);
        break;
    case ChorusEffect::POS_90:
        strText.Format(L"%d",90);
        break;
    case ChorusEffect::POS_180:
        strText.Format(L"%d",180);
        break;
    }
    fwprintf(pkFile,L"%s", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_DEGREES);
    fwprintf(pkFile,L" %s\n\n", (LPCTSTR)strText);
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, CompressorEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_COMPRESSOR);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);
    
    strText.LoadString(IDS_TEXT_GAIN);
    fwprintf(pkFile,L"%s = %.0f dB\n", (LPCTSTR)strText,pkEffect->GetGain());
    strText.LoadString(IDS_TEXT_RATIO);
    fwprintf(pkFile,L"%s = %.0f\n", (LPCTSTR)strText,pkEffect->GetRatio());
    strText.LoadString(IDS_TEXT_ATTACK);
    fwprintf(pkFile,L"%s = %.1f ms\n", (LPCTSTR)strText,pkEffect->GetAttack());
    strText.LoadString(IDS_TEXT_RELEASE);
    fwprintf(pkFile,L"%s = %.0f ms\n", (LPCTSTR)strText,pkEffect->GetRelease());
    strText.LoadString(IDS_TEXT_DELAY);
    fwprintf(pkFile,L"%s = %.1f ms\n", (LPCTSTR)strText,pkEffect->GetDelay());
    strText.LoadString(IDS_TEXT_THRESHOLD);
    fwprintf(pkFile,L"%s = %.0f dB\n\n", (LPCTSTR)strText,pkEffect->GetThreshold());
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, DelayEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_DELAY);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_FEEDBACK);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetFeedback());
    strText.LoadString(IDS_TEXT_LEFTDELAY);
    fwprintf(pkFile,L"%s = %.0f ms\n", (LPCTSTR)strText,pkEffect->GetLeftDelay());
    strText.LoadString(IDS_TEXT_RIGHTDELAY);
    fwprintf(pkFile,L"%s = %.0f ms\n", (LPCTSTR)strText,pkEffect->GetRightDelay());
    strText.LoadString(IDS_TEXT_PAN);
    fwprintf(pkFile,L"%s = %d\n\n", (LPCTSTR)strText,pkEffect->GetPan());
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, DistortionEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_DISTORTION);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);

    strText.LoadString(IDS_TEXT_GAIN);
    fwprintf(pkFile,L"%s = %.0f dB\n", (LPCTSTR)strText,pkEffect->GetGain());
    strText.LoadString(IDS_TEXT_INTENSITY);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetIntensity());
    strText.LoadString(IDS_TEXT_CENTER);
    fwprintf(pkFile,L"%s = %.0f Hz\n", (LPCTSTR)strText,pkEffect->GetCenter());
    strText.LoadString(IDS_TEXT_BANDWIDTH);
    fwprintf(pkFile,L"%s = %.0f Hz\n", (LPCTSTR)strText,pkEffect->GetBandwidth());
    strText.LoadString(IDS_TEXT_CUTOFF);
    fwprintf(pkFile,L"%s = %.0f Hz\n\n", (LPCTSTR)strText,pkEffect->GetCutoff());
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, FlangerEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_FLANGER);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_MIX);
    fwprintf(pkFile,L"%s = %.0f\n", (LPCTSTR)strText,pkEffect->GetMix());
    strText.LoadString(IDS_TEXT_DEPTH);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetDepth());
    strText.LoadString(IDS_TEXT_DELAY);
    fwprintf(pkFile,L"%s = %.1f ms\n", (LPCTSTR)strText,pkEffect->GetDelay());
    strText.LoadString(IDS_TEXT_FREQ);
    fwprintf(pkFile,L"%s = %.1f Hz\n", (LPCTSTR)strText,pkEffect->GetFrequency());
    strText.LoadString(IDS_TEXT_FEEDBACK);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetFeedback());

    strText.LoadString(IDS_TEXT_WAVEFORM);
    fwprintf(pkFile,L"%s = ", (LPCTSTR)strText);
    switch ( pkEffect->GetWaveform() )
    {
    case FlangerEffect::SINE:
        strText.LoadString(IDS_TEXT_SINE);
        break;
    case FlangerEffect::TRIANGLE:
        strText.LoadString(IDS_TEXT_TRIANGLE);
        break;
    }
    fwprintf(pkFile,L"%s\n", (LPCTSTR)strText);
    
    strText.LoadString(IDS_TEXT_PHASE);
    fwprintf(pkFile,L"%s = ", (LPCTSTR)strText);

    switch ( pkEffect->GetPhase() )
    {
    case FlangerEffect::NEG_180:
        strText.Format(L"%d",-180);
        break;
    case FlangerEffect::NEG_90:
        strText.Format(L"%d",-90);
        break;
    case FlangerEffect::ZERO:
        strText.Format(L"%d",0);
        break;
    case FlangerEffect::POS_90:
        strText.Format(L"%d",90);
        break;
    case FlangerEffect::POS_180:
        strText.Format(L"%d",180);
        break;
    }
    fwprintf(pkFile,L"%s", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_DEGREES);
    fwprintf(pkFile,L" %s\n\n", (LPCTSTR)strText);
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, ParametricEqEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_PARAMEQ);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);

    strText.LoadString(IDS_TEXT_GAIN);
    fwprintf(pkFile,L"%s = %.0f dB\n", (LPCTSTR)strText,pkEffect->GetGain());
    strText.LoadString(IDS_TEXT_CENTER);
    fwprintf(pkFile,L"%s = %.0f Hz\n", (LPCTSTR)strText,pkEffect->GetCenter());
    strText.LoadString(IDS_TEXT_BANDWIDTH);
    fwprintf(pkFile,L"%s = %.0f ", (LPCTSTR)strText,pkEffect->GetBandwidth());
    strText.LoadString(IDS_TEXT_SEMITONES);
    fwprintf(pkFile,L"%s\n\n", (LPCTSTR)strText);
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, EnVerbEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_ENVERB);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);

    if ( pkEffect->GetPreset() != EnVerbEffect::NONE )
    {
        strText.LoadString(IDS_TEXT_PRESET);
        fwprintf(pkFile,L"%s = ", (LPCTSTR)strText);
        m_kEnVerbPage.GetPresetString(strText, pkEffect->GetPreset());
        fwprintf(pkFile,L"%s\n\n", (LPCTSTR)strText);
        return;
    }

    strText.LoadString(IDS_TEXT_ROOMATTEN);
    fwprintf(pkFile,L"%s = %ld mB\n", (LPCTSTR)strText,pkEffect->GetRoomAtten());
    strText.LoadString(IDS_TEXT_HFATTEN);
    fwprintf(pkFile,L"%s = %ld mB\n", (LPCTSTR)strText,pkEffect->GetRoomHFAtten());
    strText.LoadString(IDS_TEXT_REFLECTATTEN);
    fwprintf(pkFile,L"%s = %ld mB\n", (LPCTSTR)strText,pkEffect->GetReflectAtten());
    strText.LoadString(IDS_TEXT_REVERBATTEN);
    fwprintf(pkFile,L"%s = %ld mB\n", (LPCTSTR)strText,pkEffect->GetReverbAtten());
    strText.LoadString(IDS_TEXT_REFLECTDELAY);
    fwprintf(pkFile,L"%s = %.2f s\n", (LPCTSTR)strText,pkEffect->GetReflectDelay());
    strText.LoadString(IDS_TEXT_REVERBDELAY);
    fwprintf(pkFile,L"%s = %.2f s\n", (LPCTSTR)strText,pkEffect->GetReverbDelay());
    strText.LoadString(IDS_TEXT_DECAY);
    fwprintf(pkFile,L"%s = %.1f s\n", (LPCTSTR)strText,pkEffect->GetDecayTime());
    strText.LoadString(IDS_TEXT_DECAYHFRATIO);
    fwprintf(pkFile,L"%s = %.1f\n", (LPCTSTR)strText,pkEffect->GetDecayTimeHFRatio());
    strText.LoadString(IDS_TEXT_ROLLOFF);
    fwprintf(pkFile,L"%s = %.1f\n", (LPCTSTR)strText,pkEffect->GetRolloff());
    strText.LoadString(IDS_TEXT_DIFFUSION);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetDiffusion());
    strText.LoadString(IDS_TEXT_DENSITY);
    fwprintf(pkFile,L"%s = %.0f %%\n", (LPCTSTR)strText,pkEffect->GetDensity());
    strText.LoadString(IDS_TEXT_HFREF);
    fwprintf(pkFile,L"%s = %.1f Hz\n\n", (LPCTSTR)strText,pkEffect->GetHFRef());
}

void CAudioFXDesignerDlg::SaveEffectParams (FILE* pkFile, ReverbEffect* pkEffect)
{
    CString strText;
    strText.LoadString(IDS_TEXT_STDREVERB);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);

    strText.LoadString(IDS_TEXT_MIX);
    fwprintf(pkFile,L"%s = %.0f dB\n", (LPCTSTR)strText,pkEffect->GetMix());
    strText.LoadString(IDS_TEXT_TIME);
    fwprintf(pkFile,L"%s = %.2f ms\n", (LPCTSTR)strText,pkEffect->GetTime());
    strText.LoadString(IDS_TEXT_GAIN);
    fwprintf(pkFile,L"%s = %.0f dB\n", (LPCTSTR)strText,pkEffect->GetInputGain());
    strText.LoadString(IDS_TEXT_HFRATIO);
    fwprintf(pkFile,L"%s = %.3f\n\n", (LPCTSTR)strText,pkEffect->GetHFRatio());
}

///////////////////////////////////////////////////////////

void CAudioFXDesignerDlg::UpdateUIOnPlay()
{
    m_kPlayButton.EnableWindow(FALSE);
    m_kStopButton.EnableWindow(TRUE);
    m_kSaveButton.EnableWindow(FALSE);
    m_kLoadButton.EnableWindow(FALSE);
}

void CAudioFXDesignerDlg::UpdateUIOnStop()
{
    m_kPlayButton.EnableWindow(TRUE);
    m_kStopButton.EnableWindow(FALSE);
    m_kSaveButton.EnableWindow(TRUE);
    m_kLoadButton.EnableWindow(TRUE);
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CAudioFXDesignerDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_LOAD, OnBnClickedButtonLoad)
    ON_BN_CLICKED(IDC_BUTTON_PLAY, OnBnClickedButtonPlay)
    ON_BN_CLICKED(IDC_CHECK_FLANGER, OnBnClickedCheckFlanger)
    ON_BN_CLICKED(IDC_CHECK_DELAY, OnBnClickedCheckDelay)
    ON_BN_CLICKED(IDC_CHECK_CHORUS, OnBnClickedCheckChorus)
    ON_BN_CLICKED(IDC_CHECK_REVERB, OnBnClickedCheckReverb)
    ON_BN_CLICKED(IDC_CHECK_COMPRESSOR, OnBnClickedCheckCompressor)
    ON_BN_CLICKED(IDC_CHECK_ENVERB, OnBnClickedCheckEnVerb)
    ON_BN_CLICKED(IDC_CHECK_AMPMOD, OnBnClickedCheckAmpMod)
    ON_BN_CLICKED(IDC_CHECK_PARAMEQ, OnBnClickedCheckParamEq)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnBnClickedButtonStop)
    ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
    ON_BN_CLICKED(IDC_CHECK_DISTORTION, OnBnClickedCheckDistortion)
    ON_WM_CLOSE()
END_MESSAGE_MAP()

void CAudioFXDesignerDlg::OnBnClickedCheckAmpMod()
{
    if ( m_kCheckAmpMod.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kAmpModPage);     
}

void CAudioFXDesignerDlg::OnBnClickedCheckChorus()
{
    if ( m_kCheckChorus.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kChorusPage);     
}

void CAudioFXDesignerDlg::OnBnClickedCheckCompressor()
{
    if ( m_kCheckCompressor.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kCompressorPage); 
}

void CAudioFXDesignerDlg::OnBnClickedCheckDelay()
{
    if ( m_kCheckDelay.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kDelayPage);
}

void CAudioFXDesignerDlg::OnBnClickedCheckDistortion()
{
    if ( m_kCheckDistortion.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kDistortionPage); 
}

void CAudioFXDesignerDlg::OnBnClickedCheckEnVerb()
{
    if ( m_kCheckEnVerb.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kEnVerbPage);     
}

void CAudioFXDesignerDlg::OnBnClickedCheckFlanger()
{
    if ( m_kCheckFlanger.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kFlangerPage);
}

void CAudioFXDesignerDlg::OnBnClickedCheckParamEq()
{
    if ( m_kCheckParamEQ.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kParamEQPage);    
}

void CAudioFXDesignerDlg::OnBnClickedCheckReverb()
{
    if ( m_kCheckReverb.GetCheck() == BST_CHECKED )
        m_kPropSheet.SetActivePage(&m_kReverbPage);     
}

void CAudioFXDesignerDlg::OnBnClickedButtonLoad()
{
    try
    {
        if ( m_spkAudio != NULL )
        {
            ms_spkSoundRenderer->Unload(m_spkAudio);
            m_spkAudio = NULL;
        }
    }
    catch (AudioException* pkAudEx)
    {
        pkAudEx->Show();
        delete pkAudEx;
        return;
    }

    CFileDialog kFileOpen(TRUE,L"maf",NULL,OFN_EXPLORER | OFN_FILEMUSTEXIST,
        L"Magic Audio Files (*.maf)|*.maf||",this); 
    
    if ( kFileOpen.DoModal() == IDCANCEL )
    return;

    CString strFile = kFileOpen.GetPathName();
    m_spkAudio = new Sound1D;
    m_spkAudio->SetName((LPCTSTR)strFile);

    try
    {
        ms_spkSoundRenderer->Load((Sound1D*)(Audio*)m_spkAudio);
    }
    catch (AudioException* pkAudEx)
    {
        delete pkAudEx;
        m_spkAudio = NULL;
    }
 
    if ( m_spkAudio == NULL )
    {
        m_spkAudio = new Sound2D;
        m_spkAudio->SetName(strFile);

        try
        {
            ms_spkSoundRenderer->Load((Sound2D*)(Audio*)m_spkAudio);    
        }
        catch (AudioException* pkAudEx)
        {
            delete pkAudEx;
            m_spkAudio = NULL;
        }
    }

    m_kPlayButton.EnableWindow(TRUE);
    m_kSaveButton.EnableWindow(TRUE); 
    DeselectAllEffects(false);
}

void CAudioFXDesignerDlg::OnBnClickedButtonPlay()
{
    if ( m_spkAudio == NULL )
        return;

    GetCurrentEffectSettings();

    try
    {
        ms_spkSoundRenderer->UpdateEffects(m_spkAudio);
        ms_spkSoundRenderer->Play(m_spkAudio);
    }
    catch (AudioException* pkAudEx)
    {
        pkAudEx->Show();
        delete pkAudEx;
    }
    
    UpdateUIOnPlay();
}

void CAudioFXDesignerDlg::OnBnClickedButtonSave()
{
    GetCurrentEffectSettings();

    if ( m_spkAudio->GetEffectQuantity() == 0 )
    {
        AfxMessageBox(IDS_ERR_NOEFFECTSELECTED,MB_OK | MB_ICONINFORMATION);   
        return;
    }

    CFileDialog kFileSave(FALSE,L"txt",NULL,OFN_EXPLORER | OFN_OVERWRITEPROMPT,
        L"Text Files (*.txt)|*.txt||",this);
    if ( kFileSave.DoModal() == IDCANCEL )
        return;

    CString strSaveFile = kFileSave.GetPathName();
    FILE* pkFile = _wfopen(strSaveFile,L"wt");
    if ( pkFile == NULL )
        AfxMessageBox(IDS_ERR_CREATEFILE,MB_OK | MB_ICONEXCLAMATION);   

    CString strText;
    strText.LoadString(IDS_TEXT_HEADER);
    fwprintf(pkFile,L"[%s]\n", (LPCTSTR)strText);
    strText.LoadString(IDS_TEXT_FILE);
    fwprintf(pkFile,L"%s = %s\n", (LPCTSTR)strText,m_spkAudio->GetName());
    strText.LoadString(IDS_TEXT_NUMEFFECTS);
    fwprintf(pkFile,L"%s =  %d\n\n", (LPCTSTR)strText,m_spkAudio->GetEffectQuantity());
    
    AudioEffect* pkEffect;

    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::AMPMOD)) != NULL )
        SaveEffectParams(pkFile, (AmpModEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::CHORUS)) != NULL )
        SaveEffectParams(pkFile, (ChorusEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::COMPRESSOR)) != NULL )
        SaveEffectParams(pkFile, (CompressorEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::DELAY)) != NULL )
        SaveEffectParams(pkFile, (DelayEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::DISTORTION)) != NULL )
        SaveEffectParams(pkFile, (DistortionEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::ENVERB)) != NULL )
        SaveEffectParams(pkFile, (EnVerbEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::FLANGER)) != NULL )
        SaveEffectParams(pkFile, (FlangerEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::PARAMEQ)) != NULL )
        SaveEffectParams(pkFile, (ParametricEqEffect*)pkEffect);
    if ( (pkEffect = m_spkAudio->GetEffect(AudioEffect::REVERB)) != NULL )
        SaveEffectParams(pkFile, (ReverbEffect*)pkEffect);
        
    fclose(pkFile);
}

void CAudioFXDesignerDlg::OnBnClickedButtonStop()
{
    ms_spkSoundRenderer->Stop(m_spkAudio);
    UpdateUIOnStop();
}

void CAudioFXDesignerDlg::OnClose()
{
    DestroyWindow();
}

void CAudioFXDesignerDlg::OnPaint() 
{
    if (IsIconic())
    {
        CPaintDC dc(this); 
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

HCURSOR CAudioFXDesignerDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
