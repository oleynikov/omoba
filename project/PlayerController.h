#pragma once

#include "ASceneNodeShifterInteractive.h"

namespace omoba
{

	class PlayerController
		:
			public ASceneNodeShifterInteractive
	{

		public:
											PlayerController(Ogre::SceneManager*,Ogre::Camera*);
											~PlayerController(void);
			virtual void					mousePressHandler(const OIS::MouseEvent&);
			virtual void					mouseReleaseHandler(const OIS::MouseEvent&);
			
		private:
			bool							PlayerController::getCameraRayIntersection	(
																							const Ogre::Vector2& viewportPoint,
																							const Ogre::SceneNode* targetNode,
																							Ogre::Vector3& intersectionPoint
																						);
			Ogre::Camera*					camera;
			Ogre::SceneManager*				sceneManager;
			OIS::MouseButtonID				mouseButtonSelect;

	};

};
