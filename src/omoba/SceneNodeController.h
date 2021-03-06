#pragma once

#include <OgreSceneManager.h>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
#include "Segment.h"



namespace omoba
{



	typedef Ogre::Vector3							MovementPathPoint;
	
	typedef std::deque<MovementPathPoint>			MovementPath;
	
	typedef MovementPath::iterator					MovementPathPointItr;

	typedef boost::signals2::signal<void(void)>		SignalNodeReachedDestination;
	
	
	
	enum Axis
	{

		AXIS_X,
		
		AXIS_Y,
		
		AXIS_Z

	};
	
	
	
	enum MovementMode
	{
	
		MOVEMENT_MODE_BY_VECTOR,
		
		MOVEMENT_MODE_BY_PATH
		
	};
	
	
	
	class SceneNodeController
	{

		

		public:
			
											SceneNodeController ( Ogre::SceneManager& sceneManager , const Ogre::String& nodeName );

											~SceneNodeController ( void );


			Ogre::SceneNode&				getNode ( void ) const;

			const Ogre::Vector3&			getNodeViewDirection ( void ) const;

			bool							getNodeMoving ( void ) const;

			const Ogre::Vector3				getNodePosition ( void ) const;

			const Ogre::Vector3&			getNodeMovementVector ( void ) const;
			
			const MovementPath&				getNodeMovementPath ( void ) const;
			
			const Ogre::Real&				getNodeMovementSpeed ( void ) const;
			
			
			void							setNode ( Ogre::SceneNode& node );

			void							setNodeViewDirection ( const Ogre::Vector3& nodeViewDirection );
			
			void							setNodeHoldViewDirection ( const bool nodeHoldViewDirection );
			
			void							setNodeMoving ( const bool nodeMoving );

			void							setNodePosition ( const Ogre::Vector3& nodePosition );

			void							setNodeMovementMode ( const MovementMode nodeMovementMode );

			void							setNodeMovementVector ( const Ogre::Vector3& nodeMovementVector );

			void							setNodeMovementVector ( const Ogre::Ray& nodeMovementRay , const Ogre::Real& nodeMovementSpeed );

			void							setNodeMovementVectorComponent ( const Axis nodeMovementVectorComponent , const Ogre::Real& nodeMovementVectorComponentValue );

			void							setNodeMovementPath ( const MovementPath& nodeMovementPath );
			
			void							setNodeMovementPath ( const Ogre::Vector3& nodeMovementDestination );

			void							setNodeMovementSpeed ( const Ogre::Real& nodeMovementSpeed );

			void							setNodeMovementLooped ( const bool nodeMovementLooped );

		
			void							moveNodeBy ( const Ogre::Vector3& nodeMovementDistance );

			void							moveNodeBy ( const Ogre::Ray& nodeMovementRay , const Ogre::Real& nodeMovementDistance );

			void							rotateNode ( const Ogre::Vector3& nodeRotationAxis , const Ogre::Radian& nodeRotationAngle , Ogre::Node::TransformSpace nodeRotationTransformSpace = Ogre::Node::TS_PARENT );

			void							aimNodeAt ( const Ogre::Vector3& nodeTargetPoint , Ogre::Node::TransformSpace nodeTransformSpace = Ogre::Node::TS_PARENT , const Ogre::Vector3& nodeViewDirection = Ogre::Vector3::ZERO );

			void							addNodeMovementPathPoint ( const Ogre::Vector3 nodeMovementPathPoint );


			class							ExcNodeNotDefined { };

			
			
		protected:
		
			void							addNodeMovementTime ( const Ogre::Real& movementTime );

			SignalNodeReachedDestination	signalNodeReachedDestination;
		

		
		private:

			void							checkNodeDefined ( void ) const;

			void							updateNodeOrientation ( void );


			
			Ogre::SceneNode*				node;

			Ogre::Vector3					nodeViewDirection;

			bool							nodeHoldViewDirection;

			bool							nodeMoving;
			
			MovementMode					nodeMovementMode;

			Ogre::Vector3					nodeMovementVector;
			
			MovementPath					nodeMovementPath;
			
			Ogre::Real						nodeMovementSpeed;

			bool							nodeMovementLooped;
			
			
			
	};

};
