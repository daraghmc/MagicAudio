#ifndef MADXAUDIOUTIL_H
#define MADXAUDIOUTIL_H

#include "MAAudioException.h"
#include "MADXAudioErr.h"
#include "MADXError.h"

#define MA_DXAUDIO_WARN(hr) MA_DX_WARN(AudioException,hr)
#define MA_DXAUDIO_ERR(hr) MA_DX_ERR(AudioException,hr)
#define MA_DXAUDIO_ERR_MSG(acMsg) MA_THROW_ERR(AudioException,acMsg)
#define MA_DXAUDIO_WARN_MSG(acMsg) MA_THROW_WARN(AudioException,acMsg)

extern wchar_t* MAMakeWideString(const char* acString);

#endif // MADXAUDIOUTIL_H

