#include "Cursor.h"

using namespace omoba;

			Cursor::Cursor(void)
	:
		cursorLayer(0),
		cursorContainer(0)
{

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	this->cursorContainer =	(Ogre::OverlayContainer*)	overlayManager.createOverlayElementFromTemplate
														(
															"OmobaCore/Cursor",
															"Panel",
															"CursorOverlayElement"
														);

	this->cursorLayer = overlayManager.create("CursorOverlay");
	this->cursorLayer->add2D(this->cursorContainer);
	this->cursorLayer->setZOrder(100);
	this->cursorLayer->show();

}
			Cursor::~Cursor(void)
{

	if ( this->cursorContainer )
		delete this->cursorContainer;

	if ( this->cursorLayer )
		delete this->cursorLayer;

}
void		Cursor::mouseMoveHandler ( const OIS::MouseEvent& mouseEvent )
{

	this->cursorContainer->setPosition ( mouseEvent.state.X.abs , mouseEvent.state.Y.abs );

}