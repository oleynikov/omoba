#pragma once

#include <deque>
#include "../Graph/Graph.hpp"

#include <iostream>

namespace o__O
{

	namespace Math
	{
	
		template <typename _GraphVertice>
		class AGraphPathFinder
		{

			public:
			
				typedef Graph<_GraphVertice>							_Graph;
				
				typedef typename _Graph::GraphVertices					_GraphVertices;
				
				typedef typename _GraphVertices::iterator				_VerticesItr;
				
				typedef std::pair<_GraphVertice,_GraphVertice>			_GraphVerticesPair;

				typedef std::deque<_GraphVerticesPair>					_GraphVerticesHash;
				
				typedef typename _GraphVerticesHash::iterator			_GraphVerticesHashItr;
				

				
				
											AGraphPathFinder( const _Graph& graph )
												:
													graph ( graph )
				{
				
				}

				_GraphVertices				findPath ( const _GraphVertice& verticeA , const _GraphVertice& verticeB )
				{

					this->graph.checkHasVertice(verticeA);
					this->graph.checkHasVertice(verticeB);

					return this->makePath(verticeA,verticeB);

				}

			protected:

				virtual _GraphVertices		makePath ( const _GraphVertice& verticeA , const _GraphVertice& verticeB ) = 0;
				
				static _GraphVertices		unwindPath ( const _GraphVerticesHash verticesHash )
				{

					_GraphVerticesHash	verticesHashCopy = verticesHash;
					_GraphVertice		verticeCurrent;
					_GraphVertice		verticeCurrentParent;
					_GraphVertices		pathReversed;
					
					
					
					for ( auto it = verticesHashCopy.begin() ; it != verticesHashCopy.end() ; it++ )
					{
					
						//	Get current vertice and it's parent
						verticeCurrent = (*it).second;
						verticeCurrentParent = (*it).first;
						
						std::cout << "Cur " << verticeCurrent[0] << " " << verticeCurrent[1] << std::endl;
						std::cout << "Par " << verticeCurrentParent[0] << " " << verticeCurrentParent[1] << std::endl << "----------" << std::endl;
					
					}
					
					std::cout << std::endl << "================" << std::endl;
					
					do
					{
					
						//	Get current vertice and it's parent
						verticeCurrent = (*verticesHashCopy.rbegin()).second;
						verticeCurrentParent = (*verticesHashCopy.rbegin()).first;
						
						//	Add current vertice to the reversed path
						pathReversed.push_back(verticeCurrent);
						
						if ( verticeCurrentParent == verticeCurrent )
							break;

						
						//	Erase elements from the map untill find current point't parent
						do
						{
							verticesHashCopy.pop_back();
						}
						while ( ! ( verticesHashCopy.empty() || verticeCurrentParent == (*verticesHashCopy.rbegin()).second ) );
					
					}
					while ( ! verticesHashCopy.size() == 1 );
					
					//	Reverse the reversed path
					return { pathReversed.rbegin() , pathReversed.rend() };
					
				}

				_Graph						graph;

		};
		
	}

}