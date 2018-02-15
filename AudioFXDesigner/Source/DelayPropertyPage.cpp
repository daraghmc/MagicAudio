#include "stdafx.h"
#include "AudioFXDesigner.h"
#include "DelayPropertyPage.h"

using namespace MagicAudio;

IMPLEMENT_DYNAMIC(CDelayPropertyPage, CPropertyPage)
CDelayPropertyPage::CDelayPropertyPage()
    : CPropertyPage(CDelayPropertyPage::IDD)
{
}

CDelayPropertyPage::~CDelayPropertyPage()
{
}

void CDelayPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_SLIDER_DELAY_MIX, m_kMixSlider);
    DDX_Control(pDX, IDC_SLIDER_DELAY_FEEDBACK, m_kFeedbackSlider);
    DDX_Control(pDX, IDC_SLIDER_DELAY_LEFTDELAY, m_kLeftDelaySlider);
    DDX_Control(pDX, IDC_SLIDER_DELAY_RIGHTDELAY, m_kRightDelaySlider);
    DDX_Control(pDX, IDC_CHECK_DELAY_PAN, m_kCheckPan);

    DDX_Control(pDX, IDC_STATIC_DELAY_MIX, m_kMixDisplay);
    DDX_Control(pDX, IDC_STATIC_DELAY_FEEDBACK, m_kFeedbackDisplay);
    DDX_Control(pDX, IDC_STATIC_DELAY_LEFTDELAY, m_kLeftDelayDisplay);
    DDX_Control(pDX, IDC_STATIC_DELAY_RIGHTDELAY, m_kRightDelayDisplay);
}

BOOL CDelayPropertyPage::OnInitDialog()
{
    CPropertyPage::OnInitDialog();

    int iMin, iMax;
    CString strValue;

    m_kMixSlider.SetRange((int)DelayEffect::MIN_MIX,
        (int)DelayEffect::MAX_MIX,TRUE);
    m_kMixSlider.GetRange(iMin,iMax);
    m_kMixSlider.SetTicFreq((iMax-iMin)/10);
    m_kMixSlider.SetPos(50);
    strValue.Format(L"%d",50);
    m_kMixDisplay.SetWindowText(strValue);
   
    m_kFeedbackSlider.SetRange((int)DelayEffect::MIN_FEEDBACK,
        (int)DelayEffect::MAX_FEEDBACK,TRUE);   
    m_kFeedbackSlider.GetRange(iMin,iMax);    
    m_kFeedbackSlider.SetTicFreq((iMax-iMin)/10);
    m_kFeedbackSlider.SetPos(50);
    strValue.Format(L"%d",50);
    m_kFeedbackDisplay.SetWindowText(strValue);

    m_kLeftDelaySlider.SetRange((int)DelayEffect::MIN_DELAY,
        (int)DelayEffect::MAX_DELAY,TRUE);
    m_kLeftDelaySlider.GetRange(iMin,iMax);    
    m_kLeftDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kLeftDelaySlider.SetPos(500);
    strValue.Format(L"%d",500);
    m_kLeftDelayDisplay.SetWindowText(strValue);

    m_kRightDelaySlider.SetRange((int)DelayEffect::MIN_DELAY,
        (int)DelayEffect::MAX_DELAY,TRUE);
    m_kRightDelaySlider.GetRange(iMin,iMax);
    m_kRightDelaySlider.SetTicFreq((iMax-iMin)/10);
    m_kRightDelaySlider.SetPos(500);
    strValue.Format(L"%d",500);
    m_kRightDelayDisplay.SetWindowText(strValue);

    return TRUE;  
}

///////////////////////////////////////////////////////////

float CDelayPropertyPage::GetMix ()
{
    return (float)m_kMixSlider.GetPos();
}

float CDelayPropertyPage::GetFeedback ()
{
    return (float)m_kFeedbackSlider.GetPos();
}

float CDelayPropertyPage::GetLeftDelay ()
{
    return (float)m_kLeftDelaySlider.GetPos();
}

float CDelayPropertyPage::GetRightDelay ()
{
    return (float)m_kRightDelaySlider.GetPos();
}

bool CDelayPropertyPage::GetPan ()
{
    if ( m_kCheckPan.GetCheck() == BST_CHECKED )
        return true;

    return false;
}

///////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDelayPropertyPage, CPropertyPage)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()

void CDelayPropertyPage::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pkSlider = (CSliderCtrl*)pScrollBar;
    CString strValue;

    if ( pkSlider->m_hWnd == m_kMixSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kMixSlider.GetPos());
        m_kMixDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kFeedbackSlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kFeedbackSlider.GetPos());
        m_kFeedbackDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kLeftDelaySlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kLeftDelaySlider.GetPos());
        m_kLeftDelayDisplay.SetWindowText(strValue);
    }
    else if ( pkSlider->m_hWnd == m_kRightDelaySlider.m_hWnd )
    {
        strValue.Format(L"%d",m_kRightDelaySlider.GetPos());
        m_kRightDelayDisplay.SetWindowText(strValue);
    }
 
    CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}