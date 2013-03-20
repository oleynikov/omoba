#pragma once

#include <OgreFrameListener.h>
#include "InputListener.h"
#include "SceneNodeShifter.h"

namespace omoba
{

	class CameraController
		:
            public InputListener,
			public SceneNodeShifter,
			public Ogre::FrameListener
    
	{

		public:
            
												CameraController ( void );

												~CameraController ( void );

			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );

			virtual bool						frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );

            
		private:

			bool								cameraCaptured;

			static const Ogre::Real				scrollSpeed;

			static const int					scrollAreaSize;
            
			static const OIS::MouseButtonID		cameraCaptureButton;

	};

};
