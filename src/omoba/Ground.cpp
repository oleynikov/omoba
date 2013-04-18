#include "Ground.h"

using namespace omoba;



/*

	GroundEventListener
	
*/

void							GroundEventListener::groundDestinationSelectHandler ( const Ogre::Vector3& groundDestination )
{

}

void							GroundEventListener::groundAreaSelectHandler ( const Ogre::Vector3& groundAreaPointOne , const Ogre::Vector3& groundAreaPointTwo )
{

}



/*

	GroundController
	
*/

const OIS::MouseButtonID		GroundController::buttonSelectDestination	= OIS::MouseButtonID::MB_Right;

const OIS::MouseButtonID		GroundController::buttonSelectArea			= OIS::MouseButtonID::MB_Left;	



								GroundController::GroundController ( Ogre::SceneManager& sceneManager )
									:
										SceneNodeController ( sceneManager , "OMOBA_NODE_GROUND" ),
										groundSelectionInProcess ( false ),
										groundWidth ( 1500 ),
										groundHeight ( 1500 ),
										groundSegmentsX ( 20 ),
										groundSegmentsY ( 20 )
{

	//	Create plane
	Ogre::Plane groundPlane ( Ogre::Vector3::UNIT_Y , 0 );
	
	Ogre::MeshManager::getSingleton().createPlane
	(
		"OMOBA_MESH_GROUND",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		groundPlane,
		this->groundWidth,
		this->groundHeight,
		this->groundSegmentsX,
		this->groundSegmentsY,
		true,
		1,
		5,
		5,
		Ogre::Vector3::UNIT_Z
	);
	
	//  Creating an entity
	Ogre::Entity* groundEntity = sceneManager.createEntity ( "OMOBA_ENTITY_GROUND" , "OMOBA_MESH_GROUND" );
	groundEntity->setMaterialName("Examples/Rockwall");
	
	//	Attaching entity to the SceneNodeController...
	this->getNode().attachObject ( groundEntity );
	
}

								GroundController::~GroundController ( void )
{

}

void							GroundController::mouseMoveHandler ( const OIS::MouseEvent& mouseEvent )
{

	try
	{

		//	Calculating intersection point of the camera ray with the ground
		Ogre::Vector3 intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );
		
		// Listening for target selection
		if ( mouseEvent.state.buttonDown ( GroundController::buttonSelectDestination ) )
			signalDestinationSelected ( intersectionPoint );
		
		//	Listening for area selection
		if
		(
			this->groundSelectionInProcess
				&&
			mouseEvent.state.buttonDown ( GroundController::buttonSelectArea )
		)
		{

			this->signalAreaSelected ( this->groundSelectionPointOne , intersectionPoint );
			
		}

	}

	catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
	{

	}

}

void							GroundController::mousePressHandler ( const OIS::MouseEvent& mouseEvent )
{

	try
	{

		//	Calculating intersection point of the camera ray with the ground
		Ogre::Vector3 intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );
		
		// Listening for target selection
		if ( mouseEvent.state.buttonDown ( GroundController::buttonSelectDestination ) )
			signalDestinationSelected ( intersectionPoint );
		
		//	Listening for selection begin
		if ( mouseEvent.state.buttonDown ( GroundController::buttonSelectArea ) )
		{

			this->groundSelectionInProcess = true;
			this->groundSelectionPointOne = intersectionPoint;
			
		}
	}

	catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
	{

	}

}

void							GroundController::mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right release
	if ( mouseEvent.state.buttonDown ( GroundController::buttonSelectArea ) )
	{

		try
		{
	
			//	Calculating intersection point of the camera ray with the ground
			Ogre::Vector3 intersectionPoint = CameraRayIntersectionCalculator::getSingleton().getIntersectionWith ( mouseEvent , this->getNode() );

			this->groundSelectionInProcess = false;
			this->signalAreaSelected ( this->groundSelectionPointOne , intersectionPoint );
		}

		catch ( CameraRayIntersectionCalculator::ExcNoIntersections )
		{

		}

	}

}

void							GroundController::registerEventListener ( const GroundEvent groundEvent , GroundEventListener& groundListener )
{

	switch ( groundEvent )
	{

		case GROUND_EVENT_DESTINATION_SELECTED: 
			this->signalDestinationSelected.connect
			(
				boost::bind
				(
					&GroundEventListener::groundDestinationSelectHandler,
					&groundListener,
					_1
				)
			);
			break;

		case GROUND_EVENT_AREA_SELECTED: 
			this->signalAreaSelected.connect
			(
				boost::bind
				(
					&GroundEventListener::groundAreaSelectHandler,
					&groundListener,
					_1,
					_2
				)
			);
			break;

	}

}