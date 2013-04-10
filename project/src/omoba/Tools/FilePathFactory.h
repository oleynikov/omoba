#pragma once

#include <string>



namespace omoba
{



	class AFilePathFactory
	{
	
		public:
		
			virtual std::string			makeFilePath ( const std::string& fileName ) = 0;
			
	};
	
	
	
	class FilePathFactoryByDirectoryAndExtention
		:
			public AFilePathFactory
	{
	
		public:
		
										FilePathFactoryByDirectoryAndExtention ( const std::string& fileDirectory , const std::string& fileExtention );

			virtual std::string			makeFilePath ( const std::string& fileName );
	
		private:
		
			std::string					fileDirectory;
			
			std::string					fileExtention;
			
	};
	
	
	
	typedef FilePathFactoryDefault FilePathFactoryByDirectoryAndExtention;
	
	
	
};