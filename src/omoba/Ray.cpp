#include "Ray.h"
 
using namespace omoba;

Ogre::Vector3    Ray::getDirection ( const Ogre::Ray& ray )
{

    return ray.getOrigin() - ray.getDirection();

}