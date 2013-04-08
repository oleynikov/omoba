#pragma once

#include "SpriteDataProvider.h"
#include "../../OgreExtensions/Vector3/Vector3.h"



namespace omoba
{

	class SpriteDataParser
	{
	
		public:
		
			void										setSpriteName ( const std::string& spriteName );
			
			void										set
			
			std::string									getSpriteMeshFile ( void ) const;
			
			std::string									getSpriteViewDirection ( void ) const;

			IConfiguration<std::string,std::string>		getSpriteAnimations
			
			IConfiguration<std::string,float>			getSpriteParameters ( void ) const;
			
			
		private:
		
			ISpriteDataProvider							spriteDataProvider;
		
			std::string									spriteName;	
		
	};

};