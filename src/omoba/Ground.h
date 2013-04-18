#pragma once

#include <OgreMeshManager.h>
#include <OgreEntity.h>
#include <OgrePlane.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "InputListener.h"
#include "SceneNodeController.h"
#include "CameraRayIntersectionCalculator.h"



namespace omoba
{



	typedef boost::signals2::signal<void(const Ogre::Vector3)>							SignalDestinationSelected;
	
	typedef boost::signals2::signal<void(const Ogre::Vector3, const Ogre::Vector3)>		SignalAreaSelected;

	
	
	enum GroundEvent
	{
	
		GROUND_EVENT_DESTINATION_SELECTED,
		
		GROUND_EVENT_AREA_SELECTED
	
	};



	class GroundEventListener
	{
	
		public:
			
			virtual void						groundDestinationSelectHandler ( const Ogre::Vector3& groundDestination );
	
			virtual void						groundAreaSelectHandler ( const Ogre::Vector3& groundAreaPointOne , const Ogre::Vector3& groundAreaPointTwo );
	
	};



	class GroundController
		:
			public SceneNodeController,
			public InputListener

	{

		public:

												GroundController ( Ogre::SceneManager& sceneManager );

												~GroundController ( void );

			virtual void						mouseMoveHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mousePressHandler ( const OIS::MouseEvent& mouseEvent );

			virtual void						mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent );
			
			void								registerEventListener ( const GroundEvent groundEvent , GroundEventListener& groundListener );

		private:

			SignalDestinationSelected			signalDestinationSelected;
			
			SignalAreaSelected					signalAreaSelected;

			bool								groundSelectionInProcess;
			
			Ogre::Vector3						groundSelectionPointOne;
		
			const Ogre::Real					groundWidth;
			
			const Ogre::Real					groundHeight;
			
			const int							groundSegmentsX;
			
			const int							groundSegmentsY;

			static const OIS::MouseButtonID		buttonSelectDestination;
			
			static const OIS::MouseButtonID		buttonSelectArea;

	};
	

	
};
