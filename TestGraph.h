#ifndef _TESTGRAPH_H_
#define _TESTGRAPH_H_
/*
 *	Graph.h
 *
 *	
 *
 *	Coded by Joseph A. Marrero
 *	3/15/2007
 */
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "graph.h"
using namespace std;





void initialize( );
void deinitialize( );

void render( );
void resize( int width, int height );
void keyboard_keypress( unsigned char key, int x, int y );
void idle( );
void writeText( void *font, std::string &text, int x, int y );

unsigned int winWidth = 600;
unsigned int winHeight = 400;


#define MAX_WEIGHT		100

class CGraphNode
{
protected:
	float m_X, m_Y;
	string m_Name;
	static const int size = 15;
	GLUquadric *pQuadric;

public:
	CGraphNode( );
	CGraphNode( float x, float y, string name = "unk" );
	CGraphNode( const CGraphNode &other );
	~CGraphNode( );

	void render( );

	bool operator<( const CGraphNode &other ) const;
	CGraphNode &operator=( const CGraphNode &rhs );

	float getX( ) const { return m_X; }
	float getY( ) const { return m_Y; }
	const string &getName( ) const { return m_Name; }
};

class CGraphEdge
{
  protected:
	CGraphNode *n1, *n2;
	float weight;

  public:
	CGraphEdge( );
	CGraphEdge( CGraphNode *N1, CGraphNode *N2, float w );
	CGraphEdge( const CGraphEdge &other );
	~CGraphEdge( );

	void renderEdge( );
};


#define NUMBER_OF_VERTICES	10




char *nodeNames[ NUMBER_OF_VERTICES ] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

UTILITY::CWeightedGraph<CGraphNode> theGraph;
std::vector<CGraphNode> nodes;
std::vector<CGraphEdge> edges;

#endif
