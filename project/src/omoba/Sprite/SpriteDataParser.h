#pragma once

#include <string>
#include "../../OgreExtensions/Vector3/Vector3.h"
#include "../../tinyxml/tinyxml.h"



namespace omoba
{



	enum SpriteDataComponent
	{
	
		SPRITE_DATA_COMPONENT_MESH_FILE,
		
		SPRITE_DATA_COMPONENT_VIEW_DIRECTION,
		
		SPRITE_DATA_COMPONENT_PARAMETERS
	
	}
	
	
	
	class ASpriteDataProvider
	{
	
		public:
		
																ASpriteDataProvider ( void );
		
																ASpriteDataProvider ( const std::string& spriteData );
		
			void												setSpriteData ( const std::string& spriteData );
			
			virtual void										parseSpriteData ( void );
		
			virtual std::string									getSpriteMeshFile ( void ) const = 0;
			
			virtual std::string									getSpriteViewDirection ( void ) const = 0;
			
			virtual SpriteParameter								getSpriteParameter ( const SpriteParameterId spriteParameterId ) const = 0;
			
			struct												ExcSpriteDataParsingFailed
			{
			
				SpriteDataComponent								spriteDataComponent;
			
			};
	
			struct												ExcSpriteParameterUndefined
			{
				
				SpriteParameterId								spriteParameterId;
			
			};
			
		private:
		
			std::string											spriteData;
			
	};



	class SpriteDataParserXml
		:
			public ASpriteDataParser
	{
	
		public:
	
																SpriteDataParserXml ( void );
		
																SpriteDataParserXml ( const std::string& spriteData );
																
			virtual void										parseSpriteData ( void );

			virtual std::string									getSpriteMeshFile ( void ) const;
			
			virtual std::string									getSpriteViewDirection ( void ) const;
			
			virtual SpriteParameter								getSpriteParameter ( const SpriteParameterId spriteParameterId ) const;
			
		private:
		
			void												clearParsedData ( void );
		
			void												parseSpriteMeshFile ( void );
			
			void												parseSpriteViewDirection ( void );
			
			void												parseSpriteParameters ( void );
		
			TiXmlDocument										spriteDataXml;
			
			std::string											spriteMeshFile;
			
			Ogre::Vector3										spriteViewDirection;
			
			std::map<SpriteParameterId,SpriteParameter>			spriteParameters;
			
	};

	
	
};