#include "FilePathFactory.h"

using namespace omoba;



//	FilePathFactoryByDirectoryAndExtention

				FilePathFactoryByDirectoryAndExtention::FilePathFactoryByDirectoryAndExtention ( const std::string& fileDirectory , const std::string& fileExtention )
					:
						fileDirectory	( fileDirectory ),
						fileExtention	( fileExtention )
{

}

std::string		FilePathFactoryByDirectoryAndExtention::makeFilePath ( const std::string& fileName )
{
	
	//	Constructing full path to the file
	return this->fileDirectory + "/" + fileName + "." + this->fileExtention;

}