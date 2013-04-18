#include "FileManager.h"

using namespace o__O;



std::string FileManager::getFileData ( const std::string& file )
{

	//	Opening a file stream
	std::fstream fileStream(file.data());

	//	String contaning file data
	std::string fileData;

	//	Reading file line by line
	while ( ! fileStream.eof() )
	{

		std::string fileDataLine;
		fileStream >> fileDataLine;
		fileData += fileDataLine;

	}
	
	return fileData;
	
};