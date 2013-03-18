#include "_Game.h"

using namespace omoba;

				Game::Game(void)
					:
						oPluginsCfg(Ogre::StringUtil::BLANK),
						oResourcesCfg(Ogre::StringUtil::BLANK),
						oRoot(0),
						oRenderWindow(0),
						oSceneManager(0),
						inputDispatcher(0),
						camera(0),
						cameraController(0),
						playerController(0),
						cursor(0)
{
}
				Game::~Game(void)
{

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener ( this->oRenderWindow , this );

	this->windowClosed(this->oRenderWindow);

	delete this->oRoot;

}
void			Game::initiate(void)
{

	this->setCfgFiles();
	this->createRoot();
	this->defineResources();
	this->createRenderWindow();
	this->initializeResources();
	this->createSceneManager();
	this->createInputDispatcher();
	this->createCamera();
	this->createViewport();
	this->createScene();
	this->createCursor();
	this->startRendering();

}
void			Game::setCfgFiles(void)
{

	#ifdef _DEBUG
		this->oPluginsCfg = "plugins_d.cfg";
		this->oResourcesCfg = "resources_d.cfg";
	#else
		this->oPluginsCfg = "plugins.cfg";
		this->oResourcesCfg = "resources.cfg";
	#endif

}
void			Game::createRoot(void)
{
 
    this->oRoot = new Ogre::Root(this->oPluginsCfg);

}
void			Game::defineResources(void)
{

	// Load resource paths from config file
	Ogre::ConfigFile resourcesCfg;
	resourcesCfg.load(this->oResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = resourcesCfg.getSectionIterator();
	 
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
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
			this->oRoot->restoreConfig()
				||
			this->oRoot->showConfigDialog()
		)
	)
	throw "Exit from config dialog";

	this->oRenderWindow = this->oRoot->initialise ( true , "omoba early alpha" );

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener ( this->oRenderWindow , this );

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
	this->oSceneManager = this->oRoot->createSceneManager ( "DefaultSceneManager" );

}
void			Game::createInputDispatcher(void)
{

	this->inputDispatcher = new InputDispatcher(*this->oRenderWindow);

	this->oRoot->addFrameListener ( this->inputDispatcher );

	//Set initial mouse clipping size
	this->windowResized ( this->oRenderWindow );

}
void			Game::createCamera(void)
{

	//	Creating camera and  camera node
	this->camera = this->oSceneManager->createCamera ( "CameraMain" );
	Ogre::SceneNode* cameraNode = this->oSceneManager->getRootSceneNode()->createChildSceneNode( "CameraSceneNode" );
	cameraNode->attachObject(this->camera);

	//	Creating camera controller
	this->cameraController = new CameraController();
	this->cameraController->setNode(cameraNode);
	this->cameraController->moveBy(Ogre::Vector3(0,500,500));
	this->cameraController->lookAt(Ogre::Vector3::ZERO);
	
	//	Registering camera controller to recieve input events
	this->inputDispatcher->registerListener(INPUT_EVENT_MOUSE_MOVED,this->cameraController);
	this->inputDispatcher->registerListener(INPUT_EVENT_MOUSE_PRESSED,this->cameraController);
	this->inputDispatcher->registerListener(INPUT_EVENT_MOUSE_RELEASED,this->cameraController);

	//	Registering camera controller to recieve frame events
	this->oRoot->addFrameListener ( this->cameraController );

}
void			Game::createViewport(void)
{

	// Create one viewport, entire window
	Ogre::Viewport* viewport = this->oRenderWindow->addViewport(this->camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	 
	// Alter the camera aspect ratio to match the viewport
	Ogre::Real cameraAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
	this->camera->setAspectRatio(cameraAspectRatio);

}
void			Game::createScene(void)
{

	Ogre::Entity* ogreHead = this->oSceneManager->createEntity ( "Head" , "robot.mesh" );
	Ogre::SceneNode* headNode = this->oSceneManager->getRootSceneNode()->createChildSceneNode();
	headNode->setScale(Ogre::Vector3(2,2,2));
	headNode->attachObject(ogreHead);

	this->playerController = new PlayerController(this->oSceneManager,this->camera);
	this->playerController->setNode(headNode);

	this->inputDispatcher->registerListener(INPUT_EVENT_MOUSE_PRESSED,this->playerController);
	this->inputDispatcher->registerListener(INPUT_EVENT_MOUSE_RELEASED,this->playerController);
	this->oRoot->addFrameListener(this->playerController);

	//	Set ambient light
	this->oSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	 
	//	Create a light
	Ogre::Light* l = this->oSceneManager->createLight("MainLight");
	l->setPosition(20,80,50);

	//	Create plain
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane
	(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5,
		Ogre::Vector3::UNIT_Z
	);
	Ogre::Entity* entGround = this->oSceneManager->createEntity("Ground", "ground");
	this->oSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);

}
void			Game::createCursor(void)
{

	this->cursor = new Cursor();
	this->inputDispatcher->registerListener(INPUT_EVENT_MOUSE_MOVED,this->cursor);

}
void			Game::startRendering(void)
{

	this->inputDispatcher->initiate();
	this->oRoot->startRendering();

}
void			Game::windowResized(Ogre::RenderWindow* renderWindow)
{

	this->inputDispatcher->updateRenderWindow(renderWindow);

}
void			Game::windowClosed(Ogre::RenderWindow* renderWindow)
{

	//Unattach OIS before window shutdown (very important under Linux)
	//Only close for window that created OIS
	if ( renderWindow == this->oRenderWindow )
    {
		if ( this->inputDispatcher )
		{

			this->oRoot->removeFrameListener(this->inputDispatcher);
			delete this->inputDispatcher;
			this->inputDispatcher = 0;

		}

    }

	this->oRoot->queueEndRendering();

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
        }
		catch( Ogre::Exception& e )
		{
			#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
			#else
	            std::cerr << "An exception has occured: " <<
		            e.getFullDescription().c_str() << std::endl;
			#endif
        }
		catch(...)
		{

		}
 
        return 0;

    }
 
#ifdef __cplusplus
}
#endif