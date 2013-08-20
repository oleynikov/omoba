#pragma once

#include "../Graph/Graph.hpp"



namespace o__O
{

	namespace Math
	{
	
		template <typename GraphVertice>
		class AGraphFactory
		{
		
			public:
				
				typedef Graph<GraphVertice>			GraphCompatible;

				virtual GraphCompatible				makeGraph ( void ) const = 0;

		};
		
	}

}