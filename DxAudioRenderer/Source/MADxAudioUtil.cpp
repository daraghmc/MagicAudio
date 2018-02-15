#include <stdlib.h>

wchar_t* MAMakeWideString(const char* acString)
{
    int iLength = mbstowcs(NULL,acString, 0);
    wchar_t* awcWideString = new wchar_t[iLength + 1];
    mbstowcs(awcWideString,acString,iLength + 1);

    return awcWideString;
}
