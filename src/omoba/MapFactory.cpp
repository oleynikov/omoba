#include "MapFactory.h"

using namespace omoba;



				MapFactory::MapFactory ( const AMapDataParser& mapDataParser , const ASpriteFactory& spriteFactory )
					:
						mapDataParser(mapDataParser),
						spriteFactory(spriteFactory)
{

}

void			MapFactory::makeMap ( const std::string mapName )
{

	std::vector<SpriteData> spritesData = this->mapDataParser.getSprites(mapName);

	std::vector<SpriteData>::iterator spritesDataItr = spritesData.begin();

	for ( ; spritesDataItr != spritesData.end() ; spritesDataItr++ )
	{

		SpriteData spriteData = *spritesDataItr;

		Sprite& sprite = this->spriteFactory.makeSprite(spriteData.type);
		sprite.setNodePosition(Ogre::Vector3(spriteData.position));

	}

}