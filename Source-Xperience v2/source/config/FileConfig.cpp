#include "config/FileConfig.h"

using namespace source_xperience;

FileConfig::FileConfig() {
	LoadSettings();
}


FileConfig::~FileConfig()
{
}

bool FileConfig::SaveSettings() {
	return false;
}

bool FileConfig::LoadSettings() {
	return false;
}
