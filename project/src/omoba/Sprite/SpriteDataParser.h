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
		
			virtual std::string									getSpriteMeshFile ( void ) const = 0;
			
			virtual std::string									getSpriteViewDirection ( void ) const = 0;

			virtual IConfiguration<std::string,std::string>		getSpriteAnimations ( void ) const = 0;
			
			virtual IConfiguration<std::string,float>			getSpriteParameters ( void ) const = 0;
			
			class												ExcParsingError { };
			
		private:
		
			virtual void										parseSpriteData ( void );
			
			std::string											spriteData;
			
	};



	class SpriteDataParserXml
		:
			public ASpriteDataParser
	{
	
		public:
	
																SpriteDataParserXml ( void );
		
																SpriteDataParserXml ( const std::string& spriteData );

			virtual std::string									getSpriteMeshFile ( void ) const;
			
			virtual std::string									getSpriteViewDirection ( void ) const;
			
			virtual IConfiguration<std::string,std::string>		getSpriteAnimations ( void ) const;

			
		private:
		
			virtual void										parseSpriteData ( void );

			TiXmlDocument										spriteXmlData;
		
	};

	
	
};