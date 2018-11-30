#include "SXApplication.h"

using namespace source_xperience;
using namespace std;
using namespace web;

SXApplication::SXApplication(HINSTANCE hInst) { 
	h_instance_ = hInst;
}


SXApplication::~SXApplication()
{
}

bool SXApplication::InitialiseApp() {
	configuration_ = make_shared<MockConfig>();

	//Create Dialog and pass 'this' as parameter
	dialog_hwnd_ = CreateDialogParam(h_instance_, MAKEINTRESOURCE(IDD_DIALOG1), 0, SXApplication::DialogProc, reinterpret_cast<LPARAM>(this));

	return false;
}

void SXApplication::RunApp() {
	//Open the dialog used as a window
	ShowWindow(dialog_hwnd_, SW_SHOWDEFAULT);

	///Message process loop
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) != 0) {
		if (!IsDialogMessage(dialog_hwnd_, &msg)) {
			TranslateMessage(&msg); // translate virtual-key messages
			DispatchMessage(&msg); // send it to dialog
		}
	}
}

void SXApplication::PopulateControls(shared_ptr<IConfig> configuration) {
	if (configuration == nullptr) {
		return;
	}

	//Fill COM Ports dropdown box, defaulting to the value set in the configuration
	auto default_com = configuration->GetSetting("led_controller_port").as_string();
	DialogHelpers::PopulateCombobox(Helpers::GetAvailableComPorts(), default_com, dialog_hwnd_, IDC_COMBO1);

	//Fill gamestate listener address edit control
	auto gamestate_listener_address = configuration->GetSetting("gamestate_listener_address");
	SetDlgItemText(dialog_hwnd_, IDC_EDIT1, gamestate_listener_address.as_string().c_str());

	//Fill input drivers for HUE lamps and Ledcontroller
	vector<wstring> input_driver_options{ Helpers::ConvertStringToWstring("Ambilight"), Helpers::ConvertStringToWstring("Gamestate") };

	auto hue_input_driver = configuration->GetSetting("hue_input_driver").as_integer();
	DialogHelpers::PopulateCombobox(input_driver_options, hue_input_driver, dialog_hwnd_, IDC_HUE_DRIVER);

	auto led_input_driver = configuration->GetSetting("led_input_driver").as_integer();
	DialogHelpers::PopulateCombobox(input_driver_options, led_input_driver, dialog_hwnd_, IDC_LED_DRIVER);

	//Fill output monitor combobox, default to the value set in the configuration
	auto capture_monitor = configuration->GetSetting("ambilight_capture_monitor").as_integer();
	DialogHelpers::PopulateCombobox(Helpers::GetAvailableMonitors(), capture_monitor, dialog_hwnd_, IDC_CAPTURE_MONITOR);
}

INT_PTR SXApplication::DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_INITDIALOG) {
		SetProp(hDlg, U(WINDOW_PROP_STRING), (HANDLE)lParam);
	} else if (uMsg == WM_NCDESTROY) {
		RemoveProp(hDlg, U(WINDOW_PROP_STRING));
	}

	SXApplication* p_this = reinterpret_cast<SXApplication*>(GetProp(hDlg, U(WINDOW_PROP_STRING)));

	if (p_this) {
		return p_this->DialogProcFunc(hDlg, uMsg, wParam, lParam);
	}

	return FALSE;
}

INT_PTR SXApplication::DialogProcFunc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND: {
		//Button handling
		switch (LOWORD(wParam)) {
			case IDC_TEST_LED_BUTTON:
				MessageBox(hDlg, L"Not implemented yet!", L"Not implemented yet", MB_OK);
				break;
			case IDC_AUTODISCOVER_HUE:
				MessageBox(hDlg, L"Not implemented yet!", L"Not implemented yet", MB_OK);
				break;
			case IDC_DOTA_CFG_WIZARD:
				MessageBox(hDlg, L"Not implemented yet!", L"Not implemented yet", MB_OK);
				break;
		}
		return TRUE;
	}
	case (WM_USER + 1):
		//This event was fired after INITDIALOG message was handled, we can now fill our controls
		PopulateControls(configuration_);
		return TRUE;
	case WM_INITDIALOG: 
		if (configuration_ == nullptr) {
			MessageBox(hDlg, L"No configuration service set, closing application", L"Configuration Service missing", MB_OK);
			PostQuitMessage(0);
		}
		PostMessage(hDlg, (WM_USER + 1), 0, 0);
		return FALSE;
	case WM_CLOSE: 
		DestroyWindow(hDlg);
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}

	return FALSE;
}