#ifndef CONFIG_H
#define CONFIG_H

#include <tchar.h>
#include <string>
#include <cpprest/json.h>

using namespace web;
using namespace std;

namespace source_xperience {

	class IConfig {
	public:
		IConfig() {};
		~IConfig() {};

		/// Save JSON object to JSON file
		virtual bool SaveSettings() = 0;

		/// Retrieve setting value from JSON object
		json::value GetSetting(const string setting_name);

		/// Set setting to value in JSON object
		void SetSetting(const string setting_name, const json::value& setting_value);

		enum InputDrivers {
			kAmbilight,
			kGamestate
		};
	private:
		/// Load JSON object from JSON file
		virtual bool LoadSettings() = 0;

	protected:
		/// JSON object containing setting key/values
		json::value JSON_object;
	};

}
#endif