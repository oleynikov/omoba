#include "SpriteFactory.h"

using namespace omoba;



Sprite&			SpriteFactory::makeSprite ( const std::string& spriteName )
{

	//	Getting the sprite data and populating data parser with it
	std::string spriteData = this->spriteDataProvider->getSpriteData(spriteName);
	this->spriteDataParser->setSpriteData(spriteData);

	//	Getting sprite's mesh file and constructing the object
	std::string spriteMeshFile = this->spriteDataParser->getSpriteMeshFile();
	Sprite* sprite = new Sprite(*this->sceneManager,spriteMeshFile);
	
	//	Setting sprite view direction
	Ogre::Vector3 spriteViewDirection = this->spriteDataParser()->getSpriteViewDirection();
	sprite->setNodeViewDirection(spriteViewDirection);
	
	//	Setting sprite configuration
	sprite->setConfiguration(this->spriteDataParser->getSpriteParameters());



/*
	//	Configuring sprite animation
	sprite->setAnimationName("Walk");
	sprite->setAnimationEnabled(true);

	this->root->addFrameListener ( robot );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_PRESSED , *robot );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_RELEASED , *robot );
	this->groundController->registerEventListener ( GROUND_EVENT_DESTINATION_SELECTED , *robot );
	*/

}