#include "Vector3.h"
 
using namespace OgreExtensions;



Vector3::Vector3 ( const std::string coordinates , const char delimiter )
{

	//	Constructing is String object
	o__O::String string = coordinates;
	
	//	Splitting the String by a delimiter
	std::vector<o__O::String> coordinatesArray = coordinates.split(delimiter);
	
	//	Constructing the Vector
	this->x = atoi(coordinatesArray[0].c_str());
	this->y = atoi(coordinatesArray[1].c_str());
	this->z = atoi(coordinatesArray[2].c_str());
	
}