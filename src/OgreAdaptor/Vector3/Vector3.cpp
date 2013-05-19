#include "Vector3.hpp"
 
using namespace OgreAdaptor;



//	Vector3

					Vector3::Vector3 ( const Ogre::Vector3& vector )
{

	*this = vector;

}

					Vector3::Vector3 ( const std::string coordinatesStdString , const char delimiter )
{

	//	Constructing is String object
	o__O::String coordinatesString = coordinatesStdString;
	
	//	Splitting the String by a delimiter
	std::vector<o__O::String> coordinatesArray = coordinatesString.split(delimiter);
	
	//	String could not be converted to a vector
	if ( coordinatesArray.size() != 3 )
		throw Vector3Exception::ExcStringToVectorConvertionError();
	
	//	Constructing the Vector
	this->x = atoi(coordinatesArray[0].toStdString().c_str());
	this->y = atoi(coordinatesArray[1].toStdString().c_str());
	this->z = atoi(coordinatesArray[2].toStdString().c_str());
	
}

					Vector3::Vector3 ( const o__O::PointF3 point )
{

	this->x = point[0];

	this->y = point[1];

	this->z = point[2];

}

					Vector3::Vector3 ( const o__O::PointI3 point )
{

	this->x = point[0];

	this->y = point[1];

	this->z = point[2];

}

o__O::PointF3		Vector3::toPointF3 ( void )
{

	o__O::PointF3 point;
	point[0] = this->x;
	point[1] = this->y;
	point[2] = this->z;

	return point;

}

o__O::PointI3		Vector3::toPointI3 ( void )
{

	o__O::PointI3 point;
	point[0] = this->x;
	point[1] = this->y;
	point[2] = this->z;

	return point;

}