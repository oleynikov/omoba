#include "SceneNodeShifter.h"

using namespace omoba;

					SceneNodeShifter::SceneNodeShifter ( Ogre::SceneManager* sceneManager )
                        :
                            node                ( 0 ),
                            isMoving            ( false ),
                            moveSpeed           ( Ogre::Vector3::ZERO ),
                            moveDestination     ( Ogre::Vector3::ZERO ),
                            viewDirection       ( Ogre::Vector3::UNIT_Z ),
                            holdViewDirection   ( true )
{

    if ( sceneManager )
    	this->node = sceneManager->getRootSceneNode()->createChildSceneNode ( "root" );

}

					SceneNodeShifter::~SceneNodeShifter ( void )
{



}

Ogre::SceneNode*	SceneNodeShifter::getNode ( void ) const
{

	return this->node;

}

void				SceneNodeShifter::setNode ( Ogre::SceneNode* node )
{

	this->node = node;

	if ( ! node )
		this->stop();

}

Ogre::Vector3		SceneNodeShifter::getPosition ( void ) const
{

    this->checkNodeSet();

	return this->node->getPosition();

}

void				SceneNodeShifter::setPosition ( const Ogre::Vector3& position )
{

    this->checkNodeSet();

	this->node->setPosition ( position );

}

Ogre::Vector3		SceneNodeShifter::getViewDirection ( void ) const
{

	return this->viewDirection;

}


void				SceneNodeShifter::setViewDirection ( const Ogre::Vector3& viewDirection )
{

	this->viewDirection = viewDirection;

}

bool				SceneNodeShifter::getIsMoving ( void ) const
{

    return this->isMoving;

}

void                SceneNodeShifter::stop ( void )
{

    this->setMoveSpeed ( Ogre::Vector3::ZERO );

}

void				SceneNodeShifter::moveBy ( const Ogre::Vector3& distance )
{

    this -> node -> translate ( distance );

}

Ogre::Vector3		SceneNodeShifter::getMoveSpeed ( void ) const
{

    return this -> moveSpeed;

}

void				SceneNodeShifter::setMoveSpeed ( const Ogre::Vector3& speed )
{

    this->moveSpeed = speed;
    this->updateIsMoving();
    this->updateOrientation();

}

void				SceneNodeShifter::setMoveSpeed ( const Ogre::Ray& moveRay, const Ogre::Real& moveSpeed )
{

    Ogre :: Vector3 speed = Segment :: getPointVector ( moveRay.getOrigin() , moveRay.getDirection() , moveSpeed );

    this -> setMoveSpeed ( speed );

}

void				SceneNodeShifter::setMoveSpeedComponent ( AXIS axis , const Ogre::Real moveSpeed )
{

	Ogre::Vector3 moveSpeedNew = this->moveSpeed;

	switch ( axis )
	{

		case AXIS_X : moveSpeedNew.x = moveSpeed; break;
		case AXIS_Y : moveSpeedNew.y = moveSpeed; break;
		case AXIS_Z : moveSpeedNew.z = moveSpeed; break;

	}

	this->setMoveSpeed ( moveSpeedNew );

}
void				SceneNodeShifter::pushTo ( const Ogre::Vector3& destination , const Ogre::Real& moveSpeed )
{

	this -> setMoveSpeed ( Segment :: getPointVector ( this -> getPosition() , destination , moveSpeed ) );
	this -> moveDestination = destination;

}

void                SceneNodeShifter::rotate ( const Ogre::Vector3& axis , const Ogre::Radian& angle , Ogre::Node::TransformSpace relativeTo )
{

    this -> node -> rotate ( axis , angle , relativeTo );
    
}

void				SceneNodeShifter::lookAt ( const Ogre::Vector3& point , Ogre::Node::TransformSpace ralativeTo , const Ogre::Vector3& viewDirection )
{

    //  `viewDirection` defaults to the value of `viewDirection` class member
	Ogre::Vector3 actualViewDirection =
		( viewDirection == Ogre :: Vector3 :: ZERO )
			?
		this->viewDirection
			:
		viewDirection;

    this -> node -> lookAt ( point , ralativeTo , actualViewDirection );
    
}

void                SceneNodeShifter::updateIsMoving ( void )
{

    //  Updates `nodeMoving` state depending on the `moveSpeed`

    this -> isMoving =	(
							this -> moveSpeed . x != 0
                                ||
                            this -> moveSpeed . y != 0
                                ||
                            this -> moveSpeed . z != 0
                        )
                            ?
                        true
                            :
                        false;

}

void                SceneNodeShifter::updateOrientation ( void )
{

    //  Updates node orientation if needed

    if ( this -> holdViewDirection )
    {

		this -> lookAt  (
                            this -> moveDestination,
                            Ogre :: Node :: TS_PARENT,
                            this -> viewDirection
                        );

    }
    
}

void                SceneNodeShifter::addTime ( Ogre::Real time )
{

    if ( this -> isMoving )
	{

		Ogre::Vector3	positionCurrent = this -> getPosition();
		Ogre::Vector3	nextStepSize = this -> moveSpeed * time;
		Ogre::Vector3	positionNext = positionCurrent + nextStepSize;

		Ogre::Real		distanceToDestination = Segment :: getLength ( positionCurrent , this -> moveDestination );
		Ogre::Real		distanceToNextStep = Segment::getLength ( positionCurrent , positionNext );

		if ( distanceToDestination <= distanceToNextStep )
		{

			this -> setPosition ( this -> moveDestination );
			this -> stop();
            
		}

		else
			this -> moveBy ( nextStepSize );

	}
    
}

void                SceneNodeShifter::checkNodeSet ( void ) const
{

    if ( ! this->node )
        throw excNodeNotDefined();

}