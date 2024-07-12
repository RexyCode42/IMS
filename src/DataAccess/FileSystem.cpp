#include "FileSystem.h"

void FileManager::FileWriter::write() {
	// Open file for write only operations with the append flag (std::ios::app)
	// All outputs will be added (appended) at the end of the file
	// Therefore, we avoid any potential overwrites
	/*if (const auto isFileValid{ ErrorUtils::isFilePathValid(filePath) };
		!isFileValid.has_value()) {
		std::cerr << ErrorUtils::errorToMessage(isFileValid.error()) << std::endl;
		return;
	}*/
}