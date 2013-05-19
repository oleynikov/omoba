#pragma once

#include <fstream>
#include <string>



namespace o__O
{



	class FileManagerException
	{
	
		public:
		
			class						FileDoesNotExist { };
		
			class						ErrorOpeningFile { };
	
	};
	
	

	class FileManager
	{
	
		public:
			
			static bool					getFileExists ( const std::string& file );

			static std::string			getFileContents ( const std::string& file );
			
			static void					checkFileExists ( const std::string& file );
			
	};

	
	
}