#include "InputDispatcher.h"

		omoba::InputDispatcher::InputDispatcher(Ogre::RenderWindow& renderWindow)
	:
		inputManager(0),
		keyboard(0),
		mouse(0)
{

	size_t windowHandler = 0;
    std::ostringstream windowHandlerString;
	renderWindow.getCustomAttribute("WINDOW", &windowHandler);
    windowHandlerString << windowHandler;
	
	OIS::ParamList parameters;
    parameters.insert(std::make_pair(std::string("WINDOW"),windowHandlerString.str()));

	this->inputManager = OIS::InputManager::createInputSystem(parameters);
	this->keyboard = static_cast<OIS::Keyboard*>(this->inputManager->createInputObject(OIS::OISKeyboard,true));
	this->mouse = static_cast<OIS::Mouse*>(this->inputManager->createInputObject(OIS::OISMouse,true));

	this->keyboard->setEventCallback(this);
	this->mouse->setEventCallback(this);

}

		omoba::InputDispatcher::~InputDispatcher(void)
{

	this->inputManager->destroyInputObject( this->mouse );
    this->inputManager->destroyInputObject( this->keyboard );

	OIS::InputManager::destroyInputSystem(this->inputManager);
	this->inputManager = 0;

}
void	omoba::InputDispatcher::registerListener(const omoba::InputEvent& inputEvent, omoba::AInputListener* inputListener)
{

	switch ( inputEvent )
	{

		case omoba::INPUT_EVENT_KEY_PRESSED: 
			this->signalKeyPressed.connect(boost::bind(&omoba::AInputListener::keyPressHandler,inputListener,_1)); break;

		case omoba::INPUT_EVENT_KEY_RELEASED: 
			this->signalKeyReleased.connect(boost::bind(&omoba::AInputListener::keyReleaseHandler,inputListener,_1)); break;

		case omoba::INPUT_EVENT_MOUSE_MOVED:
			this->signalMouseMoved.connect(boost::bind(&omoba::AInputListener::mouseMoveHandler,inputListener,_1)); break;

		case omoba::INPUT_EVENT_MOUSE_PRESSED:
			this->signalMousePressed.connect(boost::bind(&omoba::AInputListener::mousePressHandler,inputListener,_1)); break;

		case omoba::INPUT_EVENT_MOUSE_RELEASED:
			this->signalMouseReleased.connect(boost::bind(&omoba::AInputListener::mouseReleaseHandler,inputListener,_1)); break;

	}

}
void	omoba::InputDispatcher::updateRenderWindow(Ogre::RenderWindow* renderWindow)
{

	unsigned int
		width,
		height,
		depth;

    int
		left,
		top;

    renderWindow->getMetrics ( width , height , depth , left , top );

	const OIS::MouseState& mousState = this->mouse->getMouseState();
    mousState.width = width;
    mousState.height = height;

}
bool	omoba::InputDispatcher::keyPressed(const OIS::KeyEvent& keyEvent)
{

	this->signalKeyPressed(keyEvent);
    return true;

}
bool	omoba::InputDispatcher::keyReleased(const OIS::KeyEvent& keyEvent)
{

	this->signalKeyReleased(keyEvent);
    return true;

}
bool	omoba::InputDispatcher::mouseMoved(const OIS::MouseEvent& mouseEvent)
{

	this->signalMouseMoved(mouseEvent);
	return true;

}
bool	omoba::InputDispatcher::mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonId)
{

	this->signalMousePressed(mouseEvent);
	return true;

}
bool	omoba::InputDispatcher::mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonId)
{

	this->signalMouseReleased(mouseEvent);
	return true;

}
bool	omoba::InputDispatcher::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
{

	this->keyboard->capture();
	this->mouse->capture();
	
	return true;

}