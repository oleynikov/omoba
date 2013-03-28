#pragma once

#include <OgreException.h>
#include <OgreMovableObject.h>
#include <OgreSceneManager.h>
#include <OgreSceneQuery.h>
#include <OgreCamera.h>
#include <OISMouse.h>
#include "Segment.h"



namespace omoba
{

	class CameraRayIntersectionCalculator
	{
	
		public:

			static CameraRayIntersectionCalculator&		getSingleton ( void );

			void										configure ( Ogre::SceneManager* sceneManager , Ogre::Camera* camera );

			Ogre::Ray									getCameraToViewportRay ( const OIS::MouseEvent& mouseEvent );

			Ogre::RaySceneQueryResult&					getAllIntersections ( const OIS::MouseEvent& mouseEvent );

			Ogre::Vector3								getIntersectionWith ( const OIS::MouseEvent& mouseEvent , Ogre::SceneNode& sceneNode );

			class										ExcSceneManagerNotSet { };
			
			class										ExcCameraNotSet { };
			
			class										ExcNoIntersections { };
			
		private:

														CameraRayIntersectionCalculator ( void );
											
														CameraRayIntersectionCalculator ( const CameraRayIntersectionCalculator& copy );
											
			CameraRayIntersectionCalculator&			operator= ( CameraRayIntersectionCalculator& rho);
														
			void										checkConfigured ( void );
		
			static CameraRayIntersectionCalculator*		singleton;
			
			Ogre::SceneManager*							sceneManager;
			
			Ogre::Camera*								camera;

	};
	
};