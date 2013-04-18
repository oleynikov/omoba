#pragma once;

#include <math.h>
#include <OgreRay.h>
#include <OgreVector3.h>

namespace omoba
{

	class Ray
	{

		public:
			static Ogre::Vector3 getDirection ( const Ogre::Ray& ray );
	                                                                            
	};

};