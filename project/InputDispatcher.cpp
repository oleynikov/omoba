#include "InputDispatcher.h"

using namespace omoba;

		InputDispatcher::InputDispatcher(Ogre::RenderWindow& renderWindow)
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

		InputDispatcher::~InputDispatcher(void)
{

	this->inputManager->destroyInputObject( this->mouse );
    this->inputManager->destroyInputObject( this->keyboard );

	OIS::InputManager::destroyInputSystem(this->inputManager);
	this->inputManager = 0;

}
void	InputDispatcher::registerListener(const InputEvent& inputEvent, InputListener* inputListener)
{

	switch ( inputEvent )
	{

		case INPUT_EVENT_KEY_PRESSED: 
			this->signalKeyPressed.connect(boost::bind(&InputListener::keyPressHandler,inputListener,_1)); break;

		case INPUT_EVENT_KEY_RELEASED: 
			this->signalKeyReleased.connect(boost::bind(&InputListener::keyReleaseHandler,inputListener,_1)); break;

		case INPUT_EVENT_MOUSE_MOVED:
			this->signalMouseMoved.connect(boost::bind(&InputListener::mouseMoveHandler,inputListener,_1)); break;

		case INPUT_EVENT_MOUSE_PRESSED:
			this->signalMousePressed.connect(boost::bind(&InputListener::mousePressHandler,inputListener,_1)); break;

		case INPUT_EVENT_MOUSE_RELEASED:
			this->signalMouseReleased.connect(boost::bind(&InputListener::mouseReleaseHandler,inputListener,_1)); break;

	}

}
void	InputDispatcher::updateRenderWindow(Ogre::RenderWindow* renderWindow)
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
bool	InputDispatcher::keyPressed(const OIS::KeyEvent& keyEvent)
{

	this->signalKeyPressed(keyEvent);
    return true;

}
bool	InputDispatcher::keyReleased(const OIS::KeyEvent& keyEvent)
{

	this->signalKeyReleased(keyEvent);
    return true;

}
bool	InputDispatcher::mouseMoved(const OIS::MouseEvent& mouseEvent)
{

	this->signalMouseMoved(mouseEvent);
	return true;

}
bool	InputDispatcher::mousePressed(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonId)
{

	this->signalMousePressed(mouseEvent);
	return true;

}
bool	InputDispatcher::mouseReleased(const OIS::MouseEvent& mouseEvent, OIS::MouseButtonID buttonId)
{

	this->signalMouseReleased(mouseEvent);
	return true;

}
bool	InputDispatcher::frameRenderingQueued(const Ogre::FrameEvent& frameEvent)
{

	this->keyboard->capture();
	this->mouse->capture();
	
	return true;

}
void	InputDispatcher::initiate(void)
{

	OIS::MouseState& mouseState = const_cast<OIS::MouseState&>(this->mouse->getMouseState());
	mouseState.X.abs = mouseState.width / 2;
	mouseState.Y.abs = mouseState.height / 2;

	OIS::MouseEvent mouseEvent(0,mouseState);

	this->signalMouseMoved(mouseEvent);

}