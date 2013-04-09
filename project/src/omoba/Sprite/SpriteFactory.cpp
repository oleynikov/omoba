#include "SpriteFactory.h"

using namespace omoba;



				SpriteFactory::SpriteFactory
				(
					const ASpriteDataProvider&		spriteDataProvider,
					const ASpriteDataParser&		spriteDataParser,
					const ASpriteParameterFactory&	spriteParameterFactory
					const Ogre::SceneManager&		sceneManager
				)
				:
					spriteDataProvider				( spriteDataProvider ),
					spriteDataParser				( spriteDataParser ),
					spriteParameterFactory			( spriteParameterFactory),
					sceneManager					( sceneManager )
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
	
	//	Configuring sprite
	this->configureSprite(sprite);
	
	//	Configuring sprite parameters
	this->configureSpriteParameters(sprite);
	
	return *sprite;
	
}

void			SpriteFactory::configureSprite ( Sprite& sprite )
{

	//	Getting and setting sprite view direction
	Ogre::Vector3 spriteViewDirection = this->spriteDataParser->getSpriteViewDirection();
	sprite->setNodeViewDirection(spriteViewDirection);

}

void			SpriteFactory::configureSpriteParameters ( Sprite& sprite )
{

	//	SpriteParameter object
	SpriteParameter spriteParameter;

	//	SpriteParameterId
	SpriteParameterId spriteParameterId = 0;
	
	//	Constructing all parameters
	for ( ; spriteParameterId < SPRITE_PARAMETER_COUNT ; spriteParameterId++ )
	{
	
		spriteParameter = this->spriteParameterFactory.makeSpriteParameter(spriteParameterId);
		spriteParameter.valueCurrent = this->spriteDataParser.getSpriteParameterValueInitial(spriteParameterId);
		spriteParameter.valuewGrowthPerLevel = this->spriteDataParser.getSpriteParameterValueGrowthPerLevel(spriteParameterId);
	
	}
	
	this->sprite.addParameter(spriteParameter);

}