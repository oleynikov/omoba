#pragma once

#include <string>
#include "SpriteDataProvider.h"
#include "SpriteDataParser.h"
#include "Sprite.h"



namespace omoba
{



	class ASpriteFactory
	{
	
		public:
		
			virtual Sprite&			makeSprite ( const std::string& spriteName ) = 0;
			
	};
	


	class SpriteFactory
		:
			public ASpriteFactory
	{
	
		public:
		
									SpriteFactory ( const ASpriteDataProvider& spriteDataProvider , const ASpriteDataParser& spriteDataParser , const Ogre::SceneManager& sceneManager );
		
			virtual Sprite&			makeSprite ( const std::string& spriteName );
	
		private:

			ASpriteDataProvider&	spriteDataProvider;
		
			ASpriteDataParser&		spriteDataParser;
			
			Ogre::SceneManager&		sceneManager;
	
	};
	
	

};