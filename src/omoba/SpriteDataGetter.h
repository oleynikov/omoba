#pragma once

#include <string>
#include "../o__O/FileManager/FileManager.h"
#include "../o__O/FileManager/FilePathFactory.h"



namespace omoba
{



	class SpriteDataFileFactory
		:
			public o__O::FilePathFactoryByDirectoryAndExtention
	{
	
		public:
		
											SpriteDataFileFactory ( void );
	
	};
	


	class ASpriteDataGetter
	{
	
		public:
		
			virtual std::string				getSpriteData ( const std::string& spriteName ) = 0;
			
	};

	
	
	class SpriteDataGetterFromFile
		:
			public ASpriteDataGetter
	{
	
		public:
		
											SpriteDataGetterFromFile ( const o__O::AFilePathFactory& filePathFactory );
		
			virtual std::string				getSpriteData ( const std::string& spriteName );
			
		private:
		
			const o__O::AFilePathFactory&	filePathFactory;
	
	};
	
	
	
};