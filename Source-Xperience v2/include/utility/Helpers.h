#ifndef HELPERS_H
#define HELPERS_H

#include <fileapi.h>
#include <atlstr.h>

#include <string>
#include <sstream>
#include <vector>
#include <locale>
#include <codecvt>

using namespace std;

namespace source_xperience {
	class Helpers
	{
	public:

		static const wstring ConvertStringToWstring(string input_string) {
			wstring output_string;

			static wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

			return converter.from_bytes(input_string);
		}

		static const vector<wstring> GetAvailableComPorts() {
			wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
			vector<wstring> com_ports;

			TCHAR target_path[5000];

			for (int i = 255; i >= 0; i--) {
				CString str;
				str.Format(_T("%d"), i);
				CString com_name = CString("COM") + CString(str);

				auto ret = QueryDosDevice(com_name, reinterpret_cast<LPWSTR>(target_path), 5000);

				if (ret != 0) {
					CT2CA converted_string(com_name);
					string narrow_string(converted_string);
					com_ports.push_back(converter.from_bytes(narrow_string));
				}
			}

			return com_ports;
		}

		//Enumerate over display devices and returns their identifiers
		static const vector<wstring> GetAvailableMonitors() {
			vector<wstring> available_monitors;

			int output_index = 0;
			PDISPLAY_DEVICEA output_device = new _DISPLAY_DEVICEA();
			output_device->cb = sizeof(_DISPLAY_DEVICEA);

			while (EnumDisplayDevicesA(NULL, output_index, output_device, 0) != 0) {

				//Check if monitor is even connected/active
				if ((output_device->StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) != 1) {
					output_index++;
					continue;
				}
				
				int monitor_index = 0;
				auto device_name = string(output_device->DeviceName);
				while (EnumDisplayDevicesA(device_name.c_str(), monitor_index, output_device, 0) != 0) {
					available_monitors.push_back(to_wstring(output_index));
					monitor_index++;
				}
				output_index++;
			}

			delete output_device;

			return available_monitors;
		}
	};
}

#endif

