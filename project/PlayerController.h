#pragma once

#include "InputListener.h"
#include "SceneNodeShifter.h"

namespace omoba
{

	class PlayerController
		:
            public InputListener,
			public SceneNodeShifter
	{

		public:
            
											PlayerController ( Ogre::SceneManager* sceneManager , Ogre::Camera* camera );

											~PlayerController ( void );

			virtual void					mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void					mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );


            
		private:

			bool							getCameraRayIntersection ( const Ogre::Vector2& viewportPoint , const Ogre::SceneNode* targetNode , Ogre::Vector3& intersectionPoint );



			Ogre::Camera*					camera;

			Ogre::SceneManager*				sceneManager;

			OIS::MouseButtonID				mouseButtonSelect;

	};

};
