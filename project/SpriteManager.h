#pragma once

#include <list>
#include "InputListener.h"
#include "Sprite.h"



namespace omoba
{

	typedef std::list<Sprite&>					Sprites;
	
	typedef Sprites::iterator					SpriteItr;

	

	class SpriteManager
		:
			public InputListener
	
	{

		public:
			
												SpriteManager ( void );

												~SpriteManager ( void );

												addSprite ( const Sprite& sprite );

												removeSprite ( const Sprite& sprite );

			virtual void						mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void						mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );

			virtual void						mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult );
			
			void								setTarget ( const Ogre::Vector3& target );


			
		protected:
		
			Sprites								sprites;

			static const OIS::MouseButtonID		mouseButtonSelectUnit;

			static const OIS::MouseButtonID		mouseButtonSetUnitTarget;

	};

};
