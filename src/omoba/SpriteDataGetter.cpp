#include "SpriteDataGetter.h"

using namespace omoba;



//	SpriteDataFileFactory
				SpriteDataFileFactory::SpriteDataFileFactory ( void )
					:
						FilePathFactoryByDirectoryAndExtention ( "../../system/sprites" , "sprite" )
{

}



//	SpriteDataGetterFromFile

				SpriteDataGetterFromFile::SpriteDataGetterFromFile ( const o__O::AFilePathFactory& filePathFactory )
					:
						filePathFactory ( filePathFactory )
{

}

std::string		SpriteDataGetterFromFile::getSpriteData ( const std::string& spriteName )
{

	//	Asking a file path factory for a location of a data file
	std::string spriteDataFilePath = this->filePathFactory.makeFilePath(spriteName);

	//	Getting sprite data file content
	std::string spriteDataFileContent = o__O::FileManager::getFileData(spriteDataFilePath);
	
	return spriteDataFileContent;
	
}