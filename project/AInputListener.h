#pragma once

#include <OgreRenderWindow.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

namespace omoba
{

	class AInputListener
	{

		public:
									AInputListener(void);
									~AInputListener(void);
			virtual void			keyPressHandler(const OIS::KeyEvent&);
			virtual void			keyReleaseHandler(const OIS::KeyEvent&);
			virtual void			mouseMoveHandler(const OIS::MouseEvent&);
			virtual void			mousePressHandler(const OIS::MouseEvent&);
			virtual void			mouseReleaseHandler(const OIS::MouseEvent&);

	};

};
