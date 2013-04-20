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
		
											SpriteFactory ( ASpriteDataProvider& spriteDataProvider , Ogre::SceneManager& sceneManager );
		
			virtual Sprite&					makeSprite ( const std::string& spriteName );
	
		private:
		
			ASpriteDataProvider&			spriteDataProvider;
		
			Ogre::SceneManager&				sceneManager;
	
	};
	
	

};