#include "MADxSoundRenderer.h"
#include "MADxAudioStream.h"
#include "MADxAudioUtil.h"

using namespace MagicAudio;

DWORD DxSoundRenderer::ms_adw3DMode[] = 
{
    DS3DMODE_NORMAL,
    DS3DMODE_HEADRELATIVE,
    DS3DMODE_DISABLE
};

void DxSoundRenderer::Load (Sound3D* pkSound)
{
    SoundInfo* pkInfo = new SoundInfo;
    
    try
    {
        pkInfo->m_pkStream = new DxAudioStream;
        pkInfo->m_pkStream->Open(pkSound,pkInfo); 
        m_kSoundMap[pkSound->GetID()] = pkInfo;
        SetVolume(pkSound);
        SetAll(pkSound);
    }
    catch( AudioException* pkAudEx)
    {
        delete pkInfo;
        throw pkAudEx;
    }
}

void DxSoundRenderer::SetPosition (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;
    
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    Vector3f kPos = pkSound->GetPosition();
    HRESULT hr = pkInfo->m_pq3DBuffer->SetPosition(kPos.X(),kPos.Y(),kPos.Z(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetConeAngles (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;

    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    HRESULT hr = pkInfo->m_pq3DBuffer->SetConeAngles(pkSound->GetCone().GetInsideAngle(),
        pkSound->GetCone().GetOutsideAngle(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetOrientation (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;

    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    Vector3f kOrient = pkSound->GetCone().GetOrientation();
    HRESULT hr = pkInfo->m_pq3DBuffer->SetConeOrientation(kOrient.X(),kOrient.Y(),
        kOrient.Y(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetOutsideVolume (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;
  
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
 
    HRESULT hr = pkInfo->m_pq3DBuffer->SetConeOutsideVolume((long)
        pkSound->GetCone().GetOutsideVol(), dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetMode (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;
  
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    HRESULT hr = pkInfo->m_pq3DBuffer->SetMode(ms_adw3DMode[pkSound->GetMode()],dwDefer);
    MA_DXAUDIO_WARN(hr);   
}

void DxSoundRenderer::SetVelocity (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;

    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    Vector3f kVel = pkSound->GetVelocity();
    HRESULT hr = pkInfo->m_pq3DBuffer->SetVelocity(kVel.X(),kVel.Z(),kVel.Y(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetVolumeDistances (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;
    
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    HRESULT hr = pkInfo->m_pq3DBuffer->SetMinDistance(pkSound->GetMinVolDist(),dwDefer);
    MA_DXAUDIO_WARN(hr);    
    hr = pkInfo->m_pq3DBuffer->SetMaxDistance(pkSound->GetMaxVolDist(),dwDefer);
    MA_DXAUDIO_WARN(hr);  
}

void DxSoundRenderer::SetAll (Sound3D* pkSound, bool bDefer)
{
    SoundInfo* pkInfo = FindSound(pkSound);
    if ( pkInfo == NULL ) 
        return;
    
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;

    Vector3f kValue;

    DS3DBUFFER k3DBuff;
    k3DBuff.dwSize = sizeof(DS3DBUFFER);

    kValue = pkSound->GetPosition();
    k3DBuff.vPosition.x = kValue.X();
    k3DBuff.vPosition.y = kValue.Y();
    k3DBuff.vPosition.z = kValue.Z();

    kValue = pkSound->GetVelocity();
    k3DBuff.vVelocity.x = kValue.X();
    k3DBuff.vVelocity.y = kValue.Y();
    k3DBuff.vVelocity.z = kValue.Z();

    kValue = pkSound->GetCone().GetOrientation();
    k3DBuff.vConeOrientation.x = kValue.X();
    k3DBuff.vConeOrientation.y = kValue.Y();
    k3DBuff.vConeOrientation.z = kValue.Z();
    k3DBuff.dwInsideConeAngle = pkSound->GetCone().GetInsideAngle();
    k3DBuff.dwOutsideConeAngle = pkSound->GetCone().GetOutsideAngle();
    k3DBuff.lConeOutsideVolume = ScaleVolume(pkSound->GetCone().GetOutsideVol());

    k3DBuff.dwMode = ms_adw3DMode[pkSound->GetMode()];
    k3DBuff.flMaxDistance = pkSound->GetMaxVolDist();
    k3DBuff.flMinDistance = pkSound->GetMinVolDist();

    HRESULT hr = pkInfo->m_pq3DBuffer->SetAllParameters(&k3DBuff,dwDefer);
    MA_DXAUDIO_WARN(hr);
}

//-------------------------------------------------------------------------------

void DxSoundRenderer::SetPosition (Listener3D* pkListener, bool bDefer)
{
    if ( ms_pqListener == NULL )
        return;
    Vector3f kPos = pkListener->GetPosition();
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    HRESULT hr = ms_pqListener->SetPosition(kPos.X(),kPos.Y(),kPos.Z(),dwDefer);
    MA_DXAUDIO_ERR(hr);
}
 
void DxSoundRenderer::SetOrientation (Listener3D* pkListener, bool bDefer)
{
    if( ms_pqListener == NULL ) 
        return;

     Vector3f kFront = pkListener->GetFront();
     Vector3f kTop = pkListener->GetTop();
     DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
     HRESULT hr = ms_pqListener->SetOrientation(kFront.X(),kFront.Y(),kFront.Z(),
         kTop.X(),kTop.Y(),kTop.Z(),dwDefer);
     MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetVelocity (Listener3D* pkListener, bool bDefer)
{
    if ( ms_pqListener == NULL )
        return;

    Vector3f kVel = pkListener->GetVelocity();
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;
    HRESULT hr = ms_pqListener->SetVelocity(kVel.X(),kVel.Y(),kVel.Z(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetDoppler (Listener3D* pkListener, bool bDefer)
{
    if ( ms_pqListener == NULL )
       return;
       
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;   
    HRESULT hr = ms_pqListener->SetDopplerFactor(pkListener->GetDoppler(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetRolloff (Listener3D* pkListener, bool bDefer)
{
    if ( ms_pqListener == NULL )
       return;
       
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;   
    HRESULT hr = ms_pqListener->SetDopplerFactor(pkListener->GetRolloff(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetDistanceScale (Listener3D* pkListener, bool bDefer)
{
    if ( ms_pqListener == NULL )
       return;
       
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;   
    HRESULT hr = ms_pqListener->SetDistanceFactor(pkListener->GetDistanceScale(),dwDefer);
    MA_DXAUDIO_WARN(hr);
}

void DxSoundRenderer::SetAll (Listener3D* pkListener, bool bDefer)
{
    if ( ms_pqListener == NULL )
        return;
    
    DWORD dwDefer = bDefer ? DS3D_DEFERRED : DS3D_IMMEDIATE;   
    Vector3f kVal;
    DS3DLISTENER kD3DListen;
    kD3DListen.dwSize = sizeof(DS3DLISTENER);

    kVal = pkListener->GetPosition();
    kD3DListen.vPosition.x = kVal.X();
    kD3DListen.vPosition.y = kVal.Y();
    kD3DListen.vPosition.z = kVal.Z();

    kVal = pkListener->GetVelocity();
    kD3DListen.vVelocity.x = kVal.X(); 
    kD3DListen.vVelocity.y = kVal.Y();
    kD3DListen.vVelocity.z = kVal.Z();

    kVal = pkListener->GetTop();
    kD3DListen.vOrientTop.x = kVal.X();
    kD3DListen.vOrientTop.y = kVal.Y();
    kD3DListen.vOrientTop.z = kVal.Z();

    kVal = pkListener->GetFront(); 
    kD3DListen.vOrientFront.x = kVal.X();
    kD3DListen.vOrientFront.y = kVal.Y();
    kD3DListen.vOrientFront.z = kVal.Z();

    kD3DListen.flDopplerFactor = pkListener->GetDoppler();
    kD3DListen.flRolloffFactor = pkListener->GetRolloff();
    kD3DListen.flDistanceFactor = pkListener->GetDistanceScale();

    HRESULT hr = ms_pqListener->SetAllParameters(&kD3DListen,dwDefer);
    MA_DXAUDIO_WARN(hr);  
}

void DxSoundRenderer::CommitDeferredSettings()
{
    if( ms_pqListener == NULL ) 
        return;

    HRESULT hr = ms_pqListener->CommitDeferredSettings();
    MA_DXAUDIO_ERR(hr);
}
