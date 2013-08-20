#include "../../../../../Tester/Tester.hpp"
#include "../../../../Point/Point.hpp"
#include "../../GraphEdge.hpp"

using namespace o__O;
using namespace o__O::Math;



int main ( void )
{

	Tester::addTest([]()
	{
	
		PointI3 verticeA = {3,3,3};
		PointI3 verticeB = {5,5,5};
		GraphEdge<PointI3> edge(verticeA,verticeB);
		
		return
		(
			edge[0] == verticeA
				&&
			edge[1] == verticeB
		);
		
	});
	
	Tester::addTest([]()
	{
	
		auto verticeA = new PointI3 {3,3,3};
		auto verticeB = new PointI3 {5,5,5};
		GraphEdge<PointI3*> edge(verticeA,verticeB);
		
		return
		(
			*(edge[0]) == PointI3 {3,3,3}
				&&
			*(edge[1]) == PointI3 {5,5,5}
		);
		
	});

	Tester::addTest([]()
	{
	
		PointI3 verticeA = {0,0,0};
		PointI3 verticeB = {5,5,5};
		GraphEdge<PointI3> edge(verticeA,verticeB);
		
		try
		{
			edge[2];
		}
		catch ( o__O::Math::ExcInvalidVerticeId )
		{
			return true;
		}
		
		return false;
		
	});

	Tester::addTest([]()
	{
	
		PointI3 verticeA = {0,0,0};
		PointI3 verticeB = {5,5,5};
		GraphEdge<PointI3*> edge(&verticeA,&verticeB);
		
		return
		(
			edge.getVertice(0) == &verticeA
				&&
			edge.getVertice(1) == &verticeB
		);
		
	});

	return Tester::runAllTests() ? 0 : 1;

}