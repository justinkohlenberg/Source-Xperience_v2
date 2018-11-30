#include "config/MockConfig.h"

using namespace source_xperience;

MockConfig::MockConfig() {
	LoadSettings();
}


MockConfig::~MockConfig()
{
}

bool MockConfig::SaveSettings() {
	return true;
}

bool MockConfig::LoadSettings() {
	JSON_object = json::value();

	JSON_object[L"led_controller_port"] = json::value::string(L"COM3");
	JSON_object[L"gamestate_listener_address"] = json::value::string(L"http://localhost:9094");
	JSON_object[L"hue_input_driver"] = json::value::number(kGamestate);
	JSON_object[L"led_input_driver"] = json::value::number(kAmbilight);
	JSON_object[L"ambilight_capture_monitor"] = json::value::number(0);
	JSON_object[L"ambilight_capture_limit"] = json::value::number(0);

	return true;
}
