#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreOverlayManager.h>
#include <OgreMeshManager.h>

#include "CameraRayIntersectionCalculator.h"
#include "InputDispatcher.h"
#include "Ground.h"
#include "Cameraman.h"
#include "Cursor.h"


#include "../o__O/FileManager/FilePathFactory.h"
#include "../o__O/Data/DataGetter.h"

#include "Sprite.h"
#include "SpriteFactory.h"



namespace omoba
{

	class Game
		:
			public Ogre::WindowEventListener

	{

		public:
		
									Game ( void );
									
			virtual					~Game ( void );
			
			void					initiate ( void );
			
			void					setCfgFiles ( void );
			
			void					createRoot ( void );
			
			void					defineResources ( void );
		
			void					createRenderWindow ( void );
			
			void					initializeResources ( void );
			
			void					createSceneManager ( void );
			
			void					createCamera ( void );

			void					createViewport ( void );
			
			void					configureCameraRayIntersectionCalculator ( void );

			void					createInputDispatcher ( void );
			
			void					createCursor ( void );
			
			void					createScene ( void );
			
			void					startRendering ( void );
			
			

		protected:
		
			virtual void			windowResized ( Ogre::RenderWindow* );
			
			virtual void			windowClosed ( Ogre::RenderWindow* );

			
			
		private:
			Ogre::String			pluginsCfg;
			
			Ogre::String			resourcesCfg;
			
			Ogre::Root*				root;
			
			Ogre::RenderWindow*		renderWindow;
			
			Ogre::SceneManager*		sceneManager;
			
			Cameraman*				cameraman;
			
			InputDispatcher*		inputDispatcher;

			Cursor*					cursor;
			
			GroundController*		groundController;
			
	};

};