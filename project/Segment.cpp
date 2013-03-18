#include "Segment.h"
 
using namespace omoba;
 
Ogre::Real		Segment::getLength
											(
													const Ogre::Vector3&  a,
													const Ogre::Vector3&  b
											)
{
 
    return sqrt
    (
        ( a.x - b.x ) * ( a.x - b.x )
            +
        ( a.y - b.y ) * ( a.y - b.y )
			+
        ( a.z - b.z ) * ( a.z - b.z )
    );
        
}
 
Ogre::Vector3	Segment::getPointPosition
											(
												const Ogre::Vector3&	a,
												const Ogre::Vector3&	b,
												const Ogre::Real&		length
											)
{
 
        Ogre::Real segmentLength = Segment::getLength ( a , b );
        Ogre::Real segmentRatio = length / ( segmentLength - length );
        
        Ogre::Real pointX = ( a.x + segmentRatio * b.x ) / ( 1 + segmentRatio );
        Ogre::Real pointY = ( a.y + segmentRatio * b.y ) / ( 1 + segmentRatio );
        Ogre::Real pointZ = ( a.z + segmentRatio * b.z ) / ( 1 + segmentRatio );
        
        return Ogre::Vector3 ( pointX , pointY , pointZ );
 
}
 
Ogre::Vector3	Segment::getPointVector
                                            (
                                                const Ogre::Vector3&	segmentBegin,
                                                const Ogre::Vector3&	segmentEnd,
                                                const Ogre::Real&		distanceFromBegin
                                            )
{
 
        Ogre::Vector3 pointPosition = Segment::getPointPosition(segmentBegin,segmentEnd,distanceFromBegin);
        
        return pointPosition - segmentBegin;
 
}
 