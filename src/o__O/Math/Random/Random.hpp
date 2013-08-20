#pragma once

#include <cstdlib>
#include "../Exception/Exception.hpp"



namespace o__O
{

	namespace Math
	{
	
		class Random
		{
		
			public:
			
				static int			getInt ( const int minimum , const int maximum );
				
				static bool			coinFlip ( float winRatePercent = 50 );
				
		};
	
	}
	
};