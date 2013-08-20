#include "../../../../../Tester/Tester.hpp"
#include "../../../GraphFactory/PlaneGraphFactory.hpp"
#include "../../DijkstraGraphPathFinder.hpp"

using namespace o__O;
using namespace o__O::Math;



int main ( void )
{

	Tester::addTest([]()
	{
	
		PlaneGraphFactory graphFactory(5,5,1);
		PlaneGraph graph = graphFactory.makeGraph();
		DijkstraGraphPathFinder<PointI2> pathFinder(graph);
		std::vector<PointI2> path = pathFinder.findPath({0,0},{1,1});
	
		std::cout << path[0][0] << " " << path[0][1] << " " << std::endl;
		std::cout << path[1][0] << " " << path[1][1] << " " << std::endl;
		std::cout << path[2][0] << " " << path[2][1] << " " << std::endl;
		
		
		return
		(
			path[0] == PointI2 {0,0}
				&&
			path[1] == PointI2 {0,1}
		);
	
	});
	
	return 	Tester::runAllTests() ? 0 : 1;

}