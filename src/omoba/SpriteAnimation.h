#pragma once

#include <string>



namespace omoba
{



	enum SpriteAnimationId
	{
	
		SPRITE_ANIMATION_IDLE,
		
		SPRITE_ANIMATION_WALK,

		SPRITE_ANIMATION_COUNT

	};
	
	
	
	struct SpriteAnimation
	{

							SpriteAnimation ( const std::string name , const float speed );

		SpriteAnimation&	operator= ( const SpriteAnimation& rho );

		bool				operator== ( const SpriteAnimation& rho ) const;

		bool				operator!= ( const SpriteAnimation& rho ) const;
	
		std::string			name;
		
		float				speed;
	
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