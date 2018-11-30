#ifndef DIALOG_HELPERS_H
#define DIALOG_HELPERS_H

#include <Windows.h>
#include <vector>

#include "Helpers.h"
#include "config/IConfig.h"

using namespace std;

namespace source_xperience {
	class DialogHelpers
	{
	public:
		static void PopulateCombobox(const vector<wstring>& options, const utility::string_t& selected_option, HWND dialog_hwnd, int dialog_combobox_id) {
			int option_index = 0;
			for (const auto & option : options) {
				auto option_string = option.c_str();

				SendDlgItemMessage(dialog_hwnd, dialog_combobox_id, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(option_string));

				if (selected_option == option_string) {
					SendDlgItemMessage(dialog_hwnd, dialog_combobox_id, CB_SETCURSEL, static_cast<WPARAM>(option_index), 0);
				}

				option_index++;
			}
		}

		static void PopulateCombobox(const vector<wstring>& options, const int selected_option, HWND dialog_hwnd, int dialog_combobox_id) {
			for (const auto & option : options) {
				auto option_string = option.c_str();

				SendDlgItemMessage(dialog_hwnd, dialog_combobox_id, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(option_string));
			}
			SendDlgItemMessage(dialog_hwnd, dialog_combobox_id, CB_SETCURSEL, static_cast<WPARAM>(selected_option), 0);
		}
	};
}


#endif