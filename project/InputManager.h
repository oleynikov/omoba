#pragma once

#include <OgreFrameListener.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "AInputListener.h"

//#include <OgreRoot.h>

namespace omoba
{

	class InputManager
		:
			public OIS::KeyListener,
			public OIS::MouseListener,
			public Ogre::FrameListener
	{

		typedef std::list<AInputListener*>		Listeners;
		typedef Listeners::iterator				ListenerItr;

		public:
									InputManager(size_t);
									~InputManager(void);
			void					addListener(AInputListener*);
			void					removeListener(AInputListener*);

		private:
			virtual bool			keyPressed(const OIS::KeyEvent&);
			virtual bool			keyReleased(const OIS::KeyEvent&);
			virtual bool			mouseMoved(const OIS::MouseEvent&);
			virtual bool			mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
			virtual bool			mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
			virtual bool			frameRenderingQueued(const Ogre::FrameEvent&);
			virtual void			listenersNotify(void);

			OIS::InputManager*		inputManager;
			OIS::Keyboard*			keyboard;
			OIS::Mouse*				mouse;
			Listeners				listeners;

	};

};
