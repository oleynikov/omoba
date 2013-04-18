#include "Sprite.h"

using namespace omoba;

const OIS::MouseButtonID	Sprite::mouseButtonSelect = OIS::MouseButtonID::MB_Left;

const OIS::MouseButtonID	Sprite::mouseButtonSetTarget = OIS::MouseButtonID::MB_Right;


				Sprite::Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName )
					:
						SceneNodeController ( sceneManager , meshName ),
						selected ( false )
{

	//  Creating an entity
	Ogre::Entity* entity = sceneManager.createEntity ( meshName , meshName );
	
	//	Attaching it to the SceneNodeController...
	this->getNode().attachObject ( entity );
	
	//	and to the AnimationController
	this->setAnimationEntity ( *entity );
	this->setAnimationName ( "Idle" );
	this->setAnimationLoop ( true );
	this->setAnimationEnabled ( true );

	// Listening to the reach the destination event
	this->signalNodeReachedDestination.connect(boost::bind(&Sprite::nodeReachDestinationHandler,this));

}

				Sprite::~Sprite(void)
{

}

void			Sprite::setSpriteSelected ( const bool spriteSelected )
{

	this->selected = spriteSelected;
	this->getNode().showBoundingBox ( spriteSelected );

}

void			Sprite::mouseMoveHandler ( const OIS::MouseEvent& mouseEvent )
{

	//	Checking if mouse press was performed on this particular sprite
	try
	{
	
		Ogre::Vector3 intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );
		
	}
	
	catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
	{
	
		//	Mouse was pressed somewhere else
		return;
	
	}
	
	//	Mouse press was performed on this particular sprite. Emiting respective signal
	this->signalMouseMovedOnSprite ( mouseEvent );

}

void			Sprite::mousePressHandler ( const OIS::MouseEvent& mouseEvent )
{ 

	//	Checking if mouse press was performed on this particular sprite
	try
	{
	
		Ogre::Vector3 intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );
		
	}
	
	catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
	{
	
		//	Mouse was pressed somewhere else
		return;
	
	}
	
	//	Mouse press was performed on this particular sprite. Emiting respective signal
	this->signalMousePressedOnSprite ( mouseEvent );

	//	If `Sprite::mouseButtonSelect` button was pressed
	if ( mouseEvent.state.buttonDown ( Sprite::mouseButtonSelect ) )
		this->setSpriteSelected(true);
		
}

void			Sprite::mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent )
{

	//	Checking if mouse press was performed on this particular sprite
	try
	{
	
		Ogre::Vector3 intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );
		
	}
	
	catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
	{
	
		//	Mouse was pressed somewhere else
		return;
	
	}
	
	//	Mouse release was performed on this particular sprite. Emiting respective signal
	this->signalMouseReleasedOnSprite ( mouseEvent );

	//	Deselecting the sprite
	this->setSpriteSelected(false);

}

void			Sprite::groundDestinationSelectHandler ( const Ogre::Vector3& groundDestination )
{

	//	Launching the sprite along the path
	this->setNodeMovementPath ( groundDestination );
	this->setNodeMovementSpeed ( 100 );
	this->setNodeMoving ( true );
	
	//	Enabling the animation
	this->setAnimationName ( "Walk" );
	this->setAnimationLoop ( true );
	this->setAnimationEnabled ( true );

}

Parameters		Sprite::getParameters ( void ) const
{

	return this->parameters;

}

bool			Sprite::frameRenderingQueued ( const Ogre::FrameEvent& frameEvent )
{

	try
	{

		this->addNodeMovementTime ( frameEvent.timeSinceLastFrame );
		this->addAnimationTime ( frameEvent.timeSinceLastFrame );

	}

	catch ( ... )
	{

	}

	return true;

}

void			Sprite::nodeReachDestinationHandler ( void )
{

	this->setAnimationName ( "Idle" );
	this->setAnimationLoop ( true );
	this->setAnimationEnabled ( true );

}
