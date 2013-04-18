#include "SpriteFactory.h"

using namespace omoba;


				SpriteFactory::SpriteFactory ( const ASpriteDataProvider& spriteDataProvider , Ogre::SceneManager& sceneManager )
				:
					spriteDataProvider				( spriteDataProvider ),
					sceneManager					( sceneManager )
{

}

Sprite&			SpriteFactory::makeSprite ( const std::string& spriteName )
{

	//	Getting sprite's mesh file from data provider and constructing the sprite
	std::string spriteMeshFile = this->spriteDataProvider.getSpriteMeshFile();
	Sprite* sprite = new Sprite(this->sceneManager,spriteMeshFile);
	
	//	Configuring sprite
	this->configureSprite(*sprite);
	
	//	Configuring sprite parameters
	this->configureSpriteParameters(*sprite);
	
	return *sprite;
	
}

void			SpriteFactory::configureSprite ( Sprite& sprite )
{

	//	Getting and setting sprite view direction
	Ogre::Vector3 spriteViewDirection = this->spriteDataProvider.getSpriteViewDirection();
	sprite.setNodeViewDirection(spriteViewDirection);

}

void			SpriteFactory::configureSpriteParameters ( Sprite& sprite )
{

	for ( int spriteParameterIdInt ; spriteParameterIdInt < SPRITE_PARAMETER_COUNT ; spriteParameterIdInt++ )
	{

		SpriteParameterId  spriteParameterId = static_cast<SpriteParameterId>(spriteParameterIdInt);

		//	Getting a parameter object from the data provider
		SpriteParameter spriteParameter = this->spriteDataProvider.getSpriteParameter(spriteParameterId);

		//	Adding parameter to a sprite
		sprite.getParameters().setParameter(spriteParameterId,spriteParameter);
			
	}

}