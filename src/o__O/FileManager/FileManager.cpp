#include "FileManager.h"

using namespace o__O;



std::string FileManager::getFileData ( const std::string& file )
{

	//	Opening a file stream
	std::fstream fileStream(file.data());
	fileStream >> std::noskipws;
	
	//	Whole file string and file line string
	std::string fileData;
	std::string fileString;

	//	Read file line by line
	while ( std::getline(fileStream,fileString) )
		fileData += fileString;

	//	Return the whole file content
	return fileData;
	
};