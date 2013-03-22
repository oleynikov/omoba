#pragma once

#include <OgreEntity.h>
#include "InputListener.h"
#include "SceneNodeController.h"
#include "StdVector.h"

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

			virtual void						mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );



		protected:
		
			bool								containsInRayQueryResult ( const RayQueryResult& rayQueryResult );
			
			static const OIS::MouseButtonID		mouseButtonSelect;

			static const OIS::MouseButtonID		mouseButtonSetTarget;
			
			class								ExcNoCameraRayIntersectionWithGround { };

	};

};
