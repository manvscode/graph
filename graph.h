#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <map>
#include <string>
using namespace std;


namespace UTILITY {

template <class AnyType>
class CEdge;

template <class AnyType>
class CWeightedGraph;

/*
 *	CVertex
 *
 *	A representation of a vertex in a graph.
 */
template <class AnyType>
class CVertex
{
	friend class CWeightedGraph<AnyType>;

  protected:
	std::list<CEdge<AnyType> *> adjacentVertices;
	AnyType data;
	unsigned int distance;
	unsigned int scratch;

  public:
	CVertex( )
		: data(), distance(CWeightedGraph::INFINITY), scratch(0)
	{}

	CVertex( AnyType &obj, double theDistance )
		: data(obj), distance(theDistance), scratch(0)
	{}

	~CVertex( )
	{
		std::list<CEdge<AnyType> *>::iterator itr;

		while( adjacentVertices.size( ) > 0 )
		{
			itr = adjacentVertices.begin( );
			delete *itr;
			adjacentVertices.erase( itr );
		}
	}

	unsigned int getDistance( ) const
	{ return distance; }

	void reset( )
	{ distance = CWeightedGraph<AnyType>::INFINITY; scratch = 0; }

	AnyType getData( ) const { return data; }
};

template <class AnyType>
class CVertexDistanceComparer
{
  public:
	
	bool operator()( const CVertex<AnyType> *v1, const CVertex<AnyType> *v2 ) const
	{
		return v1->getDistance( ) < v2->getDistance( );
	}
};


/*
 *	CEdge
 *
 *	A representation of an edge in a graph.
 */
template <class AnyType>
class CEdge
{
	friend class CWeightedGraph<AnyType>;

  protected:
	CVertex<AnyType> &destVertex;
	unsigned int weight;

  public:
	CEdge( CVertex<AnyType> &v, unsigned int theweight )
		: destVertex(v), weight(theweight)
	{}
};



template <class AnyType>
class CWeightedGraph
{
	friend class CVertex<AnyType>;
	friend class CEdge<AnyType>;

  public:
	CWeightedGraph( );
	virtual ~CWeightedGraph( );
	

	void addDirectedEdge( AnyType &startVertex, AnyType &endVertex, unsigned int weight );
	void addEdge( AnyType &v1, AnyType &v2, unsigned int weight );

	void dijkstra( AnyType &startVertex );
	void reset( );

	std::list<CVertex<AnyType> *> getShortestPath( ) const;

  protected:
	static const double INFINITY;
	std::map<AnyType, CVertex<AnyType> *> vertexMap;
	std::list<CVertex<AnyType> *> shortestPath;

	CVertex<AnyType> *getVertex( AnyType &v );
};

template <class AnyType>
inline std::list<CVertex<AnyType> *> CWeightedGraph<AnyType>::getShortestPath( ) const
{ return shortestPath; }



} // end of namespace...
#include "graph.inl"
#endif
