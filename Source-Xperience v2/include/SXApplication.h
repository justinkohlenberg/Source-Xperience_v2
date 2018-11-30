#ifndef SXAPPLICATION_H
#define SXAPPLICATION_H

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

#include "resource.h"
#include "config/MockConfig.h"
#include "utility/Helpers.h"
#include "utility/DialogHelpers.h"

// user defines
#define WINDOW_PROP_STRING "sx_application_data"

using namespace std;

namespace source_xperience {
	class SXApplication
	{
	public:
		SXApplication(HINSTANCE hInst);
		~SXApplication();

		///Initialise all data necessary, load configuration and create services
		bool InitialiseApp();

		///Run application
		void RunApp();

	private:

		void PopulateControls(shared_ptr<IConfig> configuration);

		///Because winapi is C style, we can't bind a nonstatic MessageCallback to a window/dialog
		///We can solve this by creating a static callback and storing a pointer to 'this' instance in the window data
		///Then when we handle a message in this nonstatic method, we can call the nonstatic version of the handler by retrieving
		///the this reference
		static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		///Handle Messages sent to our dialog
		INT_PTR CALLBACK DialogProcFunc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

		//Window creation variables
		HINSTANCE h_instance_;
		HWND dialog_hwnd_;

		//Services
		shared_ptr<IConfig> configuration_;
	};
}

#endif