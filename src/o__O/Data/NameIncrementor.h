#pragma once

#include <string>
#include <vector>
#include <o__O/String/String.h>


namespace o__O
{



	class ANameIncrementor
	{

		public:

			virtual std::string			incrementName ( const std::string& name ) const = 0;

	};



	class NameIncrementor
		:
			public ANameIncrementor
	{

		public:

			virtual std::string			incrementName ( const std::string& name ) const;

			std::vector<std::string>	getNameParts ( const std::string& name ) const;

	};



}