#include "CameraRayIntersectionCalculator.h"

using namespace omoba;



CameraRayIntersectionCalculator&	CameraRayIntersectionCalculator::getSingleton ( void )
{

	if ( CameraRayIntersectionCalculator::singleton == NULL )
	{
	
		CameraRayIntersectionCalculator::singleton = new CameraRayIntersectionCalculator();
		
	}
	
	return *CameraRayIntersectionCalculator::singleton;
	
}

void								CameraRayIntersectionCalculator::configure ( const Ogre::SceneManager* sceneManager , const Ogre::Camera* camera )
{

	this->sceneManager = sceneManager;
	
	this->camera = camera;

}

Ogre::Ray							CameraRayIntersectionCalculator::getCameraToViewportRay ( const OIS::MouseEvent& mouseEvent )
{

	//	Checking if dependencies are installed already
	this->checkConfigured();

	float viewportX = float ( mouseEvent.state.X.abs ) / float ( mouseEvent.state.width );
	float viewportY = float ( mouseEvent.state.Y.abs ) / float ( mouseEvent.state.height );

	return this->camera.getCameraToViewportRay ( viewportX , viewportY );

}

Ogre::RaySceneQueryResult&			CameraRayIntersectionCalculator::getAllIntersections ( const OIS::MouseEvent& mouseEvent )
{

	//	Checking if dependencies are installed already
	this->checkConfigured();

	//then send a raycast straight out from the camera at the mouse's position
	Ogre::Ray mouseRay = getCameraToViewportRay ( mouseEvent );
	Ogre::RaySceneQuery* cameraRayQuery = this->sceneManager.createRayQuery ( mouseRay );
	Ogre::RaySceneQueryResult& cameraRayQueryResult = cameraRayQuery->execute();

	return cameraRayQueryResult;

}

Ogre::Vector3						CameraRayIntersectionCalculator::getIntersectionWith ( const OIS::MouseEvent& mouseEvent , const Ogre::MovableObject& object )
{

	//	Checking if dependencies are installed already
	this->checkConfigured();

	Ogre::RaySceneQueryResult& intersectionsAll = this->getAllIntersections ( mouseEvent );

	Ogre::RaySceneQueryResult::iterator itr = intersectionsAll.begin();
	
	for ( ; itr != intersectionsAll.end(); itr++ )
	{

		if ( itr->movable && itr->movable == object )
		{
		
			Ogre::Ray cameraRay = this->getCameraToViewportRay ( mouseEvent );
			
			return Segment::getPointPosition ( cameraRay.getOrigin() , cameraRay.getDirection() , itr->distance );
			
		}

	}
	
	throw ExcNoIntersections();

}

									CameraRayIntersectionCalculator::CameraRayIntersectionCalculator ( void )
{

}

									CameraRayIntersectionCalculator::CameraRayIntersectionCalculator ( const CameraRayIntersectionCalculator& copy )
{

}
											
									CameraRayIntersectionCalculator::CameraRayIntersectionCalculator& operator= ( const CameraRayIntersectionCalculator& rhp)
{

}

void								CameraRayIntersectionCalculator::checkConfigured ( void )
{

	if ( this->sceneManager == NULL )
		throw ExcSceneManagerNotSet();
		
	if ( this->camera == NULL )
		throw ExcCameraNotSet();
	
}