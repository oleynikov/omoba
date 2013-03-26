#include "Sprite.h"

using namespace omoba;

const OIS::MouseButtonID	Sprite::mouseButtonSelect = OIS::MouseButtonID::MB_Left;

const OIS::MouseButtonID	Sprite::mouseButtonSetTarget = OIS::MouseButtonID::MB_Right;


				Sprite::Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName )
					:
						SceneNodeController ( *sceneManager ),
						selected ( false )
{

	//  Units shall look where they go
	this->holdViewDirection = true;

	//  Default move speed for all units is 200
	//  this->moveSpeed = 200

	//  Creating an entity
	Ogre::Entity* entity = sceneManager->createEntity ( "entity" , meshName );
	this->getNode().attachObject ( entity );

}

				Sprite::~Sprite(void)
{

}

void			Sprite::mousePressHandler ( const MouseEvent& mouseEvent );
{ 

	//	Checking if mouse pressed on this sprite
	Ogre::Vector3 intersectionPoint;
	
	try
	{
	
		intersectionPoint = CameraRayIntersectionCalculator::getIntersectionWith ( *this );
		
	}
	
	catch ( ExcNoIntersections )
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

void			Sprite::walkThePath ( const MovePath& movePath )
{

	this->setMovePath ( movePath );
	this->setMoving ( true );

}