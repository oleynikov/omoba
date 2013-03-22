#include "SceneNodeController.h"

using namespace omoba;

					SceneNodeController::SceneNodeController ( Ogre::SceneManager* sceneManager )
                        :
                            node                ( 0 ),
                            viewDirection       ( Ogre::Vector3::UNIT_Z ),
                            holdViewDirection   ( true ),
                            isMoving            ( false ),
							moveMode			( MOVE_BY_PATH ),
                            moveVector			( Ogre::Vector3::ZERO ),
							moveSpeed			( 0 )
{

    if ( sceneManager )
    	this->node = sceneManager->getRootSceneNode()->createChildSceneNode ( "OMOBA_ROOT_NODE" );

}

					SceneNodeController::~SceneNodeController ( void )
{



}


Ogre::SceneNode&	SceneNodeController::getNode ( void ) const
{

	this->checkNodeSet();
	
	return *(this->node);

}

Ogre::Vector3&		SceneNodeController::getViewDirection ( void ) const
{

	return this->viewDirection;

}

bool				SceneNodeController::getIsMoving ( void ) const
{

    return this->isMoving;

}

Ogre::Vector3&		SceneNodeController::getPosition ( void ) const
{

    this->checkNodeSet();

	return this->node->getPosition();

}

Ogre::Vector3&		SceneNodeController::getMoveVector ( void ) const
{

    return this->moveVector;

}

MovePath&			SceneNodeController::getMovePath ( void ) const
{

	return this->movePath;
	
}

Ogre::Real&			SceneNodeController::getMoveSpeed ( void ) const
{

	return this->moveSpeed;
	
}


void				SceneNodeController::setNode ( Ogre::SceneNode& node )
{

	this->node = *node;

}

void				SceneNodeController::setViewDirection ( const Ogre::Vector3& viewDirection )
{

	this->viewDirection = viewDirection;

}

void				SceneNodeController::setMoving ( bool isMoving )
{

	this->isMoving = isMoving;
	
	this->updateOrientation();

}

void				SceneNodeController::setPosition ( const Ogre::Vector3& position )
{

    this->checkNodeSet();

	this->node->setPosition ( position );

}

void				SceneNodeController::setMoveVector ( const Ogre::Vector3& moveVector )
{

    this->moveVector = moveVector;

}

void				SceneNodeController::setMoveVector ( const Ogre::Ray& moveRay , const Ogre::Real& moveSpeed );
{

    this->setMoveVector ( Segment::getPointVector ( moveRay.getOrigin() , moveRay.getDirection() , moveSpeed ) );

}

void				SceneNodeController::setMoveVectorComponent ( const AXIS axis , const Ogre::Real value )
{

	Ogre::Vector3 moveVectorNew = this->moveVector;

	switch ( axis )
	{

		case AXIS_X : moveVectorNew.x = value; break;
		
		case AXIS_Y : moveVectorNew.y = value; break;
		
		case AXIS_Z : moveVectorNew.z = value; break;

	}

	this->setMoveVector ( moveVectorNew );

}

void				SceneNodeController::setMovePath ( const MovePath& movePath )
{

	this->movePath = movePath;
	
}

void				SceneNodeController::setMovePath ( const Ogre::Vector3 destination )
{

	this->movePath.clear();
	
	this->movePath.push_back ( destination );

}


void				SceneNodeController::moveBy ( const Ogre::Vector3& distance )
{

	this->checkNodeSet();
	
    this->node->translate ( distance );

}

void                SceneNodeController::rotate ( const Ogre::Vector3& axis , const Ogre::Radian& angle , Ogre::Node::TransformSpace relativeTo )
{

	this->checkNodeSet();
	
    this->node->rotate ( axis , angle , relativeTo );
    
}

void				SceneNodeController::lookAt ( const Ogre::Vector3& point , Ogre::Node::TransformSpace ralativeTo , const Ogre::Vector3& viewDirection )
{

	this->checkNodeSet();
	
    //  `viewDirection` defaults to the value of `viewDirection` class member
	Ogre::Vector3 actualViewDirection =
		( viewDirection == Ogre::Vector3::ZERO )
			?
		this->viewDirection
			:
		viewDirection;

    this->node->lookAt ( point , ralativeTo , actualViewDirection );
    
}


void                SceneNodeController::checkNodeSet ( void ) const
{

    if ( ! this->node )
        throw excNodeNotDefined();

}

void                SceneNodeController::updateOrientation ( void )
{

    //  Updates node orientation if needed

    if ( this->holdViewDirection )
    {
	
		Ogre::Vector3 lookPoint;
	
		switch ( this->moveMode )
		{
		
			case MOVE_BY_VECTOR:	lookPoint = this->getPosition() + this->moveVector; break;
			
			case MOVE_BY_PATH:		this->movePath.front(); break;
			
		}
		
		this->lookAt
		(
			this->lookPoint,
			Ogre::Node::TS_PARENT,
			this->viewDirection
		);

    }
    
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

void				SceneNodeController::switchMoveMode ( const SceneNodeMoveMode moveMode )
{

	this->moveMove = moveMode;

}