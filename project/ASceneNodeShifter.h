#pragma once

#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <OgreFrameListener.h>
#include <OgreEntity.h>
#include "Segment.h"

namespace omoba
{

	enum Axis
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z
	};

	class ASceneNodeShifter
		:
			public Ogre::FrameListener
	{

		public:
									ASceneNodeShifter(void);
									~ASceneNodeShifter(void);
			Ogre::SceneNode*		getNode(void) const;
			void					setNode(Ogre::SceneNode*);
			void					getViewDirection(void) const;
			void					setViewDirection(const Ogre::Vector3&);
			void					setSpeed(const Ogre::Vector3&);
			void					setSpeed(const omoba::Axis, const Ogre::Real); 
			void					setPosition(const Ogre::Vector3& position);
			bool					getMoving(void) const;
			void					stop(void);
			void					moveBy(const Ogre::Vector3&);
			void					launchTo(const Ogre::Vector3& nodeDestination, const Ogre::Real& nodeSpeed);
			void					rotateBy
												(
													const Ogre::Vector3&,
													const Ogre::Radian&,
													Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT
												);
			void					lookAt
												(
													const Ogre::Vector3&,
													Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT,
													const Ogre::Vector3& = Ogre::Vector3::NEGATIVE_UNIT_Z
												);

		protected:
			bool					lookAtMoveDirection;

		private:
			virtual bool			frameRenderingQueued(const Ogre::FrameEvent&);
			void					updateNodeMoving(void);

			Ogre::SceneNode*		node;
			Ogre::Vector3			nodeSpeed;
			bool					nodeMoving;
			Ogre::Vector3			nodeDestination;
			Ogre::Vector3			viewDirection;


	};

};