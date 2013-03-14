#pragma once

#include "ASceneNodeShifterInteractive.h"

namespace omoba
{

	class CameraController
		:
			public ASceneNodeShifterInteractive
	{

		public:
												CameraController(void);
												~CameraController(void);
			virtual void						mouseMoveHandler(const OIS::MouseEvent&);
			virtual void						mousePressHandler(const OIS::MouseEvent&);
			virtual void						mouseReleaseHandler(const OIS::MouseEvent&);

		private:
			bool								cameraCaptured;
			static const OIS::MouseButtonID		cameraCaptureButton;
			static const Ogre::Real				scrollSpeed;
			static const Ogre::Radian			rotationAngle;
			static const int					scrollAreaSize;

	};

};
