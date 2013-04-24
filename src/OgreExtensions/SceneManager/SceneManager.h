#pragma once

#include <OgreSceneManager.h>
#include <OgreException.h>
#include "../../o__O/Data/NameIncrementor.h"



namespace OgreExtensions
{

	class SceneManager
	{

		public:

			static bool				getEntityNameAvailable ( const Ogre::SceneManager& sceneManager , const std::string entityName );

			static std::string		getAvailableEntityName ( const Ogre::SceneManager& sceneManager , const std::string entityName );

	};


}