#ifndef FILECONFIG_H
#define FILECONFIG_H

#include "IConfig.h"

using namespace std;

namespace source_xperience {
	class FileConfig :
		public IConfig
	{
	public:
		FileConfig();
		~FileConfig();

		static constexpr auto filename = "config.json";

		// Inherited via IConfig
		virtual bool SaveSettings() override;
		virtual bool LoadSettings() override;
	};
}
#endif