#pragma once

#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <OgreFrameListener.h>

namespace omoba
{

	enum AXIS
	{
		X,
		Y,
		Z
	};

	class ASceneNodeShifter
		:
			public Ogre::FrameListener
	{

		public:
								ASceneNodeShifter(void);
								~ASceneNodeShifter(void);
			void				setNode(Ogre::SceneNode*);
			Ogre::SceneNode*	getNode(void) const;
			void				stopNode(void);
			bool				getNodeMoving(void) const;
			void				moveNodeBy(const Ogre::Vector3&);
			void				pushNodeBy(const Ogre::Vector3&);
			void				setNodeSpeed(const Ogre::Vector3&);
			void				setNodeSpeed(const omoba::AXIS, const Ogre::Real); 
			void				rotateNodeBy	(
													const Ogre::Vector3&,
													const Ogre::Radian&,
													Ogre::Node::TransformSpace = Ogre::Node::TransformSpace::TS_LOCAL
												);
			void				aimNodeTo		(
													const Ogre::Vector3&,
													Ogre::Node::TransformSpace = Ogre::Node::TransformSpace::TS_LOCAL,
													const Ogre::Vector3& = Ogre::Vector3::UNIT_Z
												);
			virtual bool		frameRenderingQueued(const Ogre::FrameEvent&);

		private:
			void				updateNodeMoving(void);

			Ogre::SceneNode*	node;
			Ogre::Vector3		nodeSpeed;
			bool				nodeMoving;

	};

};