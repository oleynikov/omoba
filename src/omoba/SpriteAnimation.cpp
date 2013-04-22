#include "SpriteAnimation.h"

using namespace omoba;



//	SpriteAnimation
					SpriteAnimation::SpriteAnimation ( const std::string name , const float speed )
						:
							name	( name ),
							speed	( speed )
{

}

SpriteAnimation&	SpriteAnimation::operator= ( const SpriteAnimation& rho )
{

	if ( *this != rho )
	{

		this->name = rho.name;
		this->speed = rho.speed;

	}

	return *this;

}

bool				SpriteAnimation::operator== ( const SpriteAnimation& rho ) const
{

	if
	(
		this->name == rho.name
			&&
		this->speed == rho.speed
	)

	{

		return true;

	}

	return false;

}

bool				SpriteAnimation::operator!= ( const SpriteAnimation& rho ) const
{

	if ( *this == rho )
		return false;

	return true;
		
}