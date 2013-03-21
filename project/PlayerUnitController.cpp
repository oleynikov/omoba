#include "PlayerUnitController.h"
#include "PlayerUnit.h"

using namespace omoba;



const PlayerUnitController::mouseButtonSelectUnit      = OIS::MouseButtonID::MB_Left;

const PlayerUnitController::mouseButtonSetUnitTarget   = OIS::MouseButtonID::MB_Right;



			PlayerUnitController::PlayerUnitController ( void )
{
                
}

			PlayerUnitController::~PlayerUnitController(void)
{

}

void        PlayerUnitController::addUnit ( const PlayerUnit& playerUnit )
{

    this->playerUnits.push_back ( playerUnit );

}

void        PlayerUnitController::removeUnit ( const PlayerUnit& playerUnit )
{

    this->playerUnits.remove ( playerUnit );
    
}

void		PlayerUnitController::mousePressHandler(const OIS::MouseEvent& mouseEvent)
{

    



}

void		PlayerUnitController::mouseReleaseHandler(const OIS::MouseEvent& mouseEvent)
{



}


bool		PlayerUnitController::frameRenderingQueued ( const Ogre::FrameEvent& frameEvent )
{

	this->addTime ( frameEvent.timeSinceLastFrame );

	return true;

}