#include "SpriteParameter.h"

using namespace omoba;



//	SpriteParameter
					SpriteParameter::SpriteParameter ( const float valueGrowth , const float valueCurrent )
	:
		valueGrowth		( valueGrowth ),
		valueCurrent	( valueCurrent )
{

}

SpriteParameter&	SpriteParameter::operator= ( const SpriteParameter& rho )
{

	if ( *this != rho )
	{

		this->valueCurrent = rho.valueCurrent;
		this->valueGrowth = rho.valueGrowth;

	}

	return *this;

}

bool				SpriteParameter::operator== ( const SpriteParameter& rho ) const
{

	if
	(
		this->valueCurrent == rho.valueCurrent
			&&
		this->valueGrowth == rho.valueGrowth
	)

	{

		return true;

	}

	return false;

}

bool				SpriteParameter::operator!= ( const SpriteParameter& rho ) const
{

	if ( *this == rho )
		return false;

	return true;
		
}