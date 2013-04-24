#include "FileManager.h"

using namespace o__O;



std::string		FileManager::getFileData ( const std::string& file )
{

	//	Check if file does exist
	FileManager::checkFileExists(file);

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

bool			FileManager::getFileExists ( const std::string filePath )
{

	FILE* file = fopen(filePath.data(),"r");

	if ( !file )
		return false;

	fclose(file);
	return true;

}

void			FileManager::checkFileExists ( const std::string filePath )
{

	if ( ! FileManager::getFileExists(filePath) )
		throw FileManager::ExcFileDoesNotExist();

}