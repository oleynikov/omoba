#pragma once

#include <OgreEntity.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include "InputListener.h"
#include "AnimationController.h"
#include "SceneNodeController.h"
#include "CameraRayIntersectionCalculator.h"



namespace omoba
{



	typedef boost::signals2::signal<void(const Ogre::Vector3&,const OIS::MouseState&)>     SignalMousePressed;
	


	class Sprite
		:
			public SceneNodeController,
			public AnimationController,
			public InputListener

	{
	
	

		public:

												Sprite ( Ogre::SceneManager& sceneManager , const Ogre::String& meshName );

												~Sprite ( void );

			void								setMovementPath ( const Ogre::Vector3& spriteMovementPath );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );
	
			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );

			SignalMousePressed					signalMousePressed;


	
		protected:
		
			bool								selected;
		
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;

			
			
	};

};
