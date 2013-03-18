#include "ASceneNodeShifter.h"

using namespace omoba;

					ASceneNodeShifter::ASceneNodeShifter(void)
						:
							node(0),
							nodeSpeed(Ogre::Vector3::ZERO),
							nodeMoving(false),
							viewDirection(Ogre::Vector3::UNIT_Z),
							lookAtMoveDirection(true)
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
void				ASceneNodeShifter::setViewDirection(const Ogre::Vector3& viewDirection)
{

	this->viewDirection = viewDirection;

}
void				ASceneNodeShifter::stop(void)
{

	this->setSpeed(Ogre::Vector3::ZERO);

}
bool				ASceneNodeShifter::getMoving(void) const
{

	return this->nodeMoving;

}
void				ASceneNodeShifter::moveBy(const Ogre::Vector3& delta)
{

	this->node->translate(delta);

}
void				ASceneNodeShifter::launchTo(const Ogre::Vector3& nodeDestination, const Ogre::Real& nodeSpeed)
{

	Ogre::Vector3	nodePositionCurrent = this->node->getPosition();
	Ogre::Vector3	nodeMovementSpeed = Segment::getPointVector(nodePositionCurrent,nodeDestination,nodeSpeed);

	this->nodeDestination = nodeDestination;
	this->setSpeed ( nodeMovementSpeed );

}
void				ASceneNodeShifter::setSpeed(const Ogre::Vector3& speed)
{

	this->nodeSpeed = speed;
	this->updateNodeMoving();

	if ( this->lookAtMoveDirection )
		this->lookAt(this->nodeDestination,Ogre::Node::TS_PARENT,this->viewDirection);

}
void				ASceneNodeShifter::setSpeed(const Axis axis, const Ogre::Real speed)
{

	switch(axis)
	{

		case AXIS_X: this->nodeSpeed.x = speed; break;
		case AXIS_Y: this->nodeSpeed.y = speed; break;
		case AXIS_Z: this->nodeSpeed.z = speed; break;

	}

	this->updateNodeMoving();

}
void				ASceneNodeShifter::setPosition(const Ogre::Vector3& position)
{

	this -> getNode() -> setPosition ( position );

}
void				ASceneNodeShifter::rotateBy(const Ogre::Vector3& axis, const Ogre::Radian& angle, Ogre::Node::TransformSpace relativeTo)
{

	this->node->rotate(axis,angle,relativeTo);

}
void				ASceneNodeShifter::lookAt(const Ogre::Vector3& targetPoint, Ogre::Node::TransformSpace relativeTo, const Ogre::Vector3& viewDirection)
{

	this->node->lookAt(targetPoint,relativeTo,viewDirection);

}
bool				ASceneNodeShifter::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
{

	if ( this->nodeMoving == true )
	{

		Ogre::Vector3	positionCurrent = this->getNode()->getPosition();
		Ogre::Real		distanceToDestination = Segment::getLength ( positionCurrent , this->nodeDestination );
		Ogre::Vector3	nextStepSize = this->nodeSpeed * frameEvent.timeSinceLastFrame;
		Ogre::Vector3	positionNext = positionCurrent + nextStepSize;
		Ogre::Real		distanceToNextStep = Segment::getLength ( positionCurrent , positionNext );

		if ( distanceToDestination <= distanceToNextStep )
		{
			this -> setPosition ( this->nodeDestination );
			this -> stop();
		}
		
		else
			this->moveBy ( nextStepSize );

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