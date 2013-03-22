#include "SpriteManager.h"

using namespace omoba;



const		SpriteManager::mouseButtonSelectUnit      = OIS::MouseButtonID::MB_Left;

const		SpriteManager::mouseButtonSetUnitTarget   = OIS::MouseButtonID::MB_Right;



			SpriteManager::SpriteManager ( void )
{
                
}

			SpriteManager::~SpriteManager(void)
{

}

void        SpriteManager::addUnit ( const Sprite& sprite )
{

    this->playerUnits.push_back ( playerUnit );

}

void        SpriteManager::removeUnit ( const Sprite& sprite )
{

    this->playerUnits.remove ( playerUnit );
    
}

void        SpriteManager::mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{


}

void		SpriteManager::mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{

	Ogre::RaySceneQueryResult::iterator resultItr = rayQueryResult.begin();
	
	for ( ; resultItr != rayQueryResult.end() ; resultItr++ )
	{

		if ( resultItr->movable ) && resultItr->movable->getParentSceneNode() == this->getNode() )
			return true;
			
	}
	









	SpriteItr spriteItr = this->sprites.begin();
	
	for ( ; spriteItr != this->sprites.end() ; spriteItr++ )
	{
	
		Sprite& spriteRef = *spriteItr;
	
		if ( spriteRef.getSelected() )
		{
		
			spriteRef.pushTo ( target );
			
		}
	
	}

	

    



}

void		SpriteManager::mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{



}

void		SpriteManager::setTarget ( const Ogre::Vector3& target )
{

	SpriteItr spriteItr = this->sprites.begin();
	
	for ( ; spriteItr != this->sprites.end() ; spriteItr++ )
	{
	
		Sprite& spriteRef = *spriteItr;
	
		if ( spriteRef.getSelected() )
		{
		
			spriteRef.pushTo ( target );
			
		}
	
	}
	
}