#include "Random.hpp"

using namespace o__O::Math;



//	Random

int			Random::getInt ( const int minimum , const int maximum )
{

	//	Validate the range 
	if ( minimum > maximum )
	{
	
		throw ExcInvalidRange();
	
	}
	
	//	Minimum range
	else if ( minimum == maximum )
	{
	
		return minimum;
		
	}
	
	//	Calculate the length of the range
	int rangeLength = maximum - minimum + 1;
	
	//	Return a random number from the range
	return rand() % rangeLength + minimum;

}

bool		Random::coinFlip ( float winRatePercent )
{

	if ( winRatePercent > 100 )
	{
	
		winRatePercent = 100;
	
	}
	
	if ( winRatePercent < 0 )
	{
	
		winRatePercent = 0;
	
	}
	
	int winRateInverted = 100 / winRatePercent;
	
	return Random::getInt(1,winRateInverted) == 1;

}