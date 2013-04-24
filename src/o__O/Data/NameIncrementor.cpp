#include "NameIncrementor.h"

using namespace o__O;



std::string					NameIncrementor::incrementName ( const std::string& name ) const
{

	//	Get name parts
	std::vector<std::string> nameParts = this->getNameParts(name);
	
	//	Increment name id
	o__O::String nameIdString = nameParts[1];
	int nameId = nameIdString.toInt();
	nameId++;
	std::string nameIdStdString = o__O::String(nameId).toStdString();

	//	Get name base
	std::string nameBase = nameParts[0];

	//	Return incremented name
	std::string nameNew = nameBase + nameIdStdString;

	return nameNew;

}

std::vector<std::string>	NameIncrementor::getNameParts ( const std::string& name ) const
{

	std::string nameBase = name;
	std::string nameId = "";

	while ( isdigit(nameBase[nameBase.size()-1]) )
	{

		//	Get last character of the name
		char nameLastLetter = nameBase[nameBase.size()-1];

		nameId = nameLastLetter + nameId;

		nameBase.pop_back();

	}

	std::vector<std::string> nameParts;
	nameParts.push_back(nameBase);
	nameParts.push_back(nameId);

	return nameParts;

}