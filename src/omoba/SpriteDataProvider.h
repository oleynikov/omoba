#pragma once

#include <string>
#include "../o__O/String/String.h"
#include "../OgreExtensions/Vector3/Vector3.h"
#include "../tinyxml/tinyxml.h"
#include "SpriteParameter.h"



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
		
																ASpriteDataProvider ( void );
		
																ASpriteDataProvider ( const std::string& spriteData );
		
			void												setSpriteData ( const std::string& spriteData );
			
			virtual void										parseSpriteData ( void );
		
			virtual std::string									getSpriteMeshFile ( void ) const = 0;
			
			virtual Ogre::Vector3								getSpriteViewDirection ( void ) const = 0;
			
			virtual SpriteParameter								getSpriteParameter ( const SpriteParameterId spriteParameterId ) const = 0;
			
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
		
			std::string											spriteData;
			
	};



	class SpriteDataParserXml
		:
			public ASpriteDataProvider
	{
	
		public:
	
																SpriteDataParserXml ( void );
		
																SpriteDataParserXml ( const std::string& spriteData );
																
			virtual void										parseSpriteData ( void );

			virtual std::string									getSpriteMeshFile ( void ) const;
			
			virtual Ogre::Vector3								getSpriteViewDirection ( void ) const;
			
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