#pragma once

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
			public SceneNodeController,
			public AnimationController,
			public InputListener,
			public GroundEventListener

	{

		public:

												Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName );

												~Sprite ( void );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );
			
			virtual void						groundDestinationSelectHandler ( const Ogre::Vector3 groundDestination );
	
		protected:
		
			bool								selected;
		
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;
			
	};

};
