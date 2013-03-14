#pragma once

#include "ASceneNodeShifterInteractive.h"

namespace omoba
{

	class PlayerController
		:
			public ASceneNodeShifterInteractive
	{

		public:
			PlayerController(void);
			~PlayerController(void);
			virtual void mousePressHandler(const OIS::MouseEvent&);
			virtual void mouseReleaseHandler(const OIS::MouseEvent&);
			Ogre::Camera* camera;
			Ogre::SceneManager* sceneManager;

			
		private:
			OIS::MouseButtonID mouseButtonSelect;

	};

};
