#include <climits>
#include <queue>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
#include "graph.h"

namespace UTILITY {


template <class AnyType>
const double CWeightedGraph<AnyType>::INFINITY = UINT_MAX;

template <class AnyType>
CWeightedGraph<AnyType>::CWeightedGraph( )
{
}

template <class AnyType>
CWeightedGraph<AnyType>::~CWeightedGraph( )
{
	std::map<AnyType, CVertex<AnyType> *>::iterator itr;

	while( vertexMap.size( ) > 0 )
	{
		itr = vertexMap.begin( );
		delete itr->second;
		vertexMap.erase( itr );
	}
}

template <class AnyType>
CVertex<AnyType> *CWeightedGraph<AnyType>::getVertex( AnyType &v )
{
	std::map<AnyType, CVertex<AnyType> *>::iterator itr = vertexMap.find( v );

	if( itr != vertexMap.end( ) )
		return itr->second;
	else {
		CVertex<AnyType> *vert = new CVertex<AnyType>( v, 0 );
		vertexMap[ v ] = vert;
		return vert;
	}
}


template <class AnyType>
void CWeightedGraph<AnyType>::addDirectedEdge( AnyType &startVertex, AnyType &endVertex, unsigned int weight )
{
	CVertex<AnyType> *pV1 = getVertex( startVertex );
	CVertex<AnyType> *pV2 = getVertex( endVertex );
	pV1->adjacentVertices.push_front( new CEdge<AnyType>( *pV2, weight ) );
}

template <class AnyType>
void CWeightedGraph<AnyType>::addEdge( AnyType &v1, AnyType &v2, unsigned int weight )
{
	CVertex<AnyType> *pV1 = getVertex( v1 );
	CVertex<AnyType> *pV2 = getVertex( v2 );
	pV1->adjacentVertices.push_front( new CEdge<AnyType>( *pV2, weight ) );
	pV2->adjacentVertices.push_front( new CEdge<AnyType>( *pV1, weight ) );
}

template <class AnyType>
void CWeightedGraph<AnyType>::dijkstra( AnyType &startVertex )
{
	shortestPath.clear( );
	priority_queue<CVertex<AnyType> *, vector<CVertex<AnyType> *>, CVertexDistanceComparer<AnyType> > distanceMinHeap; 

	CVertex<AnyType> *currentVertex = getVertex( startVertex );

	//shortestPath.push_back( currentVertex );
	unsigned int numberOfVerticesProcessed = 0;
	reset( );
	currentVertex->distance = 0;
	


	while( numberOfVerticesProcessed < vertexMap.size( ) )
	{
		std::list<CEdge<AnyType> *> &adjacents = currentVertex->adjacentVertices;

		std::list<CEdge<AnyType> *>::iterator itr;

		for( itr = adjacents.begin( ); itr != adjacents.end( ); ++itr )
		{
			CEdge<AnyType> *edge = (*itr);
			/*(*itr)->destVertex*/
			edge->destVertex.distance = min( currentVertex->distance + edge->weight, edge->destVertex.distance );
			if( edge->destVertex.scratch == 0 )
			{
				edge->destVertex.scratch = 1;
				distanceMinHeap.push( &edge->destVertex );
			}
		}

		currentVertex = distanceMinHeap.top( );
		distanceMinHeap.pop( );

		shortestPath.push_back( currentVertex );
		numberOfVerticesProcessed++;
	}
	
	//cout << endl;
	//std::map<AnyType, CVertex<AnyType> *>::iterator itr;
	//for( itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
	//	cout << itr->first << " " << itr->second->getDistance( ) << endl;
}

template <class AnyType>
void CWeightedGraph<AnyType>::reset( )
{
	std::map<AnyType, CVertex<AnyType> *>::iterator itr;

	for( itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
		(itr->second)->reset( );
}



} // end of namespace...