#pragma once

#include <OISKeyboard.h>
#include <OISMouse.h>

namespace omoba
{

	class InputListener
	{

		public:

			virtual void	keyPressHandler ( const OIS::KeyEvent& keyEvent );

			virtual void	keyReleaseHandler ( const OIS::KeyEvent& keyEvent );

			virtual void	mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void	mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void	mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );

	};

};
