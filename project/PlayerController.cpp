#include "PlayerController.h"

using namespace omoba;

			PlayerController::PlayerController(Ogre::SceneManager* sceneManager, Ogre::Camera* camera)
				:
					sceneManager(sceneManager),
					camera(camera),
					mouseButtonSelect(OIS::MouseButtonID::MB_Right)
{
}

			PlayerController::~PlayerController(void)
{
}
void		PlayerController::mousePressHandler(const OIS::MouseEvent& mouseEvent)
{

	if ( mouseEvent.state.buttonDown(this->mouseButtonSelect) )
	{

		//	New mouse poisition
		float viewportX = float(mouseEvent.state.X.abs) / float(mouseEvent.state.width);
		float viewportY = float(mouseEvent.state.Y.abs) / float(mouseEvent.state.height);
		Ogre::Vector2 viewportPoint(viewportX,viewportY);

		Ogre::Vector3 intersection;

		if ( this->getCameraRayIntersection(viewportPoint,this->getNode(),intersection) )
			this->getNode()->showBoundingBox(true);
		else if ( intersection != Ogre::Vector3::ZERO )
			this->pushNodeBy(intersection,100);

	}

}
void		PlayerController::mouseReleaseHandler(const OIS::MouseEvent& mouseEvent)
{

	this->getNode()->showBoundingBox(false);

}
bool		PlayerController::getCameraRayIntersection	(	
															const Ogre::Vector2& viewportPoint,
															const Ogre::SceneNode* targetNode,
															Ogre::Vector3& intersectionPoint
														)
{

	bool intersectsNode = false;
	intersectionPoint = Ogre::Vector3::ZERO;

	//then send a raycast straight out from the camera at the mouse's position
	Ogre::Ray mouseRay = this->camera->getCameraToViewportRay(viewportPoint.x,viewportPoint.y);
	Ogre::RaySceneQuery* cameraRayQuery = this->sceneManager->createRayQuery(mouseRay);
	Ogre::RaySceneQueryResult& cameraRayQueryResult = cameraRayQuery->execute();

	Ogre::RaySceneQueryResult::iterator itr = cameraRayQueryResult.begin();
	for ( ; itr != cameraRayQueryResult.end(); itr++ )
	{

		intersectionPoint = mouseRay.getPoint ( itr->distance );

		if ( itr->movable && itr->movable->getParentSceneNode() == targetNode )
		{
			intersectsNode = true;
			break;
		}

	}

	return intersectsNode;

}