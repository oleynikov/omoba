#include "CameraController.h"

using namespace omoba;

const Ogre::Real				CameraController::scrollSpeed = 200;
const int						CameraController::scrollAreaSize = 10;
const OIS::MouseButtonID		CameraController::cameraCaptureButton = OIS::MouseButtonID::MB_Middle;



								CameraController::CameraController ( void )
									:
										cameraCaptured(false)
{

	this->holdViewDirection = false;

}
                                
								CameraController::~CameraController ( void )
{

}
                                
void							CameraController::mouseMoveHandler ( const OIS::MouseEvent& mouseEvent )
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
	if ( mousePosX <= CameraController::scrollAreaSize )
		this->setMoveSpeed
		(
			Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::NEGATIVE_UNIT_X ),
			CameraController::scrollSpeed
		);

	else if ( mousePosX >= windowSizeX - omoba::CameraController::scrollAreaSize )
		this->setMoveSpeed
		(
			Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::UNIT_X ),
			CameraController::scrollSpeed
		);

	else
		this->stop();

	//	Y - axis
	if ( mousePosY <= CameraController::scrollAreaSize )
		this->setMoveSpeed
		(
			Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::NEGATIVE_UNIT_Z ),
			CameraController::scrollSpeed
		);

	else if ( mousePosY >= windowSizeY - omoba::CameraController::scrollAreaSize )
		this->setMoveSpeed
		(
			Ogre::Ray ( Ogre::Vector3::ZERO , Ogre::Vector3::UNIT_Z ),
			CameraController::scrollSpeed
		);

	else
		this->stop();

}

void							CameraController::mousePressHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right press
	if ( mouseEvent.state.buttonDown ( CameraController::cameraCaptureButton ) )
		this->cameraCaptured = true;

}

void							CameraController::mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right release
	if ( ! mouseEvent.state.buttonDown ( CameraController::cameraCaptureButton ) )
		this->cameraCaptured = false;

}


/*

	Camera control by WASD keys

void							omoba::CameraController::keyPressHandler(const OIS::KeyEvent& keyEvent)
{

	OIS::KeyCode keyCode = keyEvent.key;
	
	switch ( keyCode )
	{

		case OIS::KeyCode::KC_A : this->pushNodeBy( omoba::Axis::AXIS_X , -1 * omoba::CameraController::scrollSpeed ); break;
		case OIS::KeyCode::KC_D : this->pushNodeBy( omoba::Axis::AXIS_X , omoba::CameraController::scrollSpeed ); break;
		case OIS::KeyCode::KC_S : this->pushNodeBy( omoba::Axis::AXIS_Z , omoba::CameraController::scrollSpeed ); break;
		case OIS::KeyCode::KC_W : this->pushNodeBy( omoba::Axis::AXIS_Z , -1 * omoba::CameraController::scrollSpeed ); break;

	}

}

void							omoba::CameraController::keyReleaseHandler(const OIS::KeyEvent& keyEvent)
{

	//	Released key code
	OIS::KeyCode keyCode = keyEvent.key;

	//	[A] or [D] key was released
	if
	(
		keyCode == OIS::KeyCode::KC_A
			||
		keyCode == OIS::KeyCode::KC_D
	)
	{

		//	Stopping camera by X-axis
		this->pushNodeBy( omoba::Axis::AXIS_X , 0 );

	}

	//	[W] or [S] key was released
	else if
	(
		keyCode == OIS::KeyCode::KC_S
			||
		keyCode == OIS::KeyCode::KC_W
	)
	{

		//	Stopping camera by Z-axis
		this->pushNodeBy( omoba::Axis::AXIS_Z , 0 );

	}

}
*/