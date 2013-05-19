#include "SceneManager.h"

using namespace OgreExtension;



bool			SceneManager::getEntityNameAvailable ( const Ogre::SceneManager& sceneManager , const std::string entityName )
{

	try
	{

		//	Try to retrieve the entity by it's name
		Ogre::Entity* entity = sceneManager.getEntity(entityName);

		//	No exception occured
		if ( entity )
			return false;

	}

	catch(Ogre::ItemIdentityException)
	{

		//	No entity with such name

	}

	return true;

}

std::string		SceneManager::getAvailableEntityName ( const Ogre::SceneManager& sceneManager , const std::string entityName )
{

	if ( SceneManager::getEntityNameAvailable(sceneManager,entityName) )
		return entityName;

	//	Name is already in use
	else
	{

		o__O::NameIncrementor nameIncrementor;
		std::string entityNameNew = entityName;

		do
		{

			entityNameNew = nameIncrementor.incrementName(entityNameNew);

		}
		while ( ! SceneManager::getEntityNameAvailable(sceneManager,entityNameNew) );

		return entityNameNew;

	}

}