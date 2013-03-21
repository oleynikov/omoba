#include "SceneNodeController.h"

using namespace omoba;

					SceneNodeController::SceneNodeController ( Ogre::SceneManager* sceneManager )
                        :
                            node                ( 0 ),
                            isMoving            ( false ),
                            moveSpeed           ( Ogre::Vector3::ZERO ),
                            moveDestination     ( Ogre::Vector3::ZERO ),
                            viewDirection       ( Ogre::Vector3::UNIT_Z ),
                            holdViewDirection   ( true )
{

    if ( sceneManager )
    	this->node = sceneManager->getRootSceneNodeController()->createChildSceneNodeController ( "root" );

}

					SceneNodeController::~SceneNodeController ( void )
{



}

Ogre::SceneNodeController*	SceneNodeController::getNode ( void ) const
{

	return this->node;

}

void				SceneNodeController::setNode ( Ogre::SceneNodeController* node )
{

	this->node = node;

	if ( ! node )
		this->stop();

}

Ogre::Vector3		SceneNodeController::getPosition ( void ) const
{

    this->checkNodeSet();

	return this->node->getPosition();

}

void				SceneNodeController::setPosition ( const Ogre::Vector3& position )
{

    this->checkNodeSet();

	this->node->setPosition ( position );

}

Ogre::Vector3		SceneNodeController::getViewDirection ( void ) const
{

	return this->viewDirection;

}

void				SceneNodeController::setViewDirection ( const Ogre::Vector3& viewDirection )
{

	this->viewDirection = viewDirection;

}

bool				SceneNodeController::getIsMoving ( void ) const
{

    return this->isMoving;

}

void                SceneNodeController::stop ( void )
{

    this->setMoveSpeed ( Ogre::Vector3::ZERO );

}

void				SceneNodeController::moveBy ( const Ogre::Vector3& distance )
{

    this -> node -> translate ( distance );

}

Ogre::Vector3		SceneNodeController::getMoveSpeed ( void ) const
{

    return this -> moveSpeed;

}

void				SceneNodeController::setMoveSpeed ( const Ogre::Vector3& speed )
{

    this->moveSpeed = speed;
    this->updateIsMoving();
    this->updateOrientation();

}

void				SceneNodeController::setMoveSpeed ( const Ogre::Ray& moveRay, const Ogre::Real& moveSpeed )
{

    Ogre :: Vector3 speed = Segment :: getPointVector ( moveRay.getOrigin() , moveRay.getDirection() , moveSpeed );

    this -> setMoveSpeed ( speed );

}

void				SceneNodeController::setMoveSpeedComponent ( AXIS axis , const Ogre::Real moveSpeed )
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

void				SceneNodeController::pushTo ( const Ogre::Vector3& destination , const Ogre::Real& moveSpeed )
{

	this -> setMoveSpeed ( Segment :: getPointVector ( this -> getPosition() , destination , moveSpeed ) );
	this -> moveDestination = destination;

}

void                SceneNodeController::rotate ( const Ogre::Vector3& axis , const Ogre::Radian& angle , Ogre::Node::TransformSpace relativeTo )
{

    this -> node -> rotate ( axis , angle , relativeTo );
    
}

void				SceneNodeController::lookAt ( const Ogre::Vector3& point , Ogre::Node::TransformSpace ralativeTo , const Ogre::Vector3& viewDirection )
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

void                SceneNodeController::updateIsMoving ( void )
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

void                SceneNodeController::updateOrientation ( void )
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

void                SceneNodeController::checkNodeSet ( void ) const
{

    if ( ! this->node )
        throw excNodeNotDefined();

}

bool                SceneNodeController::frameRenderingQueued ( const Ogre::FrameEvent& frameEvent )
{

    if ( this -> isMoving )
	{

		Ogre::Vector3	positionCurrent = this -> getPosition();
		Ogre::Vector3	nextStepSize = this -> moveSpeed * frameEvent.timeSinceLastFrame;
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

    return true;
    
}