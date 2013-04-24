#pragma once

#include <string>
#include "SpriteDataProvider.h"
#include "Sprite.h"



namespace omoba
{



	class ASpriteFactory
	{
	
		public:
		
			virtual Sprite&					makeSprite ( const std::string& spriteName ) const = 0;
			
	};
	


	class SpriteFactory
		:
			public ASpriteFactory
	{
	
		public:
		
											SpriteFactory ( ASpriteDataProvider& spriteDataProvider , Ogre::SceneManager& sceneManager );
		
			virtual Sprite&					makeSprite ( const std::string& spriteName ) const;
	
		private:
		
			ASpriteDataProvider&			spriteDataProvider;
		
			Ogre::SceneManager&				sceneManager;
	
	};
	
	

};