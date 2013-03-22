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

			virtual void						mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void						mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void						mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );



		protected:

			Ogre::Camera*						camera;

			bool								cameraCaptured;

			static const Ogre::Real				scrollSpeed;

			static const int					scrollAreaSize;
			
			static const OIS::MouseButtonID		cameraCaptureButton;

	};

};
