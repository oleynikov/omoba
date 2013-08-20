#pragma once

#include <vector>
#include <algorithm>
#include "../../Exception/Exception.hpp"
#include "../../Point/Point.hpp"
#include "AGraphFactory.hpp"



namespace o__O
{

	namespace Math
	{
	
		typedef	PointI2								PlanePoint;
		
		typedef std::vector<PlanePoint>				PlanePoints;
		
		typedef PlanePoints::iterator				PlanePointsItr;

		typedef Graph<PlanePoint>					PlaneGraph;
		
		class PlaneGraphFactory
			:
				AGraphFactory<PlanePoint>
		{
		
			public:

													PlaneGraphFactory ( const int xMax , const int yMax , int stepSize = 1 );

				virtual PlaneGraph					makeGraph ( void ) const;

			protected:
			
				void								checkRectangle ( void ) const;

				void								checkStepSize ( void ) const;

				PlanePoints							getAllAdjacentPoints ( const PlanePoint& planePoint ) const;
				
				PlanePoints							getAvailableAdjacentPoints ( const PlanePoint& planePoint ) const;
				
				bool								getPointInRectangle ( const PlanePoint& planePoint ) const;

				int									xMax;
				
				int									yMax;

				int									stepSize;

		};
		
	}

}