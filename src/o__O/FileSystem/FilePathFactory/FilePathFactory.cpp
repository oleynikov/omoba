#include "FilePathFactory.hpp"

using namespace o__O;



//	FilePathFactory

				FilePathFactory::FilePathFactory ( const std::string& fileDirectory , const std::string& fileExtension )
					:
						fileDirectory	( fileDirectory ),
						fileExtension	( fileExtension )
{

}

std::string		FilePathFactory::makeFilePath ( const std::string& fileName ) const
{

	//	Constructing full path to the file
	return this->fileDirectory + fileName + this->fileExtension;

}