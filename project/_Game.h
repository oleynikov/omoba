#pragma once

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include "InputDispatcher.h"
#include "CameraController.h"
#include "PlayerController.h"

// Temp include
#include <OgreMeshManager.h>

namespace omoba
{

	class Game
		:
			public Ogre::WindowEventListener

	{

		public:
									Game(void);
			virtual					~Game(void);
			void					initiate(void);
			void					setCfgFiles(void);
			void					createRoot(void);
			void					defineResources(void);
			void					createRenderWindow(void);
			void					initializeResources(void);
			void					createSceneManager(void);
			void					createInputDispatcher(void);
			void					createCamera(void);
			void					createViewport(void);
			void					createScene(void);
			void					startRendering(void);

		protected:
			virtual void			windowResized(Ogre::RenderWindow*);
			virtual void			windowClosed(Ogre::RenderWindow*);

		private:
			Ogre::String			oPluginsCfg;
			Ogre::String			oResourcesCfg;
			Ogre::Root*				oRoot;
			Ogre::RenderWindow*		oRenderWindow;
			Ogre::SceneManager*		oSceneManager;
			InputDispatcher*		inputDispatcher;
			Ogre::Camera*			camera;
			CameraController*		cameraController;
			PlayerController*		playerController;

	};

};