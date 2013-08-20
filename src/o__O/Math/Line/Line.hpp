#pragma once

#include "../Point/Point.hpp"
#include "../Exception/Exception.hpp"



namespace o__O
{

	namespace Math
	{

		template <typename Coordinate,int dimension>
		class Line
		{
		
			typedef Point<Coordinate,dimension>		LinePoint;
			
			typedef std::array<float,dimension>		EquationCoefficients;

			public:

													Line ( const LinePoint& pointA , const LinePoint& pointB )
				{
				
					if ( pointA == pointB )
					{
					
						throw ExcPointsAreEqual();
						
					}
					
					this->points[0] = pointA;
					this->points[1] = pointB;
					
				}
				
				bool								isInteriorPoint ( const LinePoint& point ) const
				{
				
					float equationValues[dimension];
				
					for ( int key = 0 ; key < dimension ; key ++ )
					{
					
						float x = point[key];
						float x0 = this->points[0][key];
						float x1 = this->points[1][key];
					
						equationValues[key] = ( x - x0 ) / ( x1 - x0 );
						
						if ( key > 0 )
						{
						
							float valueCurrent = equationValues[key];
							float valuePrevious = equationValues[key-1];
							
							if ( valueCurrent != valuePrevious )
							{
							
								return false;
								
							}
							
						}
					
					}
					
					return true;
				
				}
				
				void								checkIsInteriorPoint ( const LinePoint& point ) const
				{
				
					if ( ! isInteriorPoint ( point ) )
					{
					
						throw ExcNotAnInteriorPoint();
						
					}
				
				}
				
			protected:
			
				LinePoint							points[2];
			
		};
		
		typedef Line<int,2> LineI2;
		
		typedef Line<int,3> LineI3;
		
		typedef Line<float,2> LineF2;
		
		typedef Line<float,3> LineF3;
		
	}
	
}