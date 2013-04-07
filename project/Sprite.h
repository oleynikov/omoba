#pragma once

#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include <string>

#include "Ground.h"
#include "InputListener.h"
#include "AnimationController.h"
#include "SceneNodeController.h"
#include "CameraRayIntersectionCalculator.h"
#include "Configuration.h"



namespace omoba
{



	typedef boost::signals2::signal<void(const OIS::MouseEvent& mouseEvent)> SignalMousePressedOnSprite;
	
	typedef boost::signals2::signal<void(const OIS::MouseEvent& mouseEvent)> SignalMouseReleasedOnSprite;
	
	typedef boost::signals2::signal<void(const OIS::MouseEvent& mouseEvent)> SignalMouseMovedOnSprite;

	

	class Sprite
		:
			public Ogre::FrameListener,
			public InputListener,
			public SceneNodeController,
			public AnimationController,
			public GroundEventListener,
			public IConfigurable<std::string,float>
	{

		public:

												Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName );

												~Sprite ( void );
												
			void								setSpriteSelected ( const bool spriteSelected );
			
			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );
			
			virtual void						groundDestinationSelectHandler ( const Ogre::Vector3& groundDestination );

			SignalMousePressedOnSprite			signalMousePressedOnSprite;
			
			SignalMouseReleasedOnSprite			signalMouseReleasedOnSprite;
			
			SignalMouseMovedOnSprite			signalMouseMovedOnSprite;
			
		private:

			virtual bool						frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );

			void								nodeReachDestinationHandler ( void );

			bool								selected;
		
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;
			
			const Ogre::String					animationWalkName;
			
			const Ogre::String					animationIdleName;
			
	};

};
