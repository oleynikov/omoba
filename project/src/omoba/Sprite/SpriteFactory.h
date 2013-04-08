#pragma once

#include "Sprite.h"



namespace omoba
{

	class SpriteFactory
	{
	
		public:
		
			Sprite& makeSprite ( const std::string& spriteName );
	
		private:
		
			SpriteDataProvider*		spriteDataProvider;
			
			SpriteDataParser*		spriteDataParser;
			
			Ogre::SceneManager*		sceneManager;
	
	};

};