#pragma once

#include <string>
#include "../o__O/String/String.h"
#include "../OgreExtensions/Vector3/Vector3.h"
#include "../tinyxml/tinyxml.h"
#include "SpriteParameter.h"
#include "SpriteDataGetter.h"



namespace omoba
{



	enum SpriteDataComponent
	{
	
		SPRITE_DATA_COMPONENT_MESH_FILE,
		
		SPRITE_DATA_COMPONENT_VIEW_DIRECTION,
		
		SPRITE_DATA_COMPONENT_PARAMETERS
	
	};
	
	
	
	class ASpriteDataProvider
	{
	
		public:
		
			virtual std::string									getSpriteMeshFile ( const std::string& spriteName ) = 0;
			
			virtual Ogre::Vector3								getSpriteViewDirection ( const std::string& spriteName ) = 0;
			
			virtual SpriteParameter								getSpriteParameter ( const std::string& spriteName , const SpriteParameterId spriteParameterId ) = 0;
			
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
			
		protected:

			
	};



	class SpriteDataProviderXml
		:
			public ASpriteDataProvider
	{
	
		public:
	
																SpriteDataProviderXml ( ASpriteDataGetter& spriteDataGetter );

			virtual std::string									getSpriteMeshFile ( const std::string& spriteName  );
			
			virtual Ogre::Vector3								getSpriteViewDirection ( const std::string& spriteName );
			
			virtual SpriteParameter								getSpriteParameter ( const std::string& spriteName , const SpriteParameterId spriteParameterId );
			
		private:

			void												updateSpriteData ( const std::string& spriteName );

			virtual void										parseSpriteData ( void );

			void												clearParsedData ( void );
		
			void												parseSpriteMeshFile ( void );
			
			void												parseSpriteViewDirection ( void );
			
			void												parseSpriteParameters ( void );
		
			ASpriteDataGetter&									spriteDataGetter;

			std::string											spriteName;
		
			TiXmlDocument										spriteDataXml;
			
			std::string											spriteMeshFile;
			
			Ogre::Vector3										spriteViewDirection;
			
			std::map<SpriteParameterId,SpriteParameter>			spriteParameters;
			
	};

	
	
};