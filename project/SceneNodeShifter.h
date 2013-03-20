#pragma once

#include "OgreSceneManager.h

namespace omoba
{

	class SceneNodeShifter
	{

		public:
									SceneNodeShifter(void);
									SceneNodeShifter(Ogre::SceneManager& sceneManager);
									~SceneNodeShifter(void);
			Ogre::SceneNode*		getNode(void) const;
			void					setNode(Ogre::SceneNode*);
			Ogre::Vector3			getPosition(void) const;
			void					setPosition(const Ogre::Vector3& position);
			void					getViewDirection(void) const;
			void					setViewDirection(const Ogre::Vector3&);
			bool					getMoving(void) const;
			void					moveBy(const Ogre::Vector3& distance);
			void					getSpeed(void) const;
			void					setSpeed(const Ogre::Vector3&);
			void					setSpeed
												(
													const Ogre::Vector3& vector,
													const Ogre::Real& speed
												);
			void					launchTo
												(
													const Ogre::Vector3& nodeDestination,
													const Ogre::Real& nodeSpeed
												);
			void					rotateBy
												(
													const Ogre::Vector3& axis,
													const Ogre::Radian& angle,
													Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT
												);
			void					lookAt
												(
													const Ogre::Vector3& point,
													Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT,
													const Ogre::Vector3&  = Ogre::Vector3::NEGATIVE_UNIT_Z
												);

		protected:
			virtual bool			frameRenderingQueued(const Ogre::FrameEvent&);
			void					updateNodeMoving(void);

			Ogre::SceneNode*		node;
			bool					isMoving;
			Ogre::Vector3			moveSpeed;
			Ogre::Vector3			moveDestination;
			Ogre::Vector3			viewDirection;
			bool					holdViewDirection;

	};

};
