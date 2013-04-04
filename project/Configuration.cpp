#include "Configuration.h"

using namespace omoba;


bool			Configuration::getParameterExists ( const std::string parameterName )
{

	return	this.find(parameterName) == this->attributes.end()
				?
			false
				:
			true;
			
}

QVariant		Configuration::getParameterValue ( const std::string parameterName ) const
{

	this->checkParameterExists();

	return this->find(parameterName)->second;

}

void			Configuration::setParameterValue ( const std::string parameterName , const float parameterValue )
{

	//	Trying to set an existing attribute
	try
	{
	
		this->checkParameterExists();

		this->find(parameterName)->second = parameterValue;
		
	}

	catch ( ExcUndefinedParameterCalled exception )
	{
	
		//	attribute doesn't exist yet
		this->insert(Parameter(parameterName,parameterValue));

	}

}

void			Configuration::deleteParameter ( const std::string parameterName )
{

	this->checkParameterExists();

	this->erase(parameterName);

}

void 			Configuration::checkParameterExists ( const std::string parameterName ) const
{

	if ( ! this->getParameterExists(parameterName) )
		throw ExcUndefinedParameterCalled();

}