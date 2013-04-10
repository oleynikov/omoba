#include "SpriteDataProvider.h"

using namespace omoba;



				SpriteDataProviderFromFile ( const ASpriteDataFileLocator& spriteDataFileLocator )
					:
						spriteDataFileLocator(spriteDataFileLocator)
{

}

std::string		SpriteDataProviderFromFile::getSpriteData ( const std::string& spriteName )
{

	//	Asking a file locator for a location of a data file
	std::string spriteDataFilePath = this->spriteDataFileLocator.getSpriteData(spriteName);

	//	Getting sprite data file content
	std::string spriteDataFileContent = o__O::FileManager::getFileData(spriteDataFilePath);
	
	return spriteDataFileContent;
	
};