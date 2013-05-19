#pragma once

#include <string>



namespace o__O
{



	class AFilePathFactory
	{
	
		public:
		
			virtual std::string			makeFilePath ( const std::string& fileName ) const = 0;
			
	};
	
	
	
	class FilePathFactory
		:
			public AFilePathFactory
	{
	
		public:
		
										FilePathFactory ( const std::string& fileDirectory , const std::string& fileExtension );

			virtual std::string			makeFilePath ( const std::string& fileName ) const;
	
		private:
		
			std::string					fileDirectory;
			
			std::string					fileExtension;
			
	};



};