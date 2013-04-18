#pragma once;

#include <math.h>
#include <OgreVector3.h>

namespace omoba
{
 
	class Segment
	{

		public:
		
			static Ogre::Real		getLength
														(
																const Ogre::Vector3&	segmentBegin,
																const Ogre::Vector3&	segmentEnd
														);
	                                                                            
			static Ogre::Vector3	getPointPosition
														(
																const Ogre::Vector3&	segmentBegin,
																const Ogre::Vector3&	segmentEnd,
																const Ogre::Real&		distanceFromBegin
														);

			static Ogre::Vector3	getPointVector
														(
																const Ogre::Vector3&	segmentBegin,
																const Ogre::Vector3&	segmentEnd,
																const Ogre::Real&		distanceFromBegin
														);
	};

};