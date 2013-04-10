#pragma once

#include <string>
#include "SpriteDataFileLocator.h"
#include "../../o__O/FileManager/FileManager.h"



namespace omoba
{



	class ASpriteDataProvider
	{
	
		public:
		
			virtual std::string			getSpriteData ( const std::string& spriteName ) = 0;
			
	};

	
	
	class SpriteDataProviderFromFile
		:
			public ASpriteDataProvider
	{
	
		public:
		
										SpriteDataProviderFromFile ( const ASpriteDataFileLocator& spriteDataFileLocator );
		
			virtual std::string			getSpriteData ( const std::string& spriteName );
			
		private:
		
			ASpriteDataFileLocator&		spriteDataFileLocator;
	
	};
	
	
	
};