#pragma once

#include <o__O/FileSystem/FileManager/FileManager.hpp>
#include <o__O/FileSystem/FilePathFactory/FilePathFactory.hpp>



namespace o__O
{



	class ADataGetter
	{

		public:

			virtual std::string			getData ( const std::string& dataId ) const = 0;

	};



	class DataGetterFromFile
		:
			public ADataGetter
	{

		public:

										DataGetterFromFile ( const AFilePathFactory& filePathFactory );

			virtual std::string			getData ( const std::string& dataFileName ) const;

		private:

			const AFilePathFactory&		filePathFactory;


	};



}