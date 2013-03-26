#pragma once

#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include "Segment.h"
#include "Ray.h"

namespace omoba
{



	typedef Ogre::Vector3						MovePoint;
	
	typedef std::deque<MovePoint>				MovePath;

	
	
	enum AXIS
	{

		AXIS_X,
		
		AXIS_Y,
		
		AXIS_Z

	};
	
	
	
	enum SceneNodeMoveMode
	{
	
		MOVE_MODE_BY_VECTOR,
		
		MOVE_MODE_BY_PATH
		
	};

	
	
	class SceneNodeController
		:
			public Ogre::FrameListener
	
	{
	
	
	
		class							excNodeNotDefined { };

		

		public:
			
										SceneNodeController ( Ogre::SceneManager* sceneManager = 0 );

										~SceneNodeController ( void );

			
			Ogre::SceneNode&			getNode ( void ) const;

			const Ogre::Vector3&		getViewDirection ( void ) const;

			bool&						getMoving ( void ) const;

			const Ogre::Vector3			getPosition ( void ) const;

			const Ogre::Vector3&		getMoveVector ( void ) const;
			
			const MovePath&				getMovePath ( void ) const;
			
			const Ogre::Real&			getMoveSpeed ( void ) const;
			
			
			void						setNode ( Ogre::SceneNode& node );

			void						setViewDirection ( const Ogre::Vector3& viewDirection );
			
			void						setMoving ( bool isMoving );

			void						setPosition ( const Ogre::Vector3& position );

			void						setMoveVector ( const Ogre::Vector3& moveVector );

			void						setMoveVector ( const Ogre::Ray& moveRay , const Ogre::Real& moveSpeed );

			void						setMoveVectorComponent ( const AXIS axis , const Ogre::Real value );

			void						setMovePath ( const MovePath& movePath );
			
			void						setMovePath ( const Ogre::Vector3 destination );

		
			void						moveBy ( const Ogre::Vector3& distance );

			void						moveBy ( const Ogre::Ray& ray , const Ogre::Real& distance );

			void						rotate ( const Ogre::Vector3& axis , const Ogre::Radian& angle , Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT );

			void						lookAt ( const Ogre::Vector3& point , Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT , const Ogre::Vector3& = Ogre::Vector3::ZERO );

			void						switchMoveMode ( const SceneNodeMoveMode moveMode );

			
			
		protected:

			void						checkNodeSet ( void ) const;

			void						updateOrientation ( void );

			virtual bool				frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );


			
			Ogre::SceneNode*			node;

			Ogre::Vector3				viewDirection;

			bool						holdViewDirection;

			bool						isMoving;
			
			SceneNodeMoveMode			moveMode;

			Ogre::Vector3				moveVector;
			
			MovePath					movePath;
			
			Ogre::Real					moveSpeed;
			
			
			
	};

};
