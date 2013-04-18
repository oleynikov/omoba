#pragma once

#include <string>
#include "SpriteDataProvider.h"
#include "SpriteDataGetter.h"
#include "Sprite.h"



namespace omoba
{



	class ASpriteFactory
	{
	
		public:
		
			virtual Sprite&					makeSprite ( const std::string& spriteName ) = 0;
			
	};
	


	class SpriteFactory
		:
			public ASpriteFactory
	{
	
		public:
		
											SpriteFactory ( const ASpriteDataProvider& spriteDataProvider , Ogre::SceneManager& sceneManager );
		
			virtual Sprite&					makeSprite ( const std::string& spriteName );
	
		private:
		
			void							configureSprite ( Sprite& sprite );
			
			void							configureSpriteParameters ( Sprite& sprite );

			const ASpriteDataProvider&		spriteDataProvider;
		
			Ogre::SceneManager&				sceneManager;
	
	};
	
	

};