#include "InputManager.h"

		omoba::InputManager::InputManager(size_t windowHandler)
	:
		inputManager(0),
		keyboard(0),
		mouse(0)
{

	OIS::ParamList parameters;
    std::ostringstream windowHandlerString;
    windowHandlerString << windowHandler;
    parameters.insert(std::make_pair(std::string("WINDOW"), windowHandlerString.str()));

	this->inputManager = OIS::InputManager::createInputSystem(parameters);
	this->keyboard = static_cast<OIS::Keyboard*>(this->inputManager->createInputObject(OIS::OISKeyboard,true));
	this->mouse = static_cast<OIS::Mouse*>(this->inputManager->createInputObject(OIS::OISMouse,true));

	this->keyboard->setEventCallback(this);
	this->mouse->setEventCallback(this);

}

		omoba::InputManager::~InputManager(void)
{
}
void	omoba::InputManager::addListener(omoba::AInputListener* listener)
{

	if(listener)
		this->listeners.push_back(listener);

}
void	omoba::InputManager::removeListener(omoba::AInputListener* listener)
{

	if(listener)
		this->listeners.remove(listener);

}
bool	omoba::InputManager::keyPressed(const OIS::KeyEvent& keyEvent)
{
    return true;
}
bool	omoba::InputManager::keyReleased(const OIS::KeyEvent& keyEvent)
{
    return true;
}
bool	omoba::InputManager::mouseMoved(const OIS::MouseEvent& mouseEvent)
{
	return true;
}
bool	omoba::InputManager::mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonId)
{
	return true;
}
bool	omoba::InputManager::mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonId)
{
	return true;
}

bool	omoba::InputManager::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
{

	this->keyboard->capture();
	this->mouse->capture();
	
	return true;

}
void	omoba::InputManager::listenersNotify(void)
{

	ListenerItr itr = this->listeners.begin();

	for ( ; itr != this->listeners.end() ; ++itr )
	{

		return;


	}

}