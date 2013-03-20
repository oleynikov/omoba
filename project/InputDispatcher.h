#pragma once

#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISEvents.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "InputListener.h"

namespace omoba
{

	typedef boost::signals2::signal<void(const OIS::KeyEvent&)>		SignalKeyEvent;
	typedef boost::signals2::signal<void(const OIS::MouseEvent&)>	SignalMouseEvent;

	enum InputEvent
	{
		INPUT_EVENT_KEY_PRESSED,
		INPUT_EVENT_KEY_RELEASED,
		INPUT_EVENT_MOUSE_MOVED,
		INPUT_EVENT_MOUSE_PRESSED,
		INPUT_EVENT_MOUSE_RELEASED
	};

	class InputDispatcher
		:
			public OIS::KeyListener,
			public OIS::MouseListener,
			public Ogre::FrameListener
	{


		public:

									InputDispatcher(Ogre::RenderWindow&);
									~InputDispatcher(void);
			void					initiate(void);
			void					registerListener(const InputEvent&, InputListener*);
			void					updateRenderWindow(Ogre::RenderWindow*);

		private:
			virtual bool			keyPressed(const OIS::KeyEvent&);
			virtual bool			keyReleased(const OIS::KeyEvent&);
			virtual bool			mouseMoved(const OIS::MouseEvent&);
			virtual bool			mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
			virtual bool			mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
			virtual bool			frameRenderingQueued(const Ogre::FrameEvent&);


			OIS::InputManager*		inputManager;
			OIS::Keyboard*			keyboard;
			OIS::Mouse*				mouse;

			SignalKeyEvent			signalKeyPressed;
			SignalKeyEvent			signalKeyReleased;
			SignalMouseEvent		signalMouseMoved;
			SignalMouseEvent		signalMousePressed;
			SignalMouseEvent		signalMouseReleased;

	};

};
