#include "Game.h"

using namespace omoba;

				Game::Game(void)
					:
						oPluginsCfg(Ogre::StringUtil::BLANK),
						oResourcesCfg(Ogre::StringUtil::BLANK),
						oRoot(0),
						oRenderWindow(0),
						oSceneManager(0),
						oCamera(0),
						inputDispatcher(0)
{
}
				Game::~Game(void)
{

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener ( this->oRenderWindow , this );

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
	this->createCamera();
	this->createViewport();
	this->createScene();
	//this->createInputDispatcher();
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

	{
		//exp delete cfg
		throw "Exit the program";
	}

	/*
		// Manual setup
		// Do not add this to the application
		RenderSystem *rs = mRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
		// or use "OpenGL Rendering Subsystem"
		mRoot->setRenderSystem(rs);
		rs->setConfigOption("Full Screen", "No");
		rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

	*/

	this->oRenderWindow = this->oRoot->initialise ( true , "omoba early alpha");

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
void			Game::createCamera(void)
{

	// Create the camera
	this->oCamera = this->oSceneManager->createCamera ( "PlayerCamera" );

	// Position it at 80 in Z direction
	this->oCamera->setPosition(Ogre::Vector3(0,300,300));

	// Look back along -Z
	this->oCamera->lookAt(Ogre::Vector3(0,0,0));
	this->oCamera->setNearClipDistance(5);

}
void			Game::createViewport(void)
{

	// Create one viewport, entire window
	Ogre::Viewport* viewport = this->oRenderWindow->addViewport(this->oCamera);
	viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	 
	// Alter the camera aspect ratio to match the viewport
	Ogre::Real cameraAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
	this->oCamera->setAspectRatio(cameraAspectRatio);

}
void			Game::createScene(void)
{

	Ogre::Entity* ogreHead = this->oSceneManager->createEntity ( "Head" , "ogrehead.mesh" );

	Ogre::SceneNode* headNode = this->oSceneManager->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);
	 
	// Set ambient light
	this->oSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	 
	// Create a light
	Ogre::Light* l = this->oSceneManager->createLight("MainLight");
	l->setPosition(20,80,50);

}
void			Game::createInputDispatcher(void)
{

	this->inputDispatcher = new InputDispatcher(*this->oRenderWindow);
	this->oRoot->addFrameListener ( this->inputDispatcher );

	//Set initial mouse clipping size
	this->windowResized ( this->oRenderWindow );

}
void			Game::startRendering(void)
{

	this->oRoot->startRendering();

}
void			Game::windowResized(Ogre::RenderWindow* renderWindow)
{

	//this->inputDispatcher->updateRenderWindow(renderWindow);

}
void			Game::windowClosed(Ogre::RenderWindow* renderWindow)
{
	
	//Unattach OIS before window shutdown (very important under Linux)
	//Only close for window that created OIS
	if ( renderWindow == this->oRenderWindow )
    {

		if ( this->inputDispatcher )
			delete this->inputDispatcher;

		this->oRoot->queueEndRendering();

    }

}
//------------------------------------------------------------------------------------------------------





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
 
        return 0;

    }
 
#ifdef __cplusplus
}
#endif