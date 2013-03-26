#pragma once

#include <OgreMovableObject.h>
#include <OgreSceneManager.h>
#include <OgreSceneQuery.h>
#include <OgreCamera.h>
#include <OISMouse.h>



namespace omoba
{

	class CameraRayIntersectionCalculator
	{
	
		public:
		
			CameraRayIntersectionCalculator&			getSingleton ( void );

			void										configure ( const Ogre::SceneManager* sceneManager , const Ogre::Camera* camera );

			Ogre::Ray									getCameraToViewportRay ( const OIS::MouseEvent& mouseEvent );

			Ogre::RaySceneQueryResult&					getAllIntersections ( const OIS::MouseEvent& mouseEvent );

			Ogre::Vector3								getIntersectionWith ( const OIS::MouseEvent& mouseEvent , const Ogre::MovableObject& object );
			
			
			
		private:

														CameraRayIntersectionCalculator ( void );
											
														CameraRayIntersectionCalculator ( const CameraRayIntersectionCalculator& copy );
											
														CameraRayIntersectionCalculator& operator= ( const CameraRayIntersectionCalculator& rhp);
														
			void										checkConfigured ( void );
		
			
			
			static CameraRayIntersectionCalculator*		singleton;
			
			Ogre::SceneManager*							sceneManager;
			
			Ogre::Camera*								camera;
			
			
			
			class										ExcSceneManagerNotSet { };
			
			class										ExcCameraNotSet { };
			
			class										ExcNoIntersections { };
			
			
			
	};
	
};