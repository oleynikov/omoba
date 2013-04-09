#pragma once

#include "../../OgreExtensions/Vector3/Vector3.h"
#include "../../tinyxml/tinyxml.h"



namespace omoba
{



	class ASpriteDataParser
	{
	
		public:
		
																ASpriteDataParser ( void );
		
																ASpriteDataParser ( const std::string& spriteData );
		
			void												setSpriteData ( const std::string& spriteData );
			
			virtual void										parseSpriteData ( void );
		
			virtual std::string									getSpriteMeshFile ( void ) const = 0;
			
			virtual std::string									getSpriteViewDirection ( void ) const = 0;

			virtual float										getSpriteParameterValueInitial ( const SpriteParameterId spriteParameterId ) const = 0;
			
			virtual float										getSpriteParameterValueGrowthPerLevel ( const SpriteParameterId spriteParameterId ) const = 0;
			
			class												ExcSpriteDataParsingError { };
			
			class												ExcSpriteParameterNotFound { };
			
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
			
			virtual float										getSpriteParameterValueInitial ( const SpriteParameterId spriteParameterId ) const;
			
			virtual float										getSpriteParameterValueGrowthPerLevel ( const SpriteParameterId spriteParameterId ) const;
			
		private:
		
			void												parseSpriteMeshFile ( void );
			
			void												parseSpriteViewDirection ( void );
			
			void												parseSpriteParameters ( void );
		
			TiXmlDocument										spriteDataXml;
			
			std::string											spriteMeshFile;
			
			Ogre::Vector3										spriteViewDirection;
			
			std::map<SpriteParameterId,float[2]>				spriteParameters;
			
	};

	
	
};