#include "Animation.h"

using namespace omoba;

		Animation::Animation(void)
			:
				state(0),
				object(0),
				running(false)
{
}
		Animation::~Animation(void)
{
}
void	Animation::setObject(Ogre::Entity* object)
{

	this -> object = object;

}
void	Animation::setName(Ogre::String& name)
{

	this -> name = name;

}
void	Animation::setLoop(bool& loop)
{

	this -> state -> setLoop ( loop );

}
void	Animation::addTime(Ogre::Real& time)
{

	this -> state -> addTime ( time );

}
void	Animation::start(void)
{

	this -> running = true;

}
void	Animation::stop(void)
{

	this -> running = false;

}