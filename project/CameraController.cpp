#include "CameraController.h"

using namespace omoba;



const Ogre::Real				CameraController::scrollSpeed = 200;
const int						CameraController::scrollAreaSize = 10;
const OIS::MouseButtonID		CameraController::cameraCaptureButton = OIS::MouseButtonID::MB_Middle;



								CameraController::CameraController ( Ogre::SceneManager* sceneManager )
									:
										SceneNodeController ( sceneManager ),
										cameraCaptured ( false ),
										camera ( 0 )
{

	this->holdViewDirection = false;
	this->viewDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;

	this->camera = sceneManager->createCamera ( "camera" );
	this->node->attachObject ( this->camera );

	this->switchMoveMode ( MOVE_MODE_BY_VECTOR );
	this->setMoving ( true );

}

								CameraController::~CameraController ( void )
{

}

Ogre::Camera*					CameraController::getCamera ( void ) const
{

	return this->camera;

}

void							CameraController::mouseMoveHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
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
		this->setMoveVectorComponent ( AXIS_X , -1 * CameraController::scrollSpeed );

	else if ( mousePosX >= windowSizeX - CameraController::scrollAreaSize )
		this->setMoveVectorComponent ( AXIS_X , CameraController::scrollSpeed );

	else
		this->setMoveVectorComponent ( AXIS_X , 0 );

	//	Y - axis
	if ( mousePosY <= CameraController::scrollAreaSize )
		this->setMoveVectorComponent ( AXIS_Z , -1 * CameraController::scrollSpeed );

	else if ( mousePosY >= windowSizeY - CameraController::scrollAreaSize )
		this->setMoveVectorComponent ( AXIS_Z , CameraController::scrollSpeed );

	else
		this->setMoveVectorComponent ( AXIS_Z , 0 );

}

void							CameraController::mousePressHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{

	// Listening for OIS::MouseButtonID::MB_Right press
	if ( mouseEvent.state.buttonDown ( CameraController::cameraCaptureButton ) )
		this->cameraCaptured = true;

}

void							CameraController::mouseReleaseHandler ( const MouseEvent& mouseEvent , const RayQueryResult& rayQueryResult )
{

	// Listening for OIS::MouseButtonID::MB_Right release
	if ( ! mouseEvent.state.buttonDown ( CameraController::cameraCaptureButton ) )
		this->cameraCaptured = false;

}