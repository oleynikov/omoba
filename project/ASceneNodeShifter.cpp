#include "ASceneNodeShifter.h"

using namespace omoba;

					ASceneNodeShifter::ASceneNodeShifter(void)
						:
							node(0),
							nodeSpeed(Ogre::Vector3::ZERO),
							nodeMoving(false) 
{
}
					ASceneNodeShifter::~ASceneNodeShifter(void)
{

	if ( this->node )
	{

		delete node;

	}

}
void				ASceneNodeShifter::setNode(Ogre::SceneNode* node)
{

	this->node = node;

}

Ogre::SceneNode*	ASceneNodeShifter::getNode(void) const
{

	return this->node;

}
void				ASceneNodeShifter::stopNode(void)
{

	this->setNodeSpeed(Ogre::Vector3::ZERO);

}
bool				ASceneNodeShifter::getNodeMoving(void) const
{

	return this->nodeMoving;

}
void				ASceneNodeShifter::moveNodeBy(const Ogre::Vector3& delta)
{

	this->node->translate(delta);

}
void				ASceneNodeShifter::pushNodeBy(const Ogre::Vector3& speed)
{

	this->setNodeSpeed(this->nodeSpeed+speed);

}
void				ASceneNodeShifter::pushNodeBy(const Ogre::Vector3& nodeDestination, const const Ogre::Real& speed)
{

	Ogre::Vector3 nodePosition = this->node->getPosition();
	Ogre::Vector3 moveDirection = nodeDestination - nodePosition;
	moveDirection.normalise();
	moveDirection.makeFloor(Ogre::Vector3(1,1,1));

	this->setNodeSpeed ( moveDirection * speed );

}
void				ASceneNodeShifter::setNodeSpeed(const Ogre::Vector3& speed)
{

	this->nodeSpeed = speed;
	this->updateNodeMoving();

}
void				ASceneNodeShifter::setNodeSpeed(const Axis axis, const Ogre::Real speed)
{

	switch(axis)
	{

		case AXIS_X: this->nodeSpeed.x = speed; break;
		case AXIS_Y: this->nodeSpeed.y = speed; break;
		case AXIS_Z: this->nodeSpeed.z = speed; break;

	}

	this->updateNodeMoving();

}
void				ASceneNodeShifter::rotateNodeBy(const Ogre::Vector3& axis, const Ogre::Radian& angle, Ogre::Node::TransformSpace relativeTo)
{

	this->node->rotate(axis,angle,relativeTo);

}
void				ASceneNodeShifter::aimNodeTo(const Ogre::Vector3& targetPoint, Ogre::Node::TransformSpace relativeTo, const Ogre::Vector3& viewDirection)
{

	this->node->lookAt(targetPoint,relativeTo,viewDirection);

}
bool				ASceneNodeShifter::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
{

	if ( this->nodeMoving == true )
	{

		this->moveNodeBy ( this->nodeSpeed * frameEvent.timeSinceLastFrame );

	}

	return true;

}
void				ASceneNodeShifter::updateNodeMoving(void)
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