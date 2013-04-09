#pragma once;

#include <OgreVector3.h>
#include "../../o__O/String/String.h"



namespace OgreExtensions
{

	class Vector3
		:
			public Ogre::Vector3
	{

		public:
		
			Vector3 ( const std::string coordinates , const char delimiter = ';' );
			
	};
	
};