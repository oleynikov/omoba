#pragma once;

#include <string>
#include <OgreVector3.h>
#include <o__O/String/String.hpp>
#include <o__O/Geometry/Point/Point.hpp>



namespace OgreAdaptor
{


	class Vector3Exception
	{

		public:

			class				ExcStringToVectorConvertionError { };

	};



	class Vector3
		:
			public Ogre::Vector3
	{

		public:

								Vector3 ( const Ogre::Vector3& vector );
		
								Vector3 ( const std::string coordinates , const char delimiter = ';' );

								Vector3 ( const o__O::PointF3 point );

								Vector3 ( const o__O::PointI3 point );

			o__O::PointF3		toPointF3 ( void );

			o__O::PointI3		toPointI3 ( void );

	};



};