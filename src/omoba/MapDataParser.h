#pragma once

#include <string>
#include <vector>
#include <o__O/Data/DataGetter.h>
#include <o__O/String/String.hpp>
#include <OgreAdaptor/Vector3/Vector3.hpp>
#include <tinyxml/tinyxml.h>
#include "Sprite.h"


namespace omoba
{



	enum MapDataComponent
	{

		MAP_DATA_COMPONENT_SPRITES

	};

	
	
	class AMapDataParser
	{
	
		public:

			virtual std::vector<SpriteData>		getSprites ( const std::string mapName ) const = 0;

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

			std::vector<SpriteData>				getSprites ( const std::string mapName ) const;

		private:

			const o__O::ADataGetter&			mapDataGetter;
			
	};

	
	
};