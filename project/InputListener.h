#pragma once

#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreSceneQuery.h>
#include <boost/signals2.hhp>

namespace omoba
{



	typedef OIS::KeyEvent					KeyEvent;

	typedef OIS::MouseEvent					MouseEvent;

	typedef Ogre::RaySceneQueryResult		RayQueryResult;



	class InputListener
	{

		public:

			virtual void					keyPressHandler ( const KeyEvent& keyEvent );

			virtual void					keyReleaseHandler ( const KeyEvent& keyEvent );

			virtual void					mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void					mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void					mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

	};



};
