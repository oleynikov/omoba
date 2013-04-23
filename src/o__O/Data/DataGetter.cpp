#include "DataGetter.h"

using namespace o__O;



				DataGetterFromFile::DataGetterFromFile ( const AFilePathFactory& filePathFactory )
					:
						filePathFactory(filePathFactory)
{

}

std::string		DataGetterFromFile::getData ( const std::string& dataFileName ) const
{

	//	Make file path
	std::string filePath = this->filePathFactory.makeFilePath(dataFileName);

	//	Get file data
	std::string fileData = FileManager::getFileData(filePath);

	//	Return file data
	return fileData;

}

const char*		DataGetterFromFile::getDataAsArray ( const std::string& dataId ) const
{

	std::string dataString = this->getData(dataId);

	return dataString.data();

}