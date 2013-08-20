#pragma once

#include <algorithm>
#include "AGraphPathFinder.hpp"


#include <iostream>
namespace o__O
{

	namespace Math
	{

		template <typename _GraphVertice>
		class DijkstraGraphPathFinder
			:
				public AGraphPathFinder<_GraphVertice>
		{
		
			public:
		
				typedef AGraphPathFinder<_GraphVertice>						_AGraphPathFinder;
				
				typedef typename _AGraphPathFinder::_Graph					_Graph;
				
				typedef typename _AGraphPathFinder::_GraphVertices			_GraphVertices;
				
				typedef typename _GraphVertices::iterator					_GraphVerticesItr;
				
				typedef typename _AGraphPathFinder::_GraphVerticesPair		_GraphVerticesPair;

				typedef typename _AGraphPathFinder::_GraphVerticesHash		_GraphVerticesHash;
				
				
				

											DijkstraGraphPathFinder ( const _Graph& graph )
												:
													_AGraphPathFinder ( graph )
				{
				
				}
				
			protected:

				virtual _GraphVertices		makePath ( const _GraphVertice& verticeA , const _GraphVertice& verticeB )
				{

					_GraphVerticesHash	verticesHash = { _GraphVerticesPair(verticeA,verticeA) };
					_GraphVertices		verticesUnexplored = { verticeA };
					_GraphVertices		verticesExplored;
					_GraphVertices		verticesAdjancent;
					_GraphVerticesItr	verticesAdjancentItr;
					_GraphVertice		verticeCurrent;
					
					while ( ! verticesUnexplored.empty() )
					{
					
						verticeCurrent =  *(verticesUnexplored.begin());
						verticesUnexplored.erase(verticesUnexplored.begin());
						verticesExplored.push_back(verticeCurrent);
						
						verticesAdjancent = this->graph.getAdjacentVertices(verticeCurrent);
						for ( verticesAdjancentItr = verticesAdjancent.begin() ; verticesAdjancentItr != verticesAdjancent.end() ; verticesAdjancentItr++ )
						{

							//	Add vertice pair
							verticesHash.push_back(_GraphVerticesPair(verticeCurrent,*verticesAdjancentItr));
						

							//	Vertice equals END
							if ( *verticesAdjancentItr == verticeB )
							{
		
								return _AGraphPathFinder::unwindPath(verticesHash);
							
							}
						
							//	Vertice already processed
							if
							(
								std::find(verticesExplored.begin(),verticesExplored.end(),*verticesAdjancentItr) == verticesExplored.end()
									&&
								std::find(verticesUnexplored.begin(),verticesUnexplored.end(),*verticesAdjancentItr) == verticesUnexplored.end()
							)
							{
							
								verticesUnexplored.push_back(*verticesAdjancentItr);
							
							}


						}
					}

					throw ExcPathCouldNotBeFound();

				}

		};
		
	}

}