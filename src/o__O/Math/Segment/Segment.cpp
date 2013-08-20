#include "Segment.hpp"

using namespace o__O::Math;



//	SegmentBase

void						SegmentBase::validatePointId ( const unsigned int verticeId )
{

	if
	(
		verticeId < 0
			||
		verticeId > 1
	)
	{
	
		throw ExcInvalidVerticeId();
	
	}

}