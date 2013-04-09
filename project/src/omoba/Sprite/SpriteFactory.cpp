#include "SpriteFactory.h"

using namespace omoba;



				SpriteFactory::SpriteFactory ( const ASpriteDataProvider& spriteDataProvider , const ASpriteDataParser& spriteDataParser , const Ogre::SceneManager& sceneManager )
					:
						spriteDataProvider	( spriteDataProvider ),
						spriteDataParser	( spriteDataParser ),
						sceneManager		( sceneManager )
{

}

Sprite&			SpriteFactory::makeSprite ( const std::string& spriteName )
{

	//	Getting sprite data from data provider
	std::string spriteData = this->spriteDataProvider.getSpriteData(spriteName);
	
	//	Populating data parser with sprite data
	this->spriteDataParser.setSpriteData(spriteData);

	//	Getting sprite's mesh file from data parser and constructing the sprite
	std::string spriteMeshFile = this->spriteDataParser.getSpriteMeshFile();
	Sprite* sprite = new Sprite(this->sceneManager,spriteMeshFile);
	
	//	Getting and setting sprite view direction
	Ogre::Vector3 spriteViewDirection = this->spriteDataParser->getSpriteViewDirection();
	sprite->setNodeViewDirection(spriteViewDirection);

	//	^ ok







	
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