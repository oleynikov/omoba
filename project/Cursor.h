#pragma once

#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include "InputListener.h"

namespace omoba
{

	class Cursor
		:
			public InputListener
	{



		public:

										Cursor ( void );

										~Cursor ( void );

			virtual void				mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );



		private:

			Ogre::Overlay*				cursorLayer;

			Ogre::OverlayContainer*		cursorContainer;



	};

};