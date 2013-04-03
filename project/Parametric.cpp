#include "InputListener.h"

using namespace omoba;



bool		AttributeHolder::getAttributeExists ( const int attributeId )
{

	return	this->attributes.find(attributeId) == this->attributes.end()
				?
			false
				:
			true;
			
}

float		AttributeHolder::getAttributeValue ( const int attributeId )
{

	checkAttributeExists();

	return this->attributes.find(attributeId)->second;

}

void		AttributeHolder::setAttributeValue ( const int attributeId , const float attributeValue )
{

	//	Trying to set an existing attribute
	try
	{
	
		checkAttributeExists();

		this->attributes.find(attributeId)->second = attributeValue;
		
	}
	
	catch ( ExcUndefinedAttribute exception )
	{
	
		//	attribute doesn't exist yet
		this->attributes.insert(Attribute(attributeId,attributeValue));
	
	}

}

void		AttributeHolder::removeAttribute ( const int attributeId )
{

	this->checkAttributeExists();
	
	this->attributes.erase(attributeId);

}

void 		AttributeHolder::checkAttributeExists ( const int attributeId )
{

	if ( ! this->getAttributeExists(attributeId) )
		throw ExcUndefinedAttribute();
		
}