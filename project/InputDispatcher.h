#pragma once

#include <OgreRenderWindow.h>
#include <OgreFrameListener.h>
#include <OgreSceneQuery.h>
#include <OgreSceneManager.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISEvents.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "InputListener.h"

namespace omoba
{

	typedef boost::signals2::signal<void(const OIS::KeyEvent&)>					SignalKeyEvent;
    
	typedef boost::signals2::signal<void(const OIS::MouseEvent&)>				SignalMouseEvent;

	typedef boost::signals2::signal<void(const Ogre::RaySceneQueryResult&)>		SignalMousePressedOnObject;

	typedef boost::signals2::signal<void(const Ogre::RaySceneQueryResult&)>		SignalMouseReleasedOnObject;

	typedef boost::signals2::signal<void(const Ogre::RaySceneQueryResult&)>		SignalMouseMovedOnObject;



    enum InputEvent
	{

		INPUT_EVENT_KEY_PRESSED,

		INPUT_EVENT_KEY_RELEASED,

		INPUT_EVENT_MOUSE_MOVED,

		INPUT_EVENT_MOUSE_PRESSED,

		INPUT_EVENT_MOUSE_RELEASED,

		INPUT_EVENT_MOUSE_MOVED_ON_OBJECT,

		INPUT_EVENT_MOUSE_PRESSED_ON_OBJECT,

		INPUT_EVENT_MOUSE_RELEASED_ON_OBJECT,
                
	};

    

	class InputDispatcher
		:
			public OIS::KeyListener,
			public OIS::MouseListener,
			public Ogre::FrameListener
    
	{


		public:

                                            InputDispatcher ( Ogre::RenderWindow& );

                                            ~InputDispatcher ( void );

			void                            initiate ( void );

			void                            registerListener ( const InputEvent&, InputListener* inputListener );

			void                            updateRenderWindow ( Ogre::RenderWindow* renderWindow);

			void							setSceneManager ( Ogre::SceneManager* sceneManager );

			void							setCamera ( Ogre::Camera* camera );



		private:

			virtual bool                    keyPressed(const OIS::KeyEvent&);

			virtual bool                    keyReleased(const OIS::KeyEvent&);

			virtual bool                    mouseMoved(const OIS::MouseEvent&);

			virtual bool                    mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);

			virtual bool                    mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);

			virtual bool                    frameRenderingQueued(const Ogre::FrameEvent&);

			Ogre::Vector2					getViewportMousePosition ( const OIS::MouseEvent& mouseEvent );

			Ogre::RaySceneQueryResult&		getCameraRayIntersector ( const Ogre::Vector2& viewportPoint );



            SignalKeyEvent                  signalKeyPressed;

			SignalKeyEvent                  signalKeyReleased;

			SignalMouseEvent                signalMouseMoved;

			SignalMouseEvent                signalMousePressed;

			SignalMouseEvent                signalMouseReleased;

            SignalMouseMovedOnObject        signalMouseMovedOnObject;

			SignalMousePressedOnObject      signalMousePressedOnObject;

            SignalMouseReleasedOnObject     signalMouseReleasedOnObject;
            


			OIS::InputManager*              inputManager;

			OIS::Keyboard*                  keyboard;

			OIS::Mouse*                     mouse;

			Ogre::SceneManager*				sceneManager;

			Ogre::Camera*					camera;

			class							ExcSceneManagerNotSet { };

			class							ExcCameraNotSet { };

	};

};
