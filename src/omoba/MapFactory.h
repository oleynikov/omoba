#pragma once

#include <string>
#include "MapDataParser.h"
#include "SpriteFactory.h"
#include <o__O/Math/Graph/GraphFactory/PlaneGraphFactory.hpp>



namespace omoba
{

	
	
	class AMapFactory
	{
	
		public:

			virtual void				makeMap ( const std::string mapName ) = 0;

	};



	class MapFactory
		:
			public AMapFactory
	{
	
		public:

										MapFactory ( const AMapDataParser& mapDataParser , const ASpriteFactory& spriteFactory );

			virtual void				makeMap ( const std::string mapName );

		private:

			void						makeMapGraph ( void );

			const AMapDataParser&		mapDataParser;
			
			const ASpriteFactory&		spriteFactory;

	};

	
	
};