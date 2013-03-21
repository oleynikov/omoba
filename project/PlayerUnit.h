#pragma once

#include <OgreEntity.h>
#include "InputListener.h"
#include "SceneNodeShifter.h"

namespace omoba
{

	class PlayerUnit
		:
			public SceneNodeShifter,
            public InputListener,
			public Ogre::FrameListener
    
	{

		public:
            
                                                PlayerUnit ( Ogre::SceneManager* sceneManager , const Ogre::String& meshName );

                                                ~PlayerUnit ( void );

			virtual void                        mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void                        mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );


            
		private:
            
            virtual bool						frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );

			bool                                getCameraRayIntersection ( const Ogre::Vector2& viewportPoint , const Ogre::SceneNode* targetNode , Ogre::Vector3& intersectionPoint );



			Ogre::Camera*                       camera;

			Ogre::SceneManager*                 sceneManager;

			static const OIS::MouseButtonID     mouseButtonSelect;

	};

};
