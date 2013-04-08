#pragma once

#include <string>
#include <fstream>



namespace omoba
{

	class ISpriteDataProvider
	{
	
		public:
		
			virtual std::string		getSpriteData ( const std::string& spriteName ) = 0;
			
	};

	class SpriteDataProviderFromFile
		:
			public ISpriteDataProvider
	{
	
		public:
		
			virtual std::string		getSpriteData ( const std::string& spriteName );
	
	};

};