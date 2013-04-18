#pragma once

#include <OgreEntity.h>
#include <OgreAnimationState.h>

namespace omoba
{

	class AnimationController
	{

		public:
		
									AnimationController ( void );

									AnimationController ( Ogre::Entity& animationEntity , Ogre::String& animationName );
									
									~AnimationController ( void );
									
			void					setAnimationEntity ( Ogre::Entity& animationEntity );
			
			void					setAnimationName ( const Ogre::String& animationName );

			void					setAnimationLoop ( const bool& animationLoop );

			void					setAnimationEnabled ( const bool animationEnabled );
			
			void					addAnimationTime ( const Ogre::Real& animationTime );
			
			class					ExcAnimationEntityNotDefined { };
			
			class					ExcAnimationStateNotDefined { };
			
		private:
		
			void					checkAnimationEntityDefined ( void );
			
			void					checkAnimationStateDefined ( void );
		
			Ogre::Entity*			animationEntity;

			Ogre::AnimationState*	animationState;
			
	};

};