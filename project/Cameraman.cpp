#include "Cameraman.h"

using namespace omoba;



const Ogre::Real				Cameraman::scrollSpeed = 200;
const int						Cameraman::scrollAreaSize = 10;
const OIS::MouseButtonID		Cameraman::cameraCaptureButton = OIS::MouseButtonID::MB_Middle;



								Cameraman::Cameraman ( Ogre::SceneManager& sceneManager , Ogre::String& cameraName )
									:
										SceneNodeController ( sceneManager , cameraName ),
										cameraCaptured ( false ),
										camera ( 0 )
{

	this->setNodeViewDirection ( Ogre::Vector3::NEGATIVE_UNIT_Z );
	this->setNodeHoldViewDirection ( false );
	this->setNodeMovementMode ( MOVEMENT_MODE_BY_VECTOR );
	this->getNodeMoving ( true );
	
	this->camera = sceneManager.createCamera ( cameraName );
	this->node->attachObject ( this->camera );

}

								Cameraman::~Cameraman ( void )
{

}

Ogre::Camera&					Cameraman::getCamera ( void ) const
{

	return *this->camera;

}

void							Cameraman::mouseMoveHandler ( const OIS::MouseEvent& mouseEvent )
{

	//  Captured camera mode
	if ( this->cameraCaptured )
	{

		int mouseDeltaX = mouseEvent.state.X.rel;
		int mouseDeltaY = mouseEvent.state.Y.rel;

		this->moveNodeBy ( Ogre::Vector3 ( mouseDeltaX , 0 , mouseDeltaY ) );

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
	if ( mousePosX <= Cameraman::scrollAreaSize )
		this->setNodeMovementVectorComponent ( AXIS_X , -1 * Cameraman::scrollSpeed );

	else if ( mousePosX >= windowSizeX - Cameraman::scrollAreaSize )
		this->setNodeMovementVectorComponent ( AXIS_X , Cameraman::scrollSpeed );

	else
		this->setNodeMovementVectorComponent ( AXIS_X , 0 );

	//	Y - axis
	if ( mousePosY <= Cameraman::scrollAreaSize )
		this->setNodeMovementVectorComponent ( AXIS_Z , -1 * Cameraman::scrollSpeed );

	else if ( mousePosY >= windowSizeY - Cameraman::scrollAreaSize )
		this->setNodeMovementVectorComponent ( AXIS_Z , Cameraman::scrollSpeed );

	else
		this->setNodeMovementVectorComponent ( AXIS_Z , 0 );

}

void							Cameraman::mousePressHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right press
	if ( mouseEvent.state.buttonDown ( Cameraman::cameraCaptureButton ) )
		this->cameraCaptured = true;

}

void							Cameraman::mouseReleaseHandler ( const OIS::MouseEvent& mouseEvent )
{

	// Listening for OIS::MouseButtonID::MB_Right release
	if ( ! mouseEvent.state.buttonDown ( Cameraman::cameraCaptureButton ) )
		this->cameraCaptured = false;

}