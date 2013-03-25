#pragma once

#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include <OISInputManager.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "InputListener.h"

namespace omoba
{



	typedef boost::signals2::signal<void(const KeyEvent&)>								SignalKeyEvent;

	typedef boost::signals2::signal<void(const MouseEvent&, const RayQueryResult&)>		SignalMouseEvent;



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

											InputDispatcher ( Ogre::RenderWindow& renderWindow );

											~InputDispatcher ( void );

			void							initiate ( void );

			void							setSceneManager ( Ogre::SceneManager* sceneManager );

			void							setCamera ( Ogre::Camera* camera );

			void							registerListener ( const InputEvent inputEvent, InputListener* inputListener );

			void							updateRenderWindow ( Ogre::RenderWindow* renderWindow);



		private:

			virtual bool					keyPressed(const OIS::KeyEvent&);

			virtual bool					keyReleased(const OIS::KeyEvent&);

			virtual bool					mouseMoved(const OIS::MouseEvent&);

			virtual bool					mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);

			virtual bool					mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);

			virtual bool					frameRenderingQueued(const Ogre::FrameEvent&);

			Ogre::RaySceneQueryResult&		getCameraRayIntersections ( const OIS::MouseEvent& mouseEvent );



			SignalKeyEvent					signalKeyPressed;

			SignalKeyEvent					signalKeyReleased;

			SignalMouseEvent				signalMouseMoved;

			SignalMouseEvent				signalMousePressed;

			SignalMouseEvent				signalMouseReleased;



			OIS::InputManager*				inputManager;

			OIS::Keyboard*					keyboard;

			OIS::Mouse*						mouse;

			Ogre::SceneManager*				sceneManager;

			Ogre::Camera*					camera;

			class							ExcSceneManagerNotSet { };

			class							ExcCameraNotSet { };

	};

};
