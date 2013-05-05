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
#include "../o__O/Configuration/Configuration.h"
#include "../OgreExtensions/SceneManager/SceneManager.h"
#include "SpriteParameter.h"
#include "SpriteAnimation.h"



namespace omoba
{


	//	Mouse Events
	typedef boost::signals2::signal<void(const OIS::MouseEvent& mouseEvent)>	SignalMousePressedOnSprite;
	
	typedef boost::signals2::signal<void(const OIS::MouseEvent& mouseEvent)>	SignalMouseReleasedOnSprite;
	
	typedef boost::signals2::signal<void(const OIS::MouseEvent& mouseEvent)>	SignalMouseMovedOnSprite;



	//	Parameters and animations
	typedef o__O::IConfiguration<SpriteParameterId,SpriteParameter>				Parameters;

	typedef o__O::IConfiguration<SpriteAnimationId,SpriteAnimation>				Animations;

	

	struct SpriteData
	{

		std::string		type;

		float			position[3];

		Ogre::Vector3	scale;

		int				rotation;

	};



	//	Sprite
	class Sprite
		:
			public Ogre::FrameListener,
			public InputListener,
			public SceneNodeController,
			public AnimationController,
			public GroundEventListener
	{

		public:

												Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName );

												~Sprite ( void );
												
			void								setSpriteSelected ( const bool spriteSelected );
			
			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );
			
			virtual void						groundDestinationSelectHandler ( const Ogre::Vector3& groundDestination );

			Parameters&							getParameters ( void );

			Animations&							getAnimations ( void );

			SignalMousePressedOnSprite			signalMousePressedOnSprite;
			
			SignalMouseReleasedOnSprite			signalMouseReleasedOnSprite;
			
			SignalMouseMovedOnSprite			signalMouseMovedOnSprite;
			
		private:

			virtual bool						frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );

			void								nodeReachDestinationHandler ( void );

			Parameters							parameters;

			Animations							animations;

			bool								selected;
		
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;

	};

};
