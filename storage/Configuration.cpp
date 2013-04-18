#include "Configuration.h"

using namespace omoba;



bool		Configurable::getAttributeExists ( const int attributeId )
{

	return	this->attributes.find(attributeId) == this->attributes.end()
				?
			false
				:
			true;
			
}

float		Configurable::getAttributeValue ( const int attributeId )
{

	checkAttributeExists(attributeId);

	return this->attributes.find(attributeId)->second;

}

void		Configurable::setAttributeValue ( const int attributeId , const float attributeValue )
{

	//	Trying to set an existing attribute
	try
	{
	
		checkAttributeExists(attributeId);

		this->attributes.find(attributeId)->second = attributeValue;
		
	}
	
	catch ( ExcUndefinedAttribute exception )
	{
	
		//	attribute doesn't exist yet
		this->attributes.insert(Attribute(attributeId,attributeValue));
	
	}

}

void		Configurable::increaseAttributeValue ( const int attributeId , const float attributeValueDelta )
{

	this->setAttributeValue(attributeId,this->getAttributeValue(attributeId)+attributeValueDelta);

}

void		Configurable::removeAttribute ( const int attributeId )
{

	this->checkAttributeExists(attributeId);
	
	this->attributes.erase(attributeId);

}

void 		Configurable::checkAttributeExists ( const int attributeId )
{

	if ( ! this->getAttributeExists(attributeId) )
		throw ExcUndefinedAttribute();
		
}