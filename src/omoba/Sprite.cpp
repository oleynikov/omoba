#include "Sprite.h"

using namespace omoba;



const OIS::MouseButtonID	Sprite::mouseButtonSelect = OIS::MouseButtonID::MB_Left;

const OIS::MouseButtonID	Sprite::mouseButtonSetTarget = OIS::MouseButtonID::MB_Right;



				Sprite::Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName )
					:
						SceneNodeController ( sceneManager , meshName ),
						selected ( false )
{

	std::string entityName = OgreExtensions::SceneManager::getAvailableEntityName(sceneManager,meshName);

	//  Create an entity and attach it to the SceneNodeController
	Ogre::Entity* entity = sceneManager.createEntity ( entityName , meshName );
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
	this->setNodeMoving ( true );
	float speedCurrent = this->parameters.getParameter(SPRITE_PARAMETER_MOVEMENT_SPEED).getValueCurrent().valueCurrent;
	this->setNodeMovementSpeed(speedCurrent);
	
	//	Enabling the animation
	this->setAnimationName ( "Walk" );
	this->setAnimationLoop ( true );
	this->setAnimationEnabled ( true );

}

Parameters&		Sprite::getParameters ( void )
{

	return this->parameters;

}

Animations&		Sprite::getAnimations ( void )
{

	return this->animations;

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

	//	Get idle animation name
	std::string animationIdleName = this->animations.getParameter(SPRITE_ANIMATION_IDLE).getValueCurrent().name;

	this->setAnimationName ( animationIdleName );
	this->setAnimationLoop ( true );
	this->setAnimationEnabled ( true );

}