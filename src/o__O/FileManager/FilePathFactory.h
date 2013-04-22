#pragma once

#include <string>



namespace o__O
{



	class AFilePathFactory
	{
	
		public:
		
			virtual std::string			makeFilePath ( const std::string& fileName ) const = 0;
			
	};
	
	
	
	class FilePathFactoryByDirectoryAndExtention
		:
			public AFilePathFactory
	{
	
		public:
		
										FilePathFactoryByDirectoryAndExtention ( const std::string& fileDirectory , const std::string& fileExtention );

			virtual std::string			makeFilePath ( const std::string& fileName ) const;
	
		private:
		
			std::string					fileDirectory;
			
			std::string					fileExtention;
			
	};
	


	typedef FilePathFactoryByDirectoryAndExtention FilePathFactoryDefault;
	
	

};