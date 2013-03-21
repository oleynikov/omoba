#pragma once

#include "InputListener.h"
#include "SceneNodeController.h"

namespace omoba
{

	class CameraController
		:
			public SceneNodeController,
            public InputListener
    
	{

		public:
            
												CameraController ( Ogre::SceneManager* sceneManager );

												~CameraController ( void );

			Ogre::Camera*						getCamera ( void ) const;

			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mousePressOnObjectHandler ( const Ogre::RaySceneQueryResult& mouseEvent );

            
		private:

			Ogre::Camera*						camera;

			bool								cameraCaptured;

			static const Ogre::Real				scrollSpeed;

			static const int					scrollAreaSize;
            
			static const OIS::MouseButtonID		cameraCaptureButton;

	};

};
