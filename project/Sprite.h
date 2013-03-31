#pragma once

#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include "Ground.h"
#include "InputListener.h"
#include "AnimationController.h"
#include "SceneNodeController.h"
#include "CameraRayIntersectionCalculator.h"



namespace omoba
{

	class Sprite
		:
			public Ogre::FrameListener,
			public GroundEventListener,
			public InputListener,
			public SceneNodeController,
			public AnimationController
	{

		public:

												Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName );

												~Sprite ( void );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );
			
			virtual void						groundDestinationSelectHandler ( const Ogre::Vector3& groundDestination );

		private:

			virtual bool						frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );

			void								nodeReachDestinationHandler ( void );

			bool								selected;
		
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;
			
	};

};
