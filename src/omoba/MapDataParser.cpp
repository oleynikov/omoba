#include "MapDataParser.h"



using namespace omoba;


//	AMapDataParser::ExcMapDataParsingFailed

												AMapDataParser::ExcMapDataParsingFailed::ExcMapDataParsingFailed ( const MapDataComponent mapDataComponent )
													:
														mapDataComponent(mapDataComponent)
{

}



//	MapDataParserXml
												MapDataParserXml::MapDataParserXml ( const o__O::ADataGetter& mapDataGetter )
													:
														mapDataGetter(mapDataGetter)
{

}

std::vector<SpriteData>							MapDataParserXml::getSprites ( const std::string mapName ) const
{

	std::string mapData = this->mapDataGetter.getData(mapName);

	TiXmlDocument mapDataXmlDocument;
	mapDataXmlDocument.Parse(mapData.data());

	//	Get parameters xml element
	TiXmlElement* spritesXmlElement = mapDataXmlDocument.RootElement()->FirstChildElement("sprites");

	if ( ! spritesXmlElement )
		throw ExcMapDataParsingFailed ( MAP_DATA_COMPONENT_SPRITES );
	
	std::vector<SpriteData> spritesData;

	TiXmlNode* spriteXmlNode = NULL;
	while ( spriteXmlNode = spritesXmlElement->IterateChildren(spriteXmlNode) )
	{

		TiXmlElement* spriteXmlElement = spriteXmlNode->ToElement();

		if ( spriteXmlElement == NULL )
			throw ExcMapDataParsingFailed ( MAP_DATA_COMPONENT_SPRITES );

		//	Get sprite data
		o__O::String spriteTypeString = spriteXmlElement->Attribute("type");
		o__O::String spritePositionXString = spriteXmlElement->Attribute("position_x");
		o__O::String spritePositionZString = spriteXmlElement->Attribute("position_z");
		o__O::String spriteRotationString = spriteXmlElement->Attribute("rotation");

		const char* spriteScaleStringPtr = spriteXmlElement->Attribute("scale");
		o__O::String spriteScaleString = spriteScaleStringPtr ? spriteScaleStringPtr : "";
		
		//	Check if parameter is defined correctly
		if
		(
			spriteTypeString.toStdString().empty()
				||
			spritePositionXString.toStdString().empty()
				||
			spritePositionZString.toStdString().empty()
		)
		{
		
			throw ExcMapDataParsingFailed ( MAP_DATA_COMPONENT_SPRITES );
		
		}

		//	Create a SpriteData object
		SpriteData spriteData;
		spriteData.type = spriteTypeString.toStdString();
		spriteData.position[0] = spritePositionXString.toFloat();
		spriteData.position[1] = 0;
		spriteData.position[2] = spritePositionZString.toFloat();
		spriteData.rotation = spriteRotationString.toInt();

		if ( ! spriteScaleString.toStdString().empty() )
			spriteData.scale = OgreExtensions::Vector3(spriteScaleString.toStdString());
		else
			spriteData.scale = Ogre::Vector3(1,1,1);

		spritesData.push_back(spriteData);

	}
	
	return spritesData;

}