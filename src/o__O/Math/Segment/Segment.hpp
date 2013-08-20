#pragma once

#include <vector>
#include "../Point/Point.hpp"



namespace o__O
{

	namespace Math
	{
	
		class SegmentBase
		{
		
			protected:
			
				static void									validatePointId ( const unsigned int verticeId );
		
		};
		
		template <typename Coordinate,int dimension>
		class Segment
			:
				public SegmentBase
		{

			public:

				typedef Point<Coordinate,dimension>			SegmentPoint;
				
				typedef Point<float,dimension>				SegmentPointF;
				
				typedef std::vector<SegmentPointF>			SegmentPointsF;

															Segment  ( const SegmentPoint& pointA , const SegmentPoint& pointB )
				{

					this->points[0] = pointA;
					this->points[1] = pointB;

				}
				
				SegmentPoint&								operator[] ( const int pointId )
				{

					SegmentBase::validatePointId(pointId);

					return this->points[pointId];

				}
				
				const SegmentPoint&							operator[] ( const int pointId ) const
				{

					SegmentBase::validatePointId(pointId);

					return this->points[pointId];

				}
				
				float										getLength ( void ) const
				{
				
					SegmentPoint pointA = this->points[0];
					SegmentPoint pointB = this->points[1];

					return pointA.getDistanceTo(pointB);

				}
				
				SegmentPointF								getInteriorPoint ( const float distanceFromPoint , const int pointId = 0 ) const
				{
				
					//	Validate segment point ID
					SegmentBase::validatePointId(pointId);
				
					//	Validate distance from segment point
					if ( this->getLength() < distanceFromPoint )
					{
					
						throw ExcNotAnInteriorPoint();
						
					}

					Segment	segmentCopy = *this;

					//	The division ratio
					double divisionRatio;

					if ( pointId == 0 )
					{
					
						divisionRatio = distanceFromPoint / ( segmentCopy.getLength() - distanceFromPoint );
						
					}
					else
					{
					
						divisionRatio = ( segmentCopy.getLength() - distanceFromPoint ) / distanceFromPoint;
					
					}
					
					SegmentPointF pointInterior;
					
					//	Calculate interior point coordinates 1 by 1
					for ( int key = 0 ; key < dimension ; key ++ )
					{
					
						pointInterior[key] = ( segmentCopy[0][key] + divisionRatio * segmentCopy[1][key] ) / ( 1 + divisionRatio );
					
					}
					
					return pointInterior;
				
				}
				
				SegmentPointsF								getInteriorPoints ( const int numberOfSubsegments ) const
				{
				
					if ( numberOfSubsegments < 1 )
					{
					
						throw ExcInvalidSubsegmentsNumber();
						
					}
					
					float subsegmentLength = this->getLength() / numberOfSubsegments;
					
					SegmentPointsF points;
					points.push_back(this->points[0]);

					for ( int key = 1 ; key < numberOfSubsegments ; key++ )
					{
					
						int distanceFromSegmentVertice = subsegmentLength * key;
						points.push_back(this->getInteriorPoint(distanceFromSegmentVertice));
					
					}
					
					points.push_back(this->points[1]);
					
					return points;
					
				}
				
				void										swapPoints ( void )
				{

					SegmentPoint pointTemp = this->points[0];

					this->points[0] = this->points[1];
					this->points[1] = pointTemp;

				}
				
			protected:
			
				SegmentPoint								points[2];
				
		};

		//	A segment which ends are two-dimensional integer points
		typedef Segment<int,2> SegmentI2;

		//	A segment which ends are three-dimensional integer points
		typedef Segment<int,3> SegmentI3;
		
		//	A segment which ends are two-dimensional float points
		typedef Segment<float,2> SegmentF2;
		
		//	A segment which ends are three-dimensional float points
		typedef Segment<float,3> SegmentF3;
		
	}
	
}