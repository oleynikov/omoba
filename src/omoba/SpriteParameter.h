#pragma once

#include <string>
#include "../o__O/FileManager/FileManager.h"



namespace omoba
{



	enum SpriteParameterId
	{
	
		SPRITE_PARAMETER_MOVEMENT_SPEED,
		
		SPRITE_PARAMETER_ATACK_SPEED,
	
		SPRITE_PARAMETER_COOLDOWN_REDUCTION,
		
		SPRITE_PARAMETER_COUNT
	
	};
	
	
	
	struct SpriteParameter
	{

							SpriteParameter ( const float valueGrowth , const float valueCurrent );

		SpriteParameter&	operator= ( const SpriteParameter& rho );

		bool				operator== ( const SpriteParameter& rho ) const;

		bool				operator!= ( const SpriteParameter& rho ) const;
	
		float				valueGrowth;
		
		float				valueCurrent;
	
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	
	
	
	
	
	struct SpriteParameterData
	{
	
		bool			isBuffable;
		
		const float		valueMinimum;
		
		const float		valueMaximum;
		
		const float		valuewGrowthPerLevel;		
	
	};
	
	
	
	
	class ASpriteParameterDataProvider
	{
	
		public:
		
			virtual std::string				getSpriteParameterData ( void ) = 0;
	
	};
	
	
	
	class SpriteParameterDataProviderFromFile
		:
			ASpriteParameterDataProvider
	{
	
		public:
			
			virtual std::string				getSpriteParameterData ( void )
			{
			
				std::string parametersSpriteFile = "../../assets/sprites/" + spriteName + ".sprite";
				
				//	Getting sprite file data
				std::string spriteFileData = o__O::FileManager::getFileData(spriteFile);
				
				return spriteFileData;
			
			
			}
	
	
	
	};
	
	
	
	
	
	class ASpriteParameterDataParser
	{
	
		public:
		
			virtual SpriteParameterData		getSpriteParameterData ( void ) = 0;
	
	
	};
	
	
	
	class
	
	
	
	



	class SpriteParameter
	{
	
		public:
		
			void								setValueCurrent ( const float valueCurrent )
			{
			
				if ( valueCurrent > this->valueMaximum )
					valueCurrent = this->valueMaximum;
					
				if ( valueCurrent < this->valueMinimum )
					valueCurrent = this->valueMinimum;
					
				this->valueCurrent = valueCurrent;
			
			}
			
			const SpriteParameterId				id;
			
			const bool							isBuffable;
			
			const float							valueMinimum;
			
			const float							valueMaximum;
			
			const float							valuewGrowthPerLevel;

			float								valueCurrent;
	
	};
	
	
	

	
	
	
	
	
	
	
	class ASpriteParameterFactory
	{
	
		public:
			
			ASpriteParameter&	makeSpriteParameter ( const SpriteParameterId spriteParameterId , con ) = 0;
	
	};
	
	
	
	class SpriteParameterFactory
		:
			public ASpriteParameterFactory
	{
	
		public:
		
			ASpriteParameter&	makeSpriteParameter ( const SpriteParameterId spriteParameterId )
			{
			
			
			
			
			
			
			
			
			
			
			}
	
	};

	*/

};