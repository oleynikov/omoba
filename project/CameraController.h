#pragma once

#include "InputListener.h"
#include "SceneNode.h"

namespace omoba
{

	class Camera
		:
			public SceneNode,
            public InputListener
    
	{

		public:
            
												Camera ( Ogre::SceneManager* sceneManager );

												~Camera ( void );

			Ogre::Camera*						getCamera ( void ) const;

			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );


            
		private:

			Ogre::Camera*						camera;

			bool								cameraCaptured;

			static const Ogre::Real				scrollSpeed;

			static const int					scrollAreaSize;
            
			static const OIS::MouseButtonID		cameraCaptureButton;

	};

};
