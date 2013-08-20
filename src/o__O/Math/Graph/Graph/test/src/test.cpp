#include "../../../../../Tester/Tester.hpp"
#include "../../../../Point/Point.hpp"
#include "../../Graph.hpp"

using namespace o__O;
using namespace o__O::Math;



int main ( void )
{
	
	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		Graph<PointI2> graph;
		graph.addVertice(pointA);
		graph.addVertice(pointB);
		
		return
		(
			graph.hasVertice(PointI2{1,1})
				&&
			graph.hasVertice(PointI2{2,2})
		);
	
	});

	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		Graph<PointI2> graph;
		graph.addVertice(pointA);
		graph.addVertice(pointB);
		graph.addEdge(pointA,pointB);
		
		return
		(
			graph.hasVertice(pointA)
				&&
			graph.hasVertice(pointB)
				&&
			graph.areAdjacent(pointA,pointB)
		);
	
	});
	
	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		Graph<PointI2> graph;
		graph.addVertice(pointA);
		graph.addEdge(pointA,pointB);
		
		return
		(
			graph.hasVertice(pointA)
				&&
			graph.hasVertice(pointB)
				&&
			graph.areAdjacent(pointA,pointB)
		);
	
	});
	
	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		GraphEdge<PointI2> edge (pointA,pointB);
		Graph<PointI2> graph;
		
		graph.addEdge(edge);
		
		return
		(
			graph.areAdjacent(pointA,pointB)
				&&
			graph.hasVertice(pointA)
				&&
			graph.hasVertice(pointB)
		);
	
	});
	
	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		GraphEdge<PointI2> edge (pointA,pointB);
		Graph<PointI2> graph;
		
		graph.addEdge(edge);
		auto vertices = graph.getAdjacentVertices(pointA);
		
		return
		(
			vertices.size() == 1
				&&
			vertices[0] == pointB
		);
	
	});
	
	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		GraphEdge<PointI2> edge (pointA,pointB);
		Graph<PointI2> graph;
		
		graph.addEdge(edge);
		graph.removeEdges({1,1});
		
		auto vertices = graph.getAdjacentVertices(pointB);
		
		return
		(
			vertices.empty()
				&&
			graph.getVerticesNumber() == 2
				&&
			graph.getEdgesNumber() == 0
		);
	
	});
	
	Tester::addTest([]()
	{
	
		PointI2 pointA {1,1};
		PointI2 pointB {2,2};
		GraphEdge<PointI2> edge (pointA,pointB);
		Graph<PointI2> graph;
		
		graph.addEdge(edge);
		graph.removeVertice({1,1});
		
		auto vertices = graph.getAdjacentVertices(pointB);
		
		return
		(
			vertices.empty()
				&&
			graph.getVerticesNumber() == 1
				&&
			graph.getEdgesNumber() == 0
		);
	
	});
	
	return 	Tester::runAllTests() ? 0 : 1;

}