#include "AnimationController.h"

using namespace omoba;



		AnimationController::AnimationController ( void )
			:
				animationEntity ( NULL ),
				animationState ( NULL )
{

}

		AnimationController::AnimationController ( Ogre::Entity& animationEntity , Ogre::String& animationName )
{

	this->setAnimationEntity ( animationEntity );
	this->setAnimationName ( animationName );

}

		AnimationController::~AnimationController ( void )
{

}

void	AnimationController::setAnimationEntity ( const Ogre::Entity& animationEntity )
{

	this->animationEntity = &animationEntity;

}

void	AnimationController::setAnimationName ( const Ogre::String& animationName )
{

	this->checkAnimationEntityDefined();
	
	this->animationState = this->animationEntity->getAnimationState ( animationName );

}

void	AnimationController::setAnimationLoop ( const bool& animationLoop )
{

	this->checkAnimationStateDefined();

	this->animationState->setLoop ( animationLoop );

}

void	AnimationController::setAnimationEnabled ( const bool animationEnabled )
{

	this->checkAnimationStateDefined();

	this->animationState->setEnabled ( animationEnabled );

}

void	AnimationController::addAnimationTime ( const Ogre::Real& animationTime )
{

	this->checkAnimationStateDefined();

	this->animationState->addTime ( animationTime );

}

void	AnimationController::checkAnimationEntityDefined ( void )
{

	if ( ! this->animationEntity )
		throw ExcAnimationEntityNotDefined();

}

void	AnimationController::checkAnimationStateDefined ( void )
{

	if ( ! this->animationState )
		throw ExcAnimationStateNotDefined ();

}