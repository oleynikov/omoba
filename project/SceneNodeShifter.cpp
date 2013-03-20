#include "SceneNodeShifter.h"

using namespace omoba;

					SceneNodeShifter::SceneNodeShifter(void)
:
							node(0),
							isMoving(false),
							moveSpeed(Ogre::Vector3::ZERO),
							moveDestination(Ogre::Vector3::ZERO),
							viewDirection(Ogre::Vector3::UNIT_Z),
							holdViewDirection(true)
{
}
					SceneNodeShifter::SceneNodeShifter(Ogre::SceneManager& sceneManager)
:
							node(0),
							isMoving(false),
							moveSpeed(Ogre::Vector3::ZERO),
							moveDestination(Ogre::Vector3::ZERO),
							viewDirection(Ogre::Vector3::UNIT_Z),
							holdViewDirection(true)
{

	this -> node = sceneManager . getRootSceneNode() -> createChildSceneNode ( "snRoot" );

}
					SceneNodeShifter::~NodeShifter(void)
{
}
Ogre::SceneNode*	SceneNodeShifter::getNode(void) const
{

	return this -> node;

}
void				SceneNodeShifter::setNode(Ogre::SceneNode* node)
{

	this -> node = node;

	if ( ! node )
		this -> stop();

}


Ogre::Vector3		SceneNodeShifter::getPosition(void) const
{

	return this -> node -> getPosition();

}
void				SceneNodeShifter::setPosition(const Ogre::Vector3& position)
{

	this -> node -> setPoition ( position );

}
void				SceneNodeShifter::getViewDirection(void) const
{

	return this -> viewDirection;

}
void				SceneNodeShifter::setViewDirection(const Ogre::Vector3& viewDirection)
{

	this -> viewDirection = viewDirection;

}