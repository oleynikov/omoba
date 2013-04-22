#pragma once

#include "../FileManager/FileManager.h"
#include "../FileManager/FilePathFactory.h"



namespace o__O
{



	class ADataGetter
	{

		public:

			virtual std::string			getData ( const std::string& dataId ) = 0;

	};



	class DataGetterFromFile
		:
			public ADataGetter
	{

		public:

										DataGetterFromFile ( const AFilePathFactory& filePathFactory );

			virtual std::string			getData ( const std::string& dataFileName );

		private:

			const AFilePathFactory&		filePathFactory;


	};



}