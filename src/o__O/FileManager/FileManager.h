#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


namespace o__O
{

	class FileManager
	{
	
		public:
			
			static std::string		getFileData ( const std::string& file );

			static bool				getFileExists ( const std::string filePath );

			static void				checkFileExists ( const std::string filePath );

			class					ExcFileDoesNotExist { };
			
	};

};