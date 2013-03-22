#include "SpriteController.h"

using namespace omoba;

const			SpriteController::mouseButtonSelect			= OIS::MouseButtonID::MB_Left;

const			SpriteController::mouseButtonSetTarget		= OIS::MouseButtonID::MB_Right;


				SpriteController::SpriteController ( Ogre::SceneManager* sceneManager , const Ogre::String& meshName )
					:
						SceneNodeShifter ( sceneManager )
{

	//  Units shall look where they go
	this->holdViewDirection = true;

	//  Default move speed for all units is 200
	//  this->moveSpeed = 200

	//  Creating an entity
	Ogre::Entity* entity = sceneManager->createEntity ( "entity" , meshName );
	this->getNode()->attachObject ( entity );

}

				SpriteController::~SpriteController(void)
{

}

void			SpriteController::mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{ 

	//	If `SPRITE_SELECT` button was pressed and if player clicked on this particular sprite
	if
	(
		mouseEvent.state.buttonDown ( SpriteController::mouseButtonSelect )
			&&
		this->containsInRayQueryResult ( rayQueryResult )
	)
	{
	
		this->getNode()->showBoundingBox ( true );
		
	}

}

void			SpriteController::mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{

	this->getNode()->showBoundingBox(false);

}

bool			SpriteController::containsInRayQueryResult ( const RayQueryResult& rayQueryResult )
{

	Ogre::RaySceneQueryResult::iterator resultItr = rayQueryResult.begin();
	
	for ( ; resultItr != rayQueryResult.end() ; resultItr++ )
	{

		if ( resultItr->movable && resultItr->movable->getParentSceneNode() == this->getNode() )
			return true;
			
	}
	
	return false;

}