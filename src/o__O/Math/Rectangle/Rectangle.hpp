#pragma once

#include <cmath>
#include <vector>
#include <stdlib.h>
#include "../Point/Point.hpp"



namespace o__O
{

	namespace Math
	{
	
		template <typename Coordinate , int dimension>
		class Rectangle
		{

			typedef Point<Coordinate,dimension>			PointCompatible;

			public:

														Rectangle ( const PointCompatible& pointTL , const PointCompatible& pointBR )
				{

					this->width = 0;
					this->height = 0;

					float rectangleWidth = abs ( pointTL[0] - pointBR[0] );

					PointCompatible pointTR { pointTL[0] + rectangleWidth , pointTL[1] };
					PointCompatible pointBL { pointBR[0] - rectangleWidth , pointBR[1] };

					vertices[0] = pointTL;
					vertices[1] = pointTR;
					vertices[2] = pointBR;
					vertices[3] = pointBL;

				}

														Rectangle ( const PointCompatible& pointTL , const PointCompatible& pointTR , const PointCompatible& pointBR , const PointCompatible& pointBL )
				{

					this->width = 0;
					this->height = 0;

					vertices[0] = pointTL;
					vertices[1] = pointTR;
					vertices[2] = pointBR;
					vertices[3] = pointBL;

				}

				PointCompatible&						operator[] ( const int verticeId )
				{

					return this->vertices[verticeId];

				}

				const PointCompatible&					operator[] ( const int verticeId ) const
				{

					return this->vertices[verticeId];

				}

				float									getWidth ( void ) const
				{

					if ( this->width == 0 )
					{

						this->calculateWidth();

					}

					return this->width;

				}

				float									getHeight ( void ) const
				{

					if ( this->height == 0 )
					{

						this->calculateHeight();

					}

					return this->height;

				}

				float									getArea ( void ) const
				{

					return ( this->getWidth() + this->getHeight() ) * 2;

				}

				bool									getAxisAligned ( void ) const
				{

					return
					(
						this->vertices[0][1] == this->vertices[1][1]
							||
						this->vertices[0][0] == this->vertices[3][0]
					);

				}

				bool									checkInnerPoint ( const PointCompatible& point ) const
				{


					return 1;


				}

			private:

				void									calculateWidth ( void ) const
				{

					PointCompatible pointTL = this->vertices[0];
					PointCompatible pointTR = this->vertices[1];

					this->width = pointTL.getDistanceTo(pointTR);

				}

				void									calculateHeight ( void ) const
				{

					PointCompatible pointTL = this->vertices[0];
					PointCompatible pointBL = this->vertices[3];

					this->height = pointTL.getDistanceTo(pointBL);

				}

				PointCompatible							vertices[4];

				float									width;

				float									height;
				
		};

		typedef Rectangle<int,2>						RectangleI2;

		typedef Rectangle<float,2>						RectangleF2;

	}
	
}