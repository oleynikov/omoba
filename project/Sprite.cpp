#include "Sprite.h"

using namespace omoba;

const OIS::MouseButtonID	Sprite::mouseButtonSelect = OIS::MouseButtonID::MB_Left;

const OIS::MouseButtonID	Sprite::mouseButtonSetTarget = OIS::MouseButtonID::MB_Right;


				Sprite::Sprite ( Ogre::SceneManager& sceneManager , Ogre::String& meshName )
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

}

				Sprite::~Sprite(void)
{

}

void			Sprite::mousePressHandler ( const OIS::MouseEvent& mouseEvent )
{ 

	//	Checking if mouse pressed on this sprite
	Ogre::Vector3 intersectionPoint;
	
	try
	{
	
		intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );
		
	}
	
	catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
	{
	
		//	Mouse pressed somewhere else
		return;
	
	}
	
	//	Mouse pressed on this sprite - emitting the signal
	this->signalMousePressed ( intersectionPoint , mouseEvent.state );
	
	//	If `SPRITE_SELECT` button was pressed
	if ( mouseEvent.state.buttonDown ( Sprite::mouseButtonSelect ) )
	{
	
		this->selected = true;
		this->getNode().showBoundingBox ( true );
		
	}
	
}

void			Sprite::mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent )
{

	this->selected = false;
	this->getNode().showBoundingBox ( false );

}

void			Sprite::setMovementPath ( const Ogre::Vector3& spriteMovementPath )
{

	//	Launching the sprite along the path
	this->setNodeMovementPath ( spriteMovementPath );
	this->setNodeMoving ( true );
	
	//	Enabling the animation
	this->setAnimationName ( "OMOBA_ANIMATION_WALK" );
	this->setAnimationLoop ( true );
	this->setAnimationRunning ( true );

}