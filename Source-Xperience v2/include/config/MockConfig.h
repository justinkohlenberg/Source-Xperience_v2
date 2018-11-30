#ifndef MOCKCONFIG_H
#define MOCKCONFIG_H

#include "IConfig.h"

using namespace std;

namespace source_xperience {
	class MockConfig :
		public IConfig
	{
	public:
		MockConfig();
		~MockConfig();

		// Inherited via IConfig
		virtual bool SaveSettings() override;
		virtual bool LoadSettings() override;
	};
}
#endif