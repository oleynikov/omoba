#pragma once

#include "../../Exception/Exception.hpp"



namespace o__O
{

	namespace Math
	{
	
		class GraphEdgeBase
		{
		
			protected:
			
				static void				checkVerticeId ( const int verticeId )
				{
				
					if ( verticeId < 0 || verticeId > 1 )
					{
					
						throw ExcInvalidVerticeId();
					
					}
				
				}
				
		};

		template <typename GraphVertice>
		class GraphEdge
			:
				public GraphEdgeBase
		{

			public:

										GraphEdge ( const GraphVertice& verticeA , const GraphVertice& verticeB )
				{
					
					//	Set vertices values
					this->vertices[0] = verticeA;
					this->vertices[1] = verticeB;
					
				}

				const GraphVertice&		operator[] ( const int verticeId ) const
				{
				
					GraphEdgeBase::checkVerticeId(verticeId);

					return this->vertices[verticeId];

				}

				GraphVertice&			operator[] ( const int verticeId )
				{
				
					GraphEdgeBase::checkVerticeId(verticeId);

					return this->vertices[verticeId];

				}

				const GraphVertice&		getVertice ( const int verticeId ) const
				{
				
					return (*this)[verticeId];

				}

				GraphVertice&			getVertice ( const int verticeId )
				{
				
					return (*this)[verticeId];

				}
				
				bool					hasVertice ( const GraphVertice& vertice )
				{
				
					return
					(
						this->vertices[0] == vertice
							||
						this->vertices[1] == vertice
					);
				
				}
				
			private:
			
				GraphVertice			vertices[2];

		};

	}
	
}