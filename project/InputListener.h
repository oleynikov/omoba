#pragma once

#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreSceneQuery.h>

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

			virtual void	mouseMoveOnObjectHandler ( const Ogre::RaySceneQueryResult& rayQueryResult );

			virtual void	mousePressOnObjectHandler ( const Ogre::RaySceneQueryResult& rayQueryResult );

			virtual void	mouseReleaseOnObjectHandler ( const Ogre::RaySceneQueryResult& rayQueryResult );



	};

};
