#include "../../../../../Tester/Tester.hpp"
#include "../../PlaneGraphFactory.hpp"

using namespace o__O;
using namespace o__O::Math;



int main ( void )
{

	Tester::addTest([]()
	{
	
		PlaneGraphFactory graphFactory(1,1,1);
		
		return 1;
		
	});
	
	Tester::addTest([]()
	{
	
		try
		{
			PlaneGraphFactory graphFactory(1,1,2);
		}
		catch ( ExcInvalidStepSize )
		{
			return true;
		}
		
		return false;
		
	});
	
	Tester::addTest([]()
	{
	
		try
		{
			PlaneGraphFactory graphFactory(10,10,2);
		}
		catch ( ExcInvalidStepSize )
		{
			return false;
		}
		
		return true;
		
	});
	
	Tester::addTest([]()
	{
	
		try
		{
			PlaneGraphFactory graphFactory(0,0,2);
		}
		catch ( ExcInvalidRectangle )
		{
			return true;
		}
		
		return false;
		
	});

	Tester::addTest([]()
	{
	
		PlaneGraphFactory graphFactory(1,1,1);
		PlaneGraph graph = graphFactory.makeGraph();
		
		return
		(
			graph.getVerticesNumber() == 4
				&&
			graph.getEdgesNumber() == 4
				&&
			graph.hasVertice(PointI2{0,0})
				&&
			graph.hasVertice(PointI2{1,0})
				&&
			graph.hasVertice(PointI2{0,1})
				&&
			graph.hasVertice(PointI2{1,1})
				&&
			graph.areAdjacent({0,0},{0,1})
				&&
			graph.areAdjacent({0,0},{1,0})
				&&
			graph.areAdjacent({1,0},{1,1})
				&&
			graph.areAdjacent({0,1},{1,1})
		);
		
	});
	
	Tester::addTest([]()
	{
	
		PlaneGraphFactory graphFactory(3,0,1);
		PlaneGraph graph = graphFactory.makeGraph();
		
		return
		(
			graph.getVerticesNumber() == 4
				&&
			graph.getEdgesNumber() == 3
				&&
			graph.hasVertice(PointI2{0,0})
				&&
			graph.hasVertice(PointI2{1,0})
				&&
			graph.hasVertice(PointI2{2,0})
				&&
			graph.hasVertice(PointI2{3,0})
				&&
			graph.areAdjacent({0,0},{1,0})
				&&
			graph.areAdjacent({1,0},{2,0})
				&&
			graph.areAdjacent({2,0},{3,0})
		);
		
	});
	
	Tester::addTest([]()
	{
	
		PlaneGraphFactory graphFactory(2,2,1);
		PlaneGraph graph = graphFactory.makeGraph();
		
		return
		(
			graph.getVerticesNumber() == 9
				&&
			graph.getEdgesNumber() == 12
				&&
			graph.areAdjacent({0,0},{1,0})
				&&
			graph.areAdjacent({1,0},{2,0})
				&&
			graph.areAdjacent({0,0},{0,1})
				&&
			graph.areAdjacent({1,0},{1,1})
				&&
			graph.areAdjacent({2,0},{2,1})
				&&
			graph.areAdjacent({0,1},{1,1})
				&&
			graph.areAdjacent({1,1},{2,1})
				&&
			graph.areAdjacent({0,1},{0,2})
				&&
			graph.areAdjacent({1,1},{1,2})
				&&
			graph.areAdjacent({2,1},{2,2})
				&&
			graph.areAdjacent({0,2},{1,2})
				&&
			graph.areAdjacent({1,2},{2,2})
		);
		
	});
	
	
	
	return 	Tester::runAllTests() ? 0 : 1;

}