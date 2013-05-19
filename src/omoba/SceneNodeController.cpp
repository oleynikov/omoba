#include "SceneNodeController.h"

using namespace omoba;

							SceneNodeController::SceneNodeController ( Ogre::SceneManager& sceneManager , const Ogre::String& nodeName )
								:
									node					( NULL ),
									nodeViewDirection		( Ogre::Vector3::UNIT_Z ),
									nodeHoldViewDirection	( true ),
									nodeMoving				( false ),
									nodeMovementMode		( MOVEMENT_MODE_BY_PATH ),
									nodeMovementVector		( Ogre::Vector3::ZERO ),
									nodeMovementSpeed		( NULL ),
									nodeMovementLooped		( false )
{

	std::string sceneNodeName = OgreExtension::SceneManager::getAvailableEntityName(sceneManager,nodeName);
 	this->node = sceneManager.getRootSceneNode()->createChildSceneNode ( sceneNodeName );

}

							SceneNodeController::~SceneNodeController ( void )
{



}


Ogre::SceneNode&			SceneNodeController::getNode ( void ) const
{

	this->checkNodeDefined();
	
	return *this->node;

}

const Ogre::Vector3&		SceneNodeController::getNodeViewDirection ( void ) const
{

	return this->nodeViewDirection;

}

void						SceneNodeController::setNodeHoldViewDirection ( const bool nodeHoldViewDirection )
{

	this->nodeHoldViewDirection = nodeHoldViewDirection;

}

bool						SceneNodeController::getNodeMoving ( void ) const
{

	return this->nodeMoving;

}

const Ogre::Vector3			SceneNodeController::getNodePosition ( void ) const
{

	this->checkNodeDefined();

	return this->node->getPosition();

}

const Ogre::Vector3&		SceneNodeController::getNodeMovementVector ( void ) const
{

	return this->nodeMovementVector;

}

const MovementPath&			SceneNodeController::getNodeMovementPath ( void ) const
{

	return this->nodeMovementPath;
	
}

const Ogre::Real&			SceneNodeController::getNodeMovementSpeed ( void ) const
{

	return this->nodeMovementSpeed;
	
}


void						SceneNodeController::setNode ( Ogre::SceneNode& node )
{

	this->node = &node;

}

void						SceneNodeController::setNodeViewDirection ( const Ogre::Vector3& nodeViewDirection )
{

	this->nodeViewDirection = nodeViewDirection;

}

void						SceneNodeController::setNodeMoving ( bool nodeMoving )
{

	this->nodeMoving = nodeMoving;
	
	if ( nodeMoving )
		this->updateNodeOrientation();

}

void						SceneNodeController::setNodePosition ( const Ogre::Vector3& nodePosition )
{

	this->checkNodeDefined();

	this->node->setPosition ( nodePosition );

}

void						SceneNodeController::setNodeScale ( const Ogre::Vector3& nodeScale )
{

	this->checkNodeDefined();

	this->node->setScale(nodeScale);

}

void						SceneNodeController::setNodeMovementMode ( const MovementMode nodeMovementMode )
{

	this->nodeMovementMode = nodeMovementMode;

}

void						SceneNodeController::setNodeMovementVector ( const Ogre::Vector3& nodeMovementVector )
{

	this->nodeMovementVector = nodeMovementVector;

}

void						SceneNodeController::setNodeMovementVector ( const Ogre::Ray& nodeMovementRay , const Ogre::Real& nodeMovementSpeed )
{

	o__O::PointF3 nodePositionCurrent = OgreAdaptor::Vector3(nodeMovementRay.getOrigin()).toPointF3();
	o__O::PointF3 nodeDestination = OgreAdaptor::Vector3(nodeMovementRay.getDirection()).toPointF3();
	o__O::PointF3 nodePositionNext = o__O::SegmentF3(nodePositionCurrent,nodeDestination).getInteriorPoint(nodeMovementSpeed);

	OgreAdaptor::Vector3 nodeMovementVector = nodePositionNext - nodePositionCurrent;

	this->setNodeMovementVector(nodeMovementVector);

}

void						SceneNodeController::setNodeMovementVectorComponent ( const Axis nodeMovementVectorComponent , const Ogre::Real& nodeMovementVectorComponentValue )
{

	Ogre::Vector3 nodeMovementVectorNew = this->nodeMovementVector;

	switch ( nodeMovementVectorComponent )
	{

		case AXIS_X : nodeMovementVectorNew.x = nodeMovementVectorComponentValue; break;
		
		case AXIS_Y : nodeMovementVectorNew.y = nodeMovementVectorComponentValue; break;
		
		case AXIS_Z : nodeMovementVectorNew.z = nodeMovementVectorComponentValue; break;

	}

	this->setNodeMovementVector ( nodeMovementVectorNew );

}

void						SceneNodeController::setNodeMovementPath ( const MovementPath& nodeMovementPath )
{

	this->nodeMovementPath = nodeMovementPath;
	
}

void						SceneNodeController::setNodeMovementPath ( const Ogre::Vector3& nodeMovementDestination )
{

	this->nodeMovementPath.clear();
	this->nodeMovementPath.push_back(this->getNodePosition());
	this->nodeMovementPath.push_back(nodeMovementDestination);

}

void						SceneNodeController::setNodeMovementSpeed ( const Ogre::Real& nodeMovementSpeed )
{

	this->nodeMovementSpeed = nodeMovementSpeed;

}


void						SceneNodeController::setNodeMovementLooped ( const bool nodeMovementLooped )
{

	this->nodeMovementLooped = nodeMovementLooped;

}

void						SceneNodeController::moveNodeBy ( const Ogre::Vector3& nodeMovementDistance )
{

	this->checkNodeDefined();
	
	this->node->translate ( nodeMovementDistance );

}

void						SceneNodeController::moveNodeBy ( const Ogre::Ray& nodeMovementRay , const Ogre::Real& nodeMovementDistance )
{

	o__O::PointF3 nodePositionCurrent = OgreAdaptor::Vector3(nodeMovementRay.getOrigin()).toPointF3();
	o__O::PointF3 nodeDestination = OgreAdaptor::Vector3(nodeMovementRay.getDirection()).toPointF3();
	o__O::PointF3 nodeMovementDelta = o__O::SegmentF3(nodePositionCurrent,nodeDestination).getInteriorPoint(nodeMovementDistance);

	this->moveNodeBy(OgreAdaptor::Vector3(nodeMovementDelta));

}

void						SceneNodeController::rotateNode ( const Ogre::Vector3& nodeRotationAxis , const Ogre::Radian& nodeRotationAngle , Ogre::Node::TransformSpace nodeRotationTransformSpace )
{

	this->checkNodeDefined();
	
	this->node->rotate ( nodeRotationAxis , nodeRotationAngle , nodeRotationTransformSpace );
	
}

void						SceneNodeController::rotateNode ( const Ogre::Vector3& nodeRotationAxis , const float nodeRotationAngle , Ogre::Node::TransformSpace nodeRotationTransformSpace )
{

	Ogre::Radian nodeRotationRadianAngle(nodeRotationAngle);

	this->rotateNode(nodeRotationAxis,nodeRotationRadianAngle,nodeRotationTransformSpace);

}

void						SceneNodeController::aimNodeAt ( const Ogre::Vector3& nodeTargetPoint , Ogre::Node::TransformSpace nodeTransformSpace , const Ogre::Vector3& nodeViewDirection )
{

	this->checkNodeDefined();
	
	//  `viewDirection` defaults to the value of `viewDirection` class member
	Ogre::Vector3 nodeActualViewDirection =
		( nodeViewDirection == Ogre::Vector3::ZERO )
			?
		this->nodeViewDirection
			:
		nodeViewDirection;

	this->node->lookAt ( nodeTargetPoint , nodeTransformSpace , nodeActualViewDirection );
	
}

void						SceneNodeController::addNodeMovementPathPoint ( const Ogre::Vector3 nodeMovementPathPoint )
{

	this->nodeMovementPath.push_back(nodeMovementPathPoint);

}

void						SceneNodeController::addNodeMovementTime ( const Ogre::Real& movementTime )
{

	this->checkNodeDefined();

	if ( this->nodeMoving )
	{

		switch ( this->nodeMovementMode )
		{

			case MOVEMENT_MODE_BY_PATH:
			{

				Ogre::Vector3	positionCurrent = this->getNodePosition();
				Ogre::Real		nextStepDistance = this->nodeMovementSpeed * movementTime;
				Ogre::Real		nextPathPointDistance = positionCurrent.distance(this->nodeMovementPath.front());
				
				this->updateNodeOrientation();

				if ( nextPathPointDistance <= nextStepDistance )
				{

					this->setNodePosition ( this->nodeMovementPath.front() );

					if ( ! this->nodeMovementLooped )
					{
						this->nodeMovementPath.pop_front();

						if ( this->nodeMovementPath.empty() )
						{

							this->setNodeMoving ( false );
							this->signalNodeReachedDestination();

						}

					}

					else
					{

						Ogre::Vector3 pointCurrent = this->nodeMovementPath.front();
						this->nodeMovementPath.push_back(pointCurrent);
						this->nodeMovementPath.pop_front();

					}
						
				}

				else
					this->moveNodeBy ( Ogre::Ray ( positionCurrent , this->nodeMovementPath.front() ) , nextStepDistance );

				break;

			}

			case MOVEMENT_MODE_BY_VECTOR:
			{

				this->moveNodeBy ( this->nodeMovementVector * movementTime );

				break;

			}

		}

	}

}


void						SceneNodeController::checkNodeDefined ( void ) const
{

	if ( ! this->node )
		throw ExcNodeNotDefined();

}

void						SceneNodeController::updateNodeOrientation ( void )
{

	//  Updates node orientation if needed

	if ( this->nodeHoldViewDirection )
	{
	
		Ogre::Vector3 nodeTargetPoint;
	
		switch ( this->nodeMovementMode )
		{
		
			case MOVEMENT_MODE_BY_VECTOR:	nodeTargetPoint = this->getNodePosition() + this->nodeMovementVector; break;
			
			case MOVEMENT_MODE_BY_PATH:		nodeTargetPoint = this->nodeMovementPath.front(); break;
			
		}
		
		this->aimNodeAt
		(
			nodeTargetPoint,
			Ogre::Node::TS_PARENT,
			this->nodeViewDirection
		);

	}
	
}