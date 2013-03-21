#include "Camera.h"

using namespace omoba;

const Ogre::Real				Camera::scrollSpeed = 200;
const int						Camera::scrollAreaSize = 10;
const OIS::MouseButtonID		Camera::cameraCaptureButton = OIS::MouseButtonID::MB_Middle;



								Camera::Camera ( Ogre::SceneManager* sceneManager )
									:
										SceneNodeShifter ( sceneManager ),
										cameraCaptured ( false ),
										camera ( 0 )
{

	this->holdViewDirection = false;
	this->viewDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;

	this->camera = sceneManager->createCamera ( "camera" );
	this->node->attachObject ( this->camera );

}

								Camera::~Camera ( void )
{

}

Ogre::Camera*					Camera::getCamera ( void ) const
{

	return this->camera;

}

void							Camera::mouseMoveHandler ( const OIS::MouseEvent& mouseEvent )
{

	//  Captured camera mode
	if ( this->cameraCaptured )
	{

		int mouseDeltaX = mouseEvent.state.X.rel;
		int mouseDeltaY = mouseEvent.state.Y.rel;

		this->moveBy ( Ogre::Vector3 ( mouseDeltaX , 0 , mouseDeltaY ) );

		return;

	}



	//  Standard mode

	//	window dimentions
	int windowSizeX = mouseEvent.state.width;
	int windowSizeY = mouseEvent.state.height;

	//	New mouse poisition
	int mousePosX = mouseEvent.state.X.abs;
	int mousePosY = mouseEvent.state.Y.abs;

	//  If the cursor is in the scroll area than we start moving the camera.
    //  When the cursor leaves the scroll area we stop the camera

	//	X - axix
	if ( mousePosX <= Camera::scrollAreaSize )
		this->setMoveSpeedComponent ( AXIS_X , -1 * Camera::scrollSpeed );

	else if ( mousePosX >= windowSizeX - omoba::Camera::scrollAreaSize )
		this->setMoveSpeedComponent ( AXIS_X , Camera::scrollSpeed );

	else
		this->setMoveSpeedComponent ( AXIS_X , 0 );

	//	Y - axis
	if ( mousePosY <= Camera::scrollAreaSize )
		this->setMoveSpeedComponent ( AXIS_Z , -1 * Camera::scrollSpeed );

	else if ( mousePosY >= windowSizeY - omoba::Camera::scrollAreaSize )
		this->setMoveSpeedComponent ( AXIS_Z , Camera::scrollSpeed );

	else
		this->setMoveSpeedComponent ( AXIS_Z , 0 );

}

void							Camera::mousePressHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right press
	if ( mouseEvent.state.buttonDown ( Camera::cameraCaptureButton ) )
		this->cameraCaptured = true;

}

void							Camera::mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right release
	if ( ! mouseEvent.state.buttonDown ( Camera::cameraCaptureButton ) )
		this->cameraCaptured = false;

}