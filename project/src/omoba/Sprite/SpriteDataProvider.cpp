#include "SpriteDataProvider.h"

using namespace omoba;



std::string SpriteDataProviderFromFile::getSpriteData ( const std::string& spriteName )
{

	//	Path to the file with the sprite data
	std::string spriteFileName = "../../assets/sprites/" + spriteName + ".sprite";

	//	Opening a file stream
	std::fstream spriteDataFile(spriteFileName.data());

	//	String contaning file data
	std::string spriteData;

	while ( ! spriteDataFile.eof() )
	{

		std::string spriteDataLine;
		spriteDataFile >> spriteDataLine;
		spriteData += spriteDataLine;

	}
	
	return spriteData;
	
};