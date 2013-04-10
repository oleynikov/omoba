#pragma once

#include <string>



namespace omoba
{



	class ASpriteDataFileLocator
	{
	
		public:
		
			virtual std::string		getSpriteDataFileLocation ( const std::string& spriteName ) = 0;
			
	};

	
	
	class SpriteDataFileLocator
		:
			public ASpriteDataFileLocator
	{
	
		public:
		
			virtual std::string		getSpriteDataFileLocation ( const std::string& spriteName );
	
	};

	
	
};