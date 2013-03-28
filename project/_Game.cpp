#include "_Game.h"

using namespace omoba;

				Game::Game ( void )
					:
						pluginsCfg ( Ogre::StringUtil::BLANK ),
						resourcesCfg ( Ogre::StringUtil::BLANK ),
						root ( 0 ),
						renderWindow ( 0 ),
						sceneManager ( 0 ),
						cameraman ( 0 ),
						inputDispatcher ( 0 ),
						cursor ( 0 ) 
{

}

				Game::~Game(void)
{

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener ( this->renderWindow , this );

	this->windowClosed ( this->renderWindow );

	delete this->root;

}

void			Game::initiate(void)
{

	this->setCfgFiles();
	this->createRoot();
	this->defineResources();
	this->createRenderWindow();
	this->initializeResources();
	this->createSceneManager();
	this->createCamera();
	this->createViewport();
	this->createCursor();
	this->configureCameraRayIntersectionCalculator();
	this->createInputDispatcher();
	this->createScene();
	this->startRendering();

}

void			Game::setCfgFiles(void)
{

	#ifdef _DEBUG
		this->pluginsCfg = "plugins_d.cfg";
		this->resourcesCfg = "resources_d.cfg";
	#else
		this->pluginsCfg = "plugins.cfg";
		this->resourcesCfg = "resources.cfg";
	#endif

}

void			Game::createRoot(void)
{
 
    this->root = new Ogre::Root ( this->pluginsCfg );

}

void			Game::defineResources(void)
{

	// Load resource paths from config file
	Ogre::ConfigFile resourcesCfg;
	resourcesCfg.load ( this->resourcesCfg );

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = resourcesCfg.getSectionIterator();
	 
	Ogre::String secName, typeName, archName;
	while ( seci.hasMoreElements() )
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

}

void			Game::createRenderWindow(void) 
{

	// Show the configuration dialog and initialise the system
	if
	(
		!
		(
			this->root->restoreConfig()
				||
			this->root->showConfigDialog()
		)
	)
	throw "Exit from config dialog";

	this->renderWindow = this->root->initialise ( true , "omoba early alpha" );

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener ( this->renderWindow , this );

}

void			Game::initializeResources(void)
{

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

void			Game::createSceneManager(void)
{

	// Create the SceneManager, in this case a generic one
	this->sceneManager = this->root->createSceneManager ( "DefaultSceneManager" );

}

void			Game::createCamera(void)
{

	//	Creating camera controller
	this->cameraman = new Cameraman ( *this->sceneManager , "OMOBA_CAMERA_MAIN" );
	this->cameraman->setNodePosition ( Ogre::Vector3 ( 0 , 300 , 300 ) );
	this->cameraman->aimNodeAt ( Ogre::Vector3::ZERO );
	
	//	Registering camera controller to recieve frame events
	this->root->addFrameListener ( this->cameraman );

}

void			Game::createViewport(void)
{

	// Create one viewport, entire window
	Ogre::Viewport* viewport = this->renderWindow->addViewport ( &this->cameraman->getCamera() );
	viewport->setBackgroundColour ( Ogre::ColourValue ( 0 , 0 , 0 ) );
	 
	// Alter the camera aspect ratio to match the viewport
	Ogre::Real cameraAspectRatio ( Ogre::Real ( viewport->getActualWidth() ) / Ogre::Real ( viewport->getActualHeight() ) );
	this->cameraman->getCamera().setAspectRatio ( cameraAspectRatio );

}

void			Game::createCursor(void)
{

	this->cursor = new Cursor();

}

void			Game::configureCameraRayIntersectionCalculator ( void )
{

	CameraRayIntersectionCalculator::getSingleton().configure ( this->sceneManager , &this->cameraman->getCamera() );

}

void			Game::createInputDispatcher(void)
{

	this->inputDispatcher = new InputDispatcher ( *this->renderWindow );
	this->root->addFrameListener ( this->inputDispatcher );

	//Set initial mouse clipping size
	this->windowResized ( this->renderWindow );

	//	Registering camera controller to recieve input events
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_MOVED , *this->cameraman );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_PRESSED , *this->cameraman );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_RELEASED , *this->cameraman );
	
	//	Registering camera controller to recieve input events
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_MOVED , *this->cursor );
	
}

void			Game::createScene(void)
{

	//	Set ambient light
	this->sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//	Create plain
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane
	(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5,
		Ogre::Vector3::UNIT_Z
	);

	Sprite* ground = new Sprite ( *this->sceneManager , "ground" );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_PRESSED , *ground );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_RELEASED , *ground );

	// Create player
	Sprite* robot = new Sprite ( *this->sceneManager , "robot.mesh" );
	robot->setNodeViewDirection ( Ogre::Vector3::UNIT_X );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_PRESSED , *robot );
	this->inputDispatcher->registerListener ( INPUT_EVENT_MOUSE_RELEASED , *robot );
	ground->signalMousePressed.connect ( boost::bind ( &Sprite::setMovementPath , robot , _1 ) );
	
}

void			Game::startRendering(void)
{

	this->inputDispatcher->initiate();
	this->root->startRendering();

}

void			Game::windowResized(Ogre::RenderWindow* renderWindow)
{

	this->inputDispatcher->updateRenderWindow ( *renderWindow );

}

void			Game::windowClosed(Ogre::RenderWindow* renderWindow)
{

	//Unattach OIS before window shutdown (very important under Linux)
	//Only close for window that created OIS
	if ( renderWindow == this->renderWindow )
    {
		if ( this->inputDispatcher )
		{

			this->root->removeFrameListener(this->inputDispatcher);
			delete this->inputDispatcher;
			this->inputDispatcher = 0;

		}

    }

	this->root->queueEndRendering();

}

//---------------------------------------------------------------------------------
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Game app;
 
        try 
        {
            app.initiate();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR| MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif