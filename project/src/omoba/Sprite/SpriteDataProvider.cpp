#include "SpriteDataProvider.h"

using namespace omoba;



std::string SpriteDataProviderFromFile::getSpriteData ( const std::string& spriteName )
{

	//	Sprite file name
	std::string spriteFile = "../../assets/sprites/" + spriteName + ".sprite";
	
	//	Getting sprite file data
	std::string spriteFileData = o__O::FileManager::getFileData(spriteFile);
	
	return spriteFileData;
	
};