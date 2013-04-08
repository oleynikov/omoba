#include "SpriteDataParser.h"

using namespace omoba;



//	SpriteDataProvider

Ogre::Vector3	SpriteDataProvider::getSpriteViewDirection ( void ) const
{

	std::string viewDirectionString = "string";
	
	return OgreExtensions::Vector3(viewDirectionString);

}