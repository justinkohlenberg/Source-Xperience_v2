#include <tchar.h>

#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")

#include "SXApplication.h"

using namespace source_xperience;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE h0, LPTSTR lpCmdLine, int nCmdShow) {
	///Create Dialog as main window and show it
	SXApplication app(hInst);

	app.InitialiseApp();

	app.RunApp();

	return 0;
}