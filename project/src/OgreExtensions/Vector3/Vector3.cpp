#include "Vector3.h"
 
using namespace OgreExtensions;



Vector3::Vector3 ( const std::string coordinatesStdString , const char delimiter )
{

	//	Constructing is String object
	o__O::String coordinatesString = coordinatesStdString;
	
	//	Splitting the String by a delimiter
	std::vector<o__O::String> coordinatesArray = coordinatesString.split(delimiter);
	
	//	String could not be converted to a vector
	if ( coordinatesArray.size() != 3 )
		throw ExcStringToVectorConvertionError();
	
	//	Constructing the Vector
	this->x = atoi(coordinatesArray[0].getStdString().c_str());
	this->y = atoi(coordinatesArray[1].getStdString().c_str());
	this->z = atoi(coordinatesArray[2].getStdString().c_str());
	
}