#include "SpriteFactory.h"

using namespace omoba;


				SpriteFactory::SpriteFactory ( ASpriteDataProvider& spriteDataProvider , Ogre::SceneManager& sceneManager )
				:
					spriteDataProvider				( spriteDataProvider ),
					sceneManager					( sceneManager )
{

}

Sprite&			SpriteFactory::makeSprite ( const std::string& spriteName ) const
{

	//	Getting sprite's mesh file from data provider and constructing the sprite
	std::string spriteMeshFile = this->spriteDataProvider.getSpriteMeshFile(spriteName);
	Sprite* sprite = new Sprite(this->sceneManager,spriteMeshFile);
	
	//	Getting and setting sprite view direction
	Ogre::Vector3 spriteViewDirection = this->spriteDataProvider.getSpriteViewDirection(spriteName);
	sprite->setNodeViewDirection(spriteViewDirection);

	//	Getting sprite parameters
	for ( int spriteParameterIdInt = 0 ; spriteParameterIdInt < SPRITE_PARAMETER_COUNT ; spriteParameterIdInt++ )
	{

		SpriteParameterId  spriteParameterId = static_cast<SpriteParameterId>(spriteParameterIdInt);

		//	Getting a parameter object from the data provider
		SpriteParameter spriteParameter = this->spriteDataProvider.getSpriteParameter(spriteName,spriteParameterId);

		//	Adding parameter to a 
		sprite->getParameters().setParameter(spriteParameterId,spriteParameter);
		
	}

	//	Get sprite animations
	for ( int spriteAnimationIdInt = 0 ; spriteAnimationIdInt < SPRITE_ANIMATION_COUNT ; spriteAnimationIdInt++ )
	{

		SpriteAnimationId  spriteAnimationId = static_cast<SpriteAnimationId>(spriteAnimationIdInt);

		//	Get an animation object from the data provider
		SpriteAnimation spriteAnimation = this->spriteDataProvider.getSpritAnimation(spriteName,spriteAnimationId);

		//	Add animation to an animation map
		sprite->getAnimations().setParameter(spriteAnimationId,spriteAnimation);
		
	}

	return *sprite;
	
}