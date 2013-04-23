#pragma once

#include <string>
#include <vector>
#include "Sprite.h"
#include "../o__O/String/String.h"
#include "../o__O/Data/DataGetter.h"
#include "../tinyxml/tinyxml.h"



namespace omoba
{



	enum MapDataComponent
	{

		MAP_DATA_COMPONENT_SPRITES

	};

	
	
	class AMapDataParser
	{
	
		public:

			virtual std::vector<SpriteData>		getSprites ( const std::string mapName ) = 0;

			struct								ExcMapDataParsingFailed
			{

												ExcMapDataParsingFailed ( const MapDataComponent mapDataComponent );
			
				MapDataComponent				mapDataComponent;
			
			};
				
	};



	class MapDataParserXml
		:
			public AMapDataParser
	{
	
		public:

												MapDataParserXml ( const o__O::ADataGetter& mapDataGetter );

			std::vector<SpriteData>				getSprites ( const std::string mapName );

		private:

			const o__O::ADataGetter&			mapDataGetter;
			
	};

	
	
};