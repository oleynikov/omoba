#pragma once;

#include <vector>

namespace omoba
{

	template <typename ObjectType>
	class StdVector
	{

		public:

			static bool contains ( std::vector<ObjectType> vector , ObjectType object );
			{

				typename std::vector<ObjectType>::iterator objectItr = vector.begin();

				for ( ; objectItr != vector.end() ; objectItr++ )
				{

					if ( *objectItr == object )
					{

						return true;

					}

				}

				return false;

			}

	};

};