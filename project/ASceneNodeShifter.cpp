#include "ASceneNodeShifter.h"

					omoba::ASceneNodeShifter::ASceneNodeShifter(void)
						:
							node(0),
							nodeSpeed(Ogre::Vector3::ZERO),
							nodeMoving(false)
{
}
					omoba::ASceneNodeShifter::~ASceneNodeShifter(void)
{

	if ( this->node )
	{

		delete node;

	}

}
void				omoba::ASceneNodeShifter::setNode(Ogre::SceneNode* node)
{

	this->node = node;

}

Ogre::SceneNode*	omoba::ASceneNodeShifter::getNode(void) const
{

	return this->node;

}
void				omoba::ASceneNodeShifter::stopNode(void)
{

	this->setNodeSpeed(Ogre::Vector3::ZERO);

}
bool				omoba::ASceneNodeShifter::getNodeMoving(void) const
{

	return this->nodeMoving;

}
void				omoba::ASceneNodeShifter::moveNodeBy(const Ogre::Vector3& delta)
{

	this->node->translate(delta);

}
void				omoba::ASceneNodeShifter::pushNodeBy(const Ogre::Vector3& speed)
{

	this->setNodeSpeed(this->nodeSpeed+speed);

}
void				omoba::ASceneNodeShifter::setNodeSpeed(const Ogre::Vector3& speed)
{

	this->nodeSpeed = speed;
	this->updateNodeMoving();

}
void				omoba::ASceneNodeShifter::setNodeSpeed(const omoba::Axis axis, const Ogre::Real speed)
{

	switch(axis)
	{

		case omoba::AXIS_X: this->nodeSpeed.x = speed; break;
		case omoba::AXIS_Y: this->nodeSpeed.y = speed; break;
		case omoba::AXIS_Z: this->nodeSpeed.z = speed; break;

	}

	this->updateNodeMoving();

}
void				omoba::ASceneNodeShifter::rotateNodeBy(const Ogre::Vector3& axis, const Ogre::Radian& angle, Ogre::Node::TransformSpace relativeTo)
{

	this->node->rotate(axis,angle,relativeTo);

}
void				omoba::ASceneNodeShifter::aimNodeTo(const Ogre::Vector3& targetDirection, Ogre::Node::TransformSpace relativeTo, const Ogre::Vector3& viewDirection)
{

	this->node->lookAt(targetDirection,relativeTo,viewDirection);

}
bool				omoba::ASceneNodeShifter::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
{

	if ( this->nodeMoving == true )
	{

		this->moveNodeBy ( this->nodeSpeed * frameEvent.timeSinceLastFrame );

	}

	return true;

}
void				omoba::ASceneNodeShifter::updateNodeMoving(void)
{

	this->nodeMoving =
		(
			this->nodeSpeed.x != 0
				||
			this->nodeSpeed.y != 0
				||
			this->nodeSpeed.z != 0
		)

		?
			true
		:
			false;

}