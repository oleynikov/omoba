#pragma once

#include <string>
#include <tinyxml/tinyxml.h>
#include <o__O/Data/DataGetter.h>
#include <o__O/String/String.hpp>
#include <OgreAdaptor/Vector3/Vector3.hpp>
#include "SpriteParameter.h"
#include "SpriteAnimation.h"



namespace omoba
{



	enum SpriteDataComponent
	{
	
		SPRITE_DATA_COMPONENT_MESH_FILE,
		
		SPRITE_DATA_COMPONENT_VIEW_DIRECTION,
		
		SPRITE_DATA_COMPONENT_PARAMETERS,

		SPRITE_DATA_COMPONENT_ANIMATIONS
	
	};
	
	
	
	class ASpriteDataProvider
	{
	
		public:
		
			virtual std::string									getSpriteMeshFile ( const std::string& spriteName ) = 0;
			
			virtual Ogre::Vector3								getSpriteViewDirection ( const std::string& spriteName ) = 0;
			
			virtual SpriteParameter								getSpriteParameter ( const std::string& spriteName , const SpriteParameterId spriteParameterId ) = 0;
			
			virtual SpriteAnimation								getSpritAnimation ( const std::string& spriteName , const SpriteAnimationId spriteAnimationId ) = 0;

			struct												ExcSpriteDataParsingFailed
			{

																ExcSpriteDataParsingFailed ( const SpriteDataComponent spriteDataComponent );
			
				SpriteDataComponent								spriteDataComponent;
			
			};
	
			struct												ExcSpriteParameterUndefined
			{

																ExcSpriteParameterUndefined ( const SpriteParameterId spriteParameterId );
				
				SpriteParameterId								spriteParameterId;
			
			};
			
			struct												ExcSpriteAnimationUndefined
			{

																ExcSpriteAnimationUndefined ( const SpriteAnimationId spriteAnimationId );
				
				SpriteAnimationId								spriteAnimationId;
			
			};

		protected:

			
	};



	class SpriteDataProviderXml
		:
			public ASpriteDataProvider
	{
	
		public:
	
																SpriteDataProviderXml ( o__O::ADataGetter& spriteDataGetter );

			virtual std::string									getSpriteMeshFile ( const std::string& spriteName  );
			
			virtual Ogre::Vector3								getSpriteViewDirection ( const std::string& spriteName );
			
			virtual SpriteParameter								getSpriteParameter ( const std::string& spriteName , const SpriteParameterId spriteParameterId );
			
			virtual SpriteAnimation								getSpritAnimation ( const std::string& spriteName , const SpriteAnimationId spriteAnimationId );

		private:

			void												updateSpriteData ( const std::string& spriteName );

			virtual void										parseSpriteData ( void );

			void												clearParsedData ( void );
		
			void												parseSpriteMeshFile ( void );
			
			void												parseSpriteViewDirection ( void );
			
			void												parseSpriteParameters ( void );

			void												parseSpriteAnimations ( void );

			o__O::ADataGetter&									spriteDataGetter;

			std::string											spriteName;
		
			TiXmlDocument										spriteDataXml;
			
			std::string											spriteMeshFile;
			
			Ogre::Vector3										spriteViewDirection;
			
			std::map<SpriteParameterId,SpriteParameter>			spriteParameters;

			std::map<SpriteAnimationId,SpriteAnimation>			spriteAnimations;
			
	};

	
	
};