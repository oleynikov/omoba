#include "FileManager.hpp"

using namespace o__O;



//	FileManager

bool				FileManager::getFileExists ( const std::string& file )
{

	//	Open an input file stream
	std::ifstream fileStream(file.data());
	
	//	Check if a stream is successfully opened
	if ( fileStream.is_open() )
	{
	
		//	Close the file stream
		fileStream.close();
		
		return true;
		
	}
	
	return false;

}

std::string			FileManager::getFileContents ( const std::string& file )
{

	//	Check if the file does exist
	FileManager::checkFileExists(file);

	//	Open an input file stream
	std::ifstream fileStream(file.data());
	
	//	Check if a stream is successfully opened
	if ( ! fileStream.is_open() )
	{
	
		throw FileManagerException::ErrorOpeningFile();
		
	}
	
	//	Define variables to hold file contents
	char fileCharacter;
	std::string fileContents;
	
	//	Read file line by line
    while ( fileStream.good() && ! fileStream.eof() )
    {
	
		fileCharacter = fileStream.get();
		
		if ( fileCharacter != -1 )
		{

			fileContents += fileCharacter;
			
		}
		
    }

	//	Close the file stream
	fileStream.close();
	
	//	Return file contents
	return fileContents;
	
};

void				FileManager::checkFileExists ( const std::string& file )
{

	if ( ! FileManager::getFileExists(file) )
	{
	
		throw FileManagerException::FileDoesNotExist();
		
	}
	
}