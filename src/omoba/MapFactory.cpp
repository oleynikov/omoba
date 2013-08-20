#include "MapFactory.h"

using namespace omoba;
using namespace o__O::Math;



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
		sprite.rotateNode(Ogre::Vector3::UNIT_Y,spriteData.rotation);
		sprite.setNodeScale(spriteData.scale);

	}

}

void			MapFactory::makeMapGraph ( void )
{

	PlaneGraphFactory mapGraphFactory(1000,1000,10);

}