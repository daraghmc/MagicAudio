#include <windows.h>
#include <string>
#include <vector>
using namespace std;

#include "WavToMafException.h"
#include "WavToMafDialog.h"

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(NULL);

	INITCOMMONCONTROLSEX kICC;
	kICC.dwSize = sizeof(INITCOMMONCONTROLSEX);
	kICC.dwICC = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&kICC);

	WindowedException::SetWindow((int)GetDesktopWindow());
    try
    {
        WavToMafDialog kAppDialog;
	    kAppDialog.Show();
    }
    catch ( WavToMafException* pkEx )
    {
        pkEx->Show();
        delete pkEx;
    }

    CoUninitialize();
    return 0;
}



