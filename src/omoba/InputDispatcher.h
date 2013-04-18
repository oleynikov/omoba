#pragma once

#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include <OISInputManager.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "InputEvent.h"
#include "InputListener.h"

namespace omoba
{



	typedef boost::signals2::signal<void(const OIS::KeyEvent&)>		SignalKeyEvent;

	typedef boost::signals2::signal<void(const OIS::MouseEvent&)>	SignalMouseEvent;


	
	class InputDispatcher
		:
			public OIS::KeyListener,
			public OIS::MouseListener,
			public Ogre::FrameListener

	{

		public:

											InputDispatcher ( Ogre::RenderWindow& renderWindow );

											~InputDispatcher ( void );

			void							initiate ( void );

			void							registerListener ( const InputEvent inputEvent , InputListener& inputListener );

			void							updateRenderWindow ( Ogre::RenderWindow& renderWindow);



		private:

			virtual bool					keyPressed ( const OIS::KeyEvent& keyEvent );

			virtual bool					keyReleased ( const OIS::KeyEvent& keyEvent );

			virtual bool					mouseMoved ( const OIS::MouseEvent& mouseEvent );

			virtual bool					mousePressed ( const OIS::MouseEvent& mouseEvent , OIS::MouseButtonID buttonId );

			virtual bool					mouseReleased ( const OIS::MouseEvent& mouseEvent , OIS::MouseButtonID buttonId );

			virtual bool					frameRenderingQueued ( const Ogre::FrameEvent& );



			SignalKeyEvent					signalKeyPressed;

			SignalKeyEvent					signalKeyReleased;

			SignalMouseEvent				signalMouseMoved;

			SignalMouseEvent				signalMousePressed;

			SignalMouseEvent				signalMouseReleased;



			OIS::InputManager*				inputManager;

			OIS::Keyboard*					keyboard;

			OIS::Mouse*						mouse;

			

	};

};
