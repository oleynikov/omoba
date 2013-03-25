#pragma once

#include <OgreEntity.h>
#include "InputListener.h"
#include "SceneNodeController.h"



namespace omoba
{

	class SpriteController
		:
			public SceneNodeController,
			public InputListener

	{

		public:

												SpriteController ( Ogre::SceneManager* sceneManager , const Ogre::String& meshName );

												~SpriteController ( void );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );



		protected:
		
			bool								containsInRayQueryResult ( const RayQueryResult& rayQueryResult );
			
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;
			
			class								ExcNoCameraRayIntersectionWithGround { };

	};

};
