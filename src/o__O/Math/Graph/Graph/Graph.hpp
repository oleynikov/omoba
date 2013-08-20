#pragma once

#include <vector>
#include <algorithm>
#include <initializer_list>
#include "../../Exception/Exception.hpp"
#include "../GraphEdge/GraphEdge.hpp"



namespace o__O
{
	
	namespace Math
	{
	
		template <typename GraphVertice>
		class Graph
		{
			
			public:
		
				typedef std::vector<GraphVertice>				GraphVertices;
				
				typedef typename GraphVertices::iterator		VerticesItr;
				
				typedef GraphEdge<GraphVertice>					GraphEdgeCompatible;
				
				typedef std::vector<GraphEdgeCompatible>		GraphEdges;
				
				typedef typename GraphEdges::const_iterator		GraphEdgesConstItr;

				void				addVertice ( const GraphVertice& vertice )
				{
				
					//	Ensure that the vertice doesn't exist yet
					this->checkHasNoVertice(vertice);

					//	Add the vertice
					this->vertices.push_back(vertice);

				}

				void				addEdge ( const GraphEdgeCompatible& graphEdge )
				{
				
					//	Add edge to the edges collection
					this->edges.push_back(graphEdge);

					//	Add edge's vertices to the vertices collection
					//	An `ExcVerticeAlreadyExists` may occure and it's totally Ok
					try
					{
						this->addVertice(graphEdge[0]);
					}
					catch ( ExcVerticeAlreadyExists ) { }

					try
					{
						this->addVertice(graphEdge[1]);
					}
					catch ( ExcVerticeAlreadyExists ) { }

				}

				void				addEdge ( const GraphVertice& verticeA , const GraphVertice& verticeB )
				{
					
					//	Add a new edge to the graph
					this->addEdge(GraphEdgeCompatible(verticeA,verticeB));

				}
				
				void				removeVertice ( const GraphVertice& vertice )
				{
				
					//	Remove all edges adjacent to the vertice
					this->removeEdges(vertice);
					
					//	Find vertice iterator
					auto verticeItr = this->getVerticeItr(vertice);
					
					//	Remove the vertice
					this->vertices.erase(verticeItr);
				
				}
				
				void				removeEdges ( const GraphVertice& vertice )
				{
				
					for ( auto edgesItr = this->edges.begin() ; edgesItr != this->edges.end() ; )
					{
					
						if ( (*edgesItr).hasVertice(vertice) )
						{
						
							this->edges.erase(edgesItr);
							continue;
						
						}
						
						edgesItr++;
					
					}
				
				}
				
				int					getVerticesNumber ( void ) const
				{
				
					return this->vertices.size();
				
				}
				
				int					getEdgesNumber ( void ) const
				{
				
					return this->edges.size();
				
				}
				
				GraphVertices		getAdjacentVertices ( const GraphVertice& vertice )
				{

					//	Ensure that the graph has the vertice
					this->checkHasVertice(vertice);
				
					//	Collection of vertice neighbours
					GraphVertices verticeNeighbours;

					//	Iterate over edges collection
					for ( auto edgesItr = this->edges.begin(); edgesItr != this->edges.end() ; edgesItr++ )
					{
					
						//	If one of the edge's vertices equals the `vertice`, add the other to the neighbours collection
						if ( (*edgesItr)[0] == vertice )
						{

							verticeNeighbours.push_back((*edgesItr)[1]);

						}
						
						else if ( (*edgesItr)[1] == vertice )
						{

							verticeNeighbours.push_back((*edgesItr)[0]);

						}

					}

					return verticeNeighbours;

				}

				bool				areAdjacent ( const GraphVertice& verticeA , const GraphVertice& verticeB )
				{

					//	Ensure that the graph has these vertices
					this->checkHasVertice(verticeA);
					this->checkHasVertice(verticeB);

					for ( auto edgesItr = this->edges.begin() ; edgesItr != this->edges.end() ; edgesItr++ )
					{

						if
						(
							(
								(*edgesItr).getVertice(0) == verticeA
									&& 
								(*edgesItr).getVertice(1) == verticeB
							)
								||
							(
								(*edgesItr).getVertice(1) == verticeA
									&& 
								(*edgesItr).getVertice(0) == verticeB
							)
						)
						{

							return true;

						}
						
					}
					
					return false;
					
				}

				bool				hasVertice ( const GraphVertice& vertice ) const
				{

					return	std::find(this->vertices.begin(),this->vertices.end(),vertice) != this->vertices.end();

				}

				void				checkHasVertice ( const GraphVertice& vertice ) const
				{

					if ( ! this->hasVertice(vertice) )
					{
					
						throw ExcVerticeDoesNotExist();
						
					}

				}

				void				checkHasNoVertice ( const GraphVertice& vertice ) const
				{
				
					if ( this->hasVertice(vertice) )
					{
					
						throw ExcVerticeAlreadyExists();
						
					}
				
				}
				
			private:
			
				VerticesItr			getVerticeItr ( const GraphVertice& vertice )
				{
				
					for ( auto verticesItr = this->vertices.begin() ; verticesItr != this->vertices.end() ; verticesItr++ )
					{
					
						if ( *verticesItr == vertice )
						{
						
							return verticesItr;
							
						}
					
					}
					
					return this->vertices.end();
				
				}

				GraphVertices		vertices;

				GraphEdges			edges;

		};
	
	}

}