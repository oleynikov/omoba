#include "PlaneGraphFactory.hpp"

using namespace o__O::Math;



//	PlaneGraphFactory

					PlaneGraphFactory::PlaneGraphFactory ( const int xMax , const int yMax , int stepSize )
						:
							xMax		( xMax ),
							yMax		( yMax ),
							stepSize	( stepSize )
{

	this->checkRectangle();
	this->checkStepSize();

}

PlaneGraph			PlaneGraphFactory::makeGraph ( void ) const
{

	PlanePoints		pointsUnprocessed = { PlanePoint{0,0} };
	PlanePoints		pointsProcessed;
	PlanePoints		pointsAdjacent;
	PlanePointsItr	pointsAdjacentItr;
	PlanePoint		pointCurrent;
	PlaneGraph		graph;
	
	while ( ! pointsUnprocessed.empty() )
	{
		
		//	Get one point out of the unprocessed list and add it to the processed list
		pointCurrent = *pointsUnprocessed.rbegin();
		pointsUnprocessed.pop_back();
		pointsProcessed.push_back(pointCurrent);
		
		//	Get it's adjacent points
		pointsAdjacent = this->getAvailableAdjacentPoints(pointCurrent);
		
		//	Add them to graph
		for ( pointsAdjacentItr = pointsAdjacent.begin() ; pointsAdjacentItr != pointsAdjacent.end() ; pointsAdjacentItr++ )
		{

			//	Check if the point was already processed
			if ( std::find(pointsProcessed.begin(),pointsProcessed.end(),*pointsAdjacentItr) != pointsProcessed.end() )
				continue;

			//	Add an edge to the graph
			graph.addEdge(pointCurrent,*pointsAdjacentItr);
				
			//	Check if the point was already added to unprocessed
			if ( std::find(pointsUnprocessed.begin(),pointsUnprocessed.end(),*pointsAdjacentItr) != pointsUnprocessed.end() )
				continue;
			
			pointsUnprocessed.push_back(*pointsAdjacentItr);
		
		}
	
	}

	return graph;
	
}

void				PlaneGraphFactory::checkRectangle ( void ) const
{

	if
	(
		this->xMax == 0
			&&
		this->yMax == 0
	)
	{
	
		throw ExcInvalidRectangle();
	
	}

}

void				PlaneGraphFactory::checkStepSize ( void ) const
{

	if
	(
		fmod ( this->xMax , this->stepSize ) != 0
			||
		fmod ( this->yMax , this->stepSize ) != 0
	)
	{

		throw ExcInvalidStepSize();

	}

}

PlanePoints			PlaneGraphFactory::getAllAdjacentPoints ( const PlanePoint& planePoint ) const
{

	auto pointT	= PlanePoint { planePoint[0] , planePoint[1] + this->stepSize };
	auto pointB	= PlanePoint { planePoint[0] , planePoint[1] - this->stepSize };
	auto pointL	= PlanePoint { planePoint[0] - this->stepSize , planePoint[1] };
	auto pointR	= PlanePoint { planePoint[0] + this->stepSize , planePoint[1] };
	
	return { pointT , pointB , pointL , pointR };

}

PlanePoints			PlaneGraphFactory::getAvailableAdjacentPoints ( const PlanePoint& planePoint ) const
{

	PlanePoints availableAdjacentPoints = this->getAllAdjacentPoints(planePoint);
	
	for ( auto availableAdjacentPointsItr = availableAdjacentPoints.begin() ; availableAdjacentPointsItr != availableAdjacentPoints.end() ; availableAdjacentPointsItr++ )
	{
	
		if ( ! this->getPointInRectangle(*availableAdjacentPointsItr) )
		{
		
			availableAdjacentPoints.erase(availableAdjacentPointsItr);
			availableAdjacentPointsItr--;
		
		}
	
	}
	
	return availableAdjacentPoints;

}

bool				PlaneGraphFactory::getPointInRectangle ( const PlanePoint& planePoint ) const
{
	
	return
	(
		planePoint[0] >= 0
			&&
		planePoint[0] <= this->xMax
			&&
		planePoint[1] >= 0
			&&
		planePoint[1] <= this->yMax
	);

}