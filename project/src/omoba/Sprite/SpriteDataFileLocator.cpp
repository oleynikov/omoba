#include "SpriteDataFileLocator.h"

using namespace omoba;



std::string SpriteDataFileLocator::getSpriteDataFileLocation ( const std::string& spriteName )
{

	return std::string("../../assets/sprites/" + spriteName + ".sprite");
	
};