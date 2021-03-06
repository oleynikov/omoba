#pragma once

#include <OgreFrameListener.h>
#include "InputListener.h"
#include "SceneNodeController.h"

namespace omoba
{

	class Cameraman
		:
			public SceneNodeController,
			public Ogre::FrameListener,
			public InputListener

	{

		public:

												Cameraman ( Ogre::SceneManager& sceneManager , const Ogre::String& cameraName );

												~Cameraman ( void );

			Ogre::Camera&						getCamera ( void ) const;

			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );



		protected:

			Ogre::Camera*						camera;

			bool								cameraCaptured;

			static const Ogre::Real				scrollSpeed;

			static const int					scrollAreaSize;
			
			static const OIS::MouseButtonID		cameraCaptureButton;



		private:

			virtual bool						frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );

	};

};
