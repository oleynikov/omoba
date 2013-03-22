#pragma once

#include <OgreSceneManager.h>
#include <OgreFrameListener.h>
#include "Segment.h"
#include "Ray.h"

namespace omoba
{



	typedef Ogre::Vector3						MovePoint;
	
	typedef std::vector<MovePoint>				MovePath;

	
	
	enum AXIS
	{

		AXIS_X,
		AXIS_Y,
		AXIS_Z

	};

	
	
	class SceneNodeController
		:
			public Ogre::FrameListener
	
	{

		public:
			
									SceneNodeController ( Ogre::SceneManager* sceneManager = 0 );

									~SceneNodeController ( void );

			Ogre::SceneNode*		getNode ( void ) const;

			void					setNode ( Ogre::SceneNode* node );

			Ogre::Vector3			getPosition ( void ) const;

			void					setPosition ( const Ogre::Vector3& position );

			Ogre::Vector3			getViewDirection ( void ) const;
			
			void					setViewDirection ( const Ogre::Vector3& viewDirection );
			
			bool					getIsMoving ( void ) const;
			
			void					go ( void );
			
			void					stop ( void );

			void					moveBy ( const Ogre::Vector3& distance );

			Ogre::Vector3			getMoveSpeed ( void ) const;

			void					setMoveSpeed ( const Ogre::Vector3& moveSpeed );

			void					setMoveSpeed ( const Ogre::Ray& moveRay , const Ogre::Real& moveSpeed );

			void					setMoveSpeedComponent ( const AXIS axis , const Ogre::Real moveSpeed );
			
			void					setMovePath ( const MovePath& movePath );
			
			void					pushTo ( const Ogre::Vector3& destination , const Ogre::Real& moveSpeed );
			
			void					rotate ( const Ogre::Vector3& axis , const Ogre::Radian& angle , Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT );

			void					lookAt ( const Ogre::Vector3& point , Ogre::Node::TransformSpace = Ogre::Node::TS_PARENT , const Ogre::Vector3& = Ogre::Vector3::ZERO );

			class					excNodeNotDefined { };


			
		protected:

			void					updateIsMoving ( void );

			void					updateOrientation ( void );
			
			void					checkNodeSet ( void ) const;

			virtual bool			frameRenderingQueued ( const Ogre::FrameEvent& frameEvent );


			
			Ogre::SceneNode*		node;

			bool					isMoving;

			Ogre::Vector3			moveVector;
			
			MovePath				movePath;
			
			Ogre::Real				moveSpeed;

			Ogre::Vector3			viewDirection;

			bool					holdViewDirection;

	};

};
