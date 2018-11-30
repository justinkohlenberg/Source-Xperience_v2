#include "config/IConfig.h"

using namespace source_xperience;

json::value IConfig::GetSetting(const string setting_name) {
	auto setting_wstring = utility::conversions::to_utf16string(setting_name);
	if (!JSON_object.has_field(setting_wstring)) {
		return json::value();
	}

	return JSON_object.at(setting_wstring);
}

void IConfig::SetSetting(const string setting_name, const json::value & setting_value) {
	auto setting_wstring = utility::conversions::to_utf16string(setting_name);

	JSON_object[setting_wstring] = setting_value;
}
