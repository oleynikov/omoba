#include "FilePathFactory.h"

using namespace o__O;



//	FilePathFactoryByDirectoryAndExtention

				FilePathFactoryByDirectoryAndExtention::FilePathFactoryByDirectoryAndExtention ( const std::string& fileDirectory , const std::string& fileExtention )
					:
						fileDirectory	( fileDirectory ),
						fileExtention	( fileExtention )
{

}

std::string		FilePathFactoryByDirectoryAndExtention::makeFilePath ( const std::string& fileName ) const
{
	
	//	Constructing full path to the file
	return this->fileDirectory + "/" + fileName + "." + this->fileExtention;

}