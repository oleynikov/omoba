#pragma once;

#include <math.h>
#include <OgreRay.h>
#include <OgreVector3.h>

namespace omoba
{

    enum AXIS_RAY
    {

        AXIS_RAY_X = Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::UNIT_X ),
        AXIS_RAY_Y = Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::UNIT_Y ),
        AXIS_RAY_Z = Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::UNIT_Z ),
        AXIS_RAY_X_NEGATIVE = Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::NEGATIVE_UNIT_X ),
        AXIS_RAY_Y_NEGATIVE = Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::NEGATIVE_UNIT_Y ),
        AXIS_RAY_Z_NEGATIVE = Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::NEGATIVE_UNIT_Z ),

    };

	class Ray
	{

		public:
			static Ogre::Vector3    getDirection
                                                    (
                                                        const Ogre::Ray&    ray
                                                    );
	                                                                            
	};

};