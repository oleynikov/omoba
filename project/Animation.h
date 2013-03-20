#pragma once

#include "OgreAnimationState.h"

namespace omoba
{

	class Animation
	{

		public:
									Animation(void);
									~Animation(void);
			void					setObject(Ogre::Entity* object);
			void					setName(Ogre::String& name);
			void					setLoop(bool& loop);
			void					addTime(Ogre::Real& time);
			void					start(void);
			void					stop(void);

		protected:
			Ogre::AnimationState*	state;
			Ogre::Entity*			object;
			Ogre::String			name;
			bool					running;

	};

};