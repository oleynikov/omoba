#include "PlayerController.h"

		omoba::PlayerController::PlayerController(Ogre::SceneManager* sceneManager, Ogre::Camera* camera)
	:
		sceneManager(sceneManager),
		camera(camera),
		mouseButtonSelect(OIS::MouseButtonID::MB_Left)
{
}

		omoba::PlayerController::~PlayerController(void)
{
}
void	omoba::PlayerController::mousePressHandler(const OIS::MouseEvent& mouseEvent)
{

	if ( mouseEvent.state.buttonDown(this->mouseButtonSelect) )
	{

		//	New mouse poisition
		int mousePosX = mouseEvent.state.X.abs;
		int mousePosY = mouseEvent.state.Y.abs;
		int mousePosZ = mouseEvent.state.Z.rel;

		//then send a raycast straight out from the camera at the mouse's position
		Ogre::Ray mouseRay = this->camera->getCameraToViewportRay
		(
			mousePosX/float(mouseEvent.state.width),
			mousePosY/float(mouseEvent.state.height)
		);

		Ogre::RaySceneQuery* query = this->sceneManager->createRayQuery(Ogre::Ray());
		query->setRay(mouseRay);
	 
		Ogre::RaySceneQueryResult& result = query->execute();
		Ogre::RaySceneQueryResult::iterator iter = result.begin();
	 
		// Get the results, set the camera height
		for (iter; iter != result.end(); iter++)
		{

			if
			(
				iter->movable
					&&
				iter->movable->getParentSceneNode() == this->getNode()
			)
			{

				this->getNode()->showBoundingBox(true);

			}

		}

	}

}

void	omoba::PlayerController::mouseReleaseHandler(const OIS::MouseEvent& mouseEvent)
{

	this->getNode()->showBoundingBox(false);

}
