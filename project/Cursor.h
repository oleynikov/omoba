#pragma once

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include "AInputListener.h"

namespace omoba
{

	class Cursor
		:
			public AInputListener
	{

		public:
										Cursor(void);
										~Cursor(void);
			virtual void				mouseMoveHandler(const OIS::MouseEvent&);

		private:
			Ogre::Overlay*				cursorLayer;
			Ogre::OverlayContainer*		cursorContainer;

	};

};