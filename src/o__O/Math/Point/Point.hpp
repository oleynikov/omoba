#pragma once

#include <initializer_list>
#include <array>
#include <math.h>
#include "../Exception/Exception.hpp"



namespace o__O
{

	namespace Math
	{

		template <typename Coordinate , int dimension>
		class Point
		{
		
			public:
				
				typedef std::array<Coordinate,dimension>					Coordinates;
				
				typedef std::initializer_list<Coordinate>					CoordinatesInitializerList;
				
				typedef typename CoordinatesInitializerList::iterator		CoordinatesInitializerListItr;
				
		
												Point ( void )
				{
				
					//	Check if the dimension of the point is legal
					this->validateDimension();

					//	 Set coordinates values to zero
					this->setCoordinatesValues(0);

				}

												Point ( const CoordinatesInitializerList& coordinates )
				{
				
					this->validateDimensionMatch(coordinates);
					
					this->setCoordinatesValues(coordinates);
				
				}
				
												template <typename _Coordinate>
												Point ( const Point<_Coordinate,dimension>& point )
				{
				
					this->setCoordinatesValues(point.getCoordinatesRef());

				}
				
												template <typename _Coordinate>
				Point&							operator= ( const Point<_Coordinate,dimension>& point )
				{
				
					this->setCoordinatesValues(point.getCoordinatesRef());
				
					return *this;

				}

				Coordinate&						operator[] ( const int coordinateId )
				{
				
					this->validateCoordinateId(coordinateId);

					return this->coordinates[coordinateId];

				}
				
				const Coordinate&				operator[] ( const int coordinateId ) const
				{
				
					this->validateCoordinateId(coordinateId);

					return this->coordinates[coordinateId];

				}

												template <typename _Coordinate>
				bool							operator== ( const Point<_Coordinate,dimension>& point ) const
				{

					for ( int key = 0 ; key < dimension ; key++ )
					{
					
						if ( this->coordinates[key] != point[key] )
						{
						
							return false;
							
						}
						
					}
					
					return true;
					
				}

												template <typename _Coordinate>
				bool							operator!= ( const Point<_Coordinate,dimension>& point ) const
				{

					return ! ( *this == point );

				}

												template <typename _Coordinate>
				Point							operator+ ( const Point<_Coordinate,dimension>& point ) const
				{
				
					Point pointResult = *this;

					for ( int key = 0 ; key < dimension ; key++ )
					{
					
						pointResult[key] += point[key];
						
					}

					return pointResult;

				}

												template <typename _Coordinate>
				Point							operator- ( const Point<_Coordinate,dimension>& point ) const
				{
				
					return (*this)+(point*(-1));

				}

				Point							operator* ( const float multiplier ) const
				{

					Point pointResult = *this;

					for ( int key = 0 ; key < dimension ; key++ )
					{
					
						pointResult[key] *= multiplier;
						
					}

					return pointResult;

				}

				Point							operator/ ( const float multiplier ) const
				{
				
					return (*this)*(1/multiplier);
				
				}
				
				int								getDimension ( void ) const
				{

					return dimension;

				}

				Coordinate						getCoordinateValue ( const int coordinateId )
				{
				
					this->validateCoordinateId(coordinateId);
					
					return this->coordinates[coordinateId];
				
				}
				
				Coordinates&					getCoordinatesRef ( void )
				{
				
					return this->coordinates;
				
				}
				
				const Coordinates&				getCoordinatesRef ( void ) const
				{
				
					return this->coordinates;
				
				}
				
												template <typename _Coordinate>
				float							getDistanceTo ( const Point<_Coordinate,dimension>& point ) const
				{

					float distanceSquared = 0;

					for ( int key = 0 ; key != dimension ; key++ )
					{

						float coordinateA = this->coordinates[key];
						float coordinateB = point.coordinates[key];
			
						distanceSquared += ( coordinateB - coordinateA ) * ( coordinateB - coordinateA );

					}
		
					float distance = sqrt(distanceSquared);

					return distance;

				}

												template <typename _Coordinate>
				void							setCoordinatesValues ( const _Coordinate& coordinatesValue )
				{
				
					/*
					
						Set all coordinates values to `coordinatesValue`
						
					*/
				
					this->coordinates.fill(coordinatesValue);
					
				}

				void							setCoordinatesValues ( const CoordinatesInitializerList& coordinates )
				{
				
					CoordinatesInitializerListItr coordinatesItr = coordinates.begin();
					int coordinateId = 0;
					
					for ( ; coordinatesItr != coordinates.end() ; coordinatesItr++ , coordinateId++ )
					{
					
						this->coordinates[coordinateId] = *coordinatesItr;
					
					}

				}

												template <typename _Coordinate>
				void							setCoordinatesValues ( const std::array<_Coordinate,dimension>& coordinates )
				{
				
					for ( int key = 0 ; key < dimension ; key++ )
					{
					
						this->coordinates[key] = coordinates[key];
						
					}
				
				}

				void							validateDimensionMatch ( const CoordinatesInitializerList& coordinates ) const
				{
				
					if ( coordinates.size() != dimension )
					{
					
						throw ExcDimensionMismatch();
						
					}
				
				}
				
												template <typename _Coordinate , int _dimension>
				void							validateDimensionMatch ( const Point<_Coordinate,_dimension>& point ) const
				{

					if ( dimension != _dimension )
					{

						throw ExcDimensionMismatch();

					}

				}
				
				void							validateCoordinateId ( const int coordinateId ) const
				{
				
					if ( coordinateId >= 0 && dimension <= coordinateId )
					{
					
						throw ExcDimensionMismatch();
						
					}
					
				}

				void							validateDimension ( void ) const
				{
				
					/*
					
						Throws an `ExcIllegalDimension` Exceptioneption if the dimension of the point is illegal
						
					*/
				
					if ( dimension <= 0 )
					{
					
						throw ExcInvalidDimension();
						
					}
				
				}

			protected:

				Coordinates						coordinates;

		};

		typedef Point<int,2> PointI2;

		typedef Point<int,3> PointI3;

		typedef Point<float,2> PointF2;

		typedef Point<float,3> PointF3;

	}

}