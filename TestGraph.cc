/*
 *	Graph.cc
 * 
 *	
 *
 *	Coded by Joseph A. Marrero
 *	3/15/2007
 */
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "TestGraph.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

int main( int argc, char *argv[] )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

	//glutCreateWindow( "Graph" );

	glutGameModeString( "1024x768:16" );
	if( glutGameModeGet( GLUT_GAME_MODE_POSSIBLE ) )
		glutEnterGameMode( );
	else
	{
		cerr << "The requested mode is not available!" << endl;
		return -1;	
	}

	glutDisplayFunc( render );
	glutReshapeFunc( resize );
	glutKeyboardFunc( keyboard_keypress );
	glutIdleFunc( idle );

	initialize( );
	glutMainLoop( );
	deinitialize( );

	return 0;
}


void initialize( )
{
	//glEnable( GL_ALPHA_TEST );
	
	glEnable( GL_POINT_SMOOTH );
	glEnable( GL_LINE_SMOOTH );
	//glEnable( GL_POLYGON_SMOOTH );
	glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	//glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glLineStipple( 1, 0xF0F0 );

	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );		
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );


	glPixelStorei( GL_PACK_ALIGNMENT, 4 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	
	srand( (unsigned int) time(NULL) );

	////for( int i = 0; i < NUMBER_OF_VERTICES; i++ )
	////{
	////	ostringstream oss;
	////	oss << "n" << rand() % NUMBER_OF_VERTICES;
	////	nodes.push_back( CGraphNode( rand() % winWidth, rand() % winHeight, oss.str() ) );
	////}

	////for( int i = 0; i < NUMBER_OF_VERTICES; i++ )
	////{
	////	theGraph.addDirectedEdge( nodes[ rand() % NUMBER_OF_VERTICES ], nodes[ rand() % NUMBER_OF_VERTICES ], rand() % MAX_WEIGHT );
	////}

	////theGraph.dijkstra( nodes[ rand() % NUMBER_OF_VERTICES ] );




	//Graph
	CGraphNode a(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "A");
	CGraphNode b(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "B");
	CGraphNode c(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "C");
	CGraphNode d(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "D");
	CGraphNode e(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "E");
	CGraphNode f(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "F");
	CGraphNode g(80 * ((rand() % 7) + 1),  80 * ((rand() % 7) + 1), "G");
	
	nodes.push_back( a );
	nodes.push_back( b );
	nodes.push_back( c );
	nodes.push_back( d );
	nodes.push_back( e );
	nodes.push_back( f );
	nodes.push_back( g );

	unsigned int i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( b, a, i );
	CGraphEdge e1( &nodes[ 1 ], &nodes[ 0 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( a, f, i );
	CGraphEdge e2( &nodes[ 0 ], &nodes[ 5 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( b, c, i );
	CGraphEdge e3( &nodes[ 1 ], &nodes[ 2 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( c, a, i );
	CGraphEdge e4( &nodes[ 2 ], &nodes[ 0 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( f, b, i );
	CGraphEdge e5( &nodes[ 5 ], &nodes[ 1 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( e, f, i );
	CGraphEdge e6( &nodes[ 4 ], &nodes[ 5 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( d, e, i );
	CGraphEdge e7( &nodes[ 3 ], &nodes[ 4 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( c, d, i );
	CGraphEdge e8( &nodes[ 2 ], &nodes[ 3 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( c, g, i );
	CGraphEdge e9( &nodes[ 2 ], &nodes[ 6 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( g, a, i );
	CGraphEdge e10( &nodes[ 6 ], &nodes[ 0 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( g, e, i );
	CGraphEdge e11( &nodes[ 6 ], &nodes[ 4 ], i );

	i = (rand() % 22) + 1;
	theGraph.addDirectedEdge( g, d, i );
	CGraphEdge e12( &nodes[ 6 ], &nodes[ 3 ], i );

	
	
	
	
	
	
	
	
	
	
	
	
	
	edges.push_back( e1 );
	edges.push_back( e2 );
	edges.push_back( e3 );
	edges.push_back( e4 );
	edges.push_back( e5 );
	edges.push_back( e6 );
	edges.push_back( e7 );
	edges.push_back( e8 );
	edges.push_back( e9 );
	edges.push_back( e10 );
	edges.push_back( e11 );
	edges.push_back( e12 );


	theGraph.dijkstra( c );
	
}

void deinitialize( )
{
	// TO DO: Deinitialization code goes here...
}


void render( )
{
	glClearColor( 0.1f, 0.1f, 0.1f, 0.1f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity( );
	
	// the graph
	for( int i = 0; i < edges.size( ); i++ )
		edges[ i ].renderEdge( );

	for( int i = 0; i < nodes.size( ); i++ )
		nodes[ i ].render( );

	std::list<UTILITY::CVertex<CGraphNode> *> &shortestPath = theGraph.getShortestPath( );
	std::list<UTILITY::CVertex<CGraphNode> *>::iterator itr;

	int cnt = 7;
	writeText( GLUT_BITMAP_9_BY_15, string("Vertex - Distance"), 800, 500 + 20 * cnt );
	for( itr = shortestPath.begin( ); itr != shortestPath.end(); ++itr )
	{
		cnt--;
		ostringstream oss;
		oss << (*itr)->getData( ).getName() << " - " << (*itr)->getDistance();
		writeText( GLUT_BITMAP_9_BY_15, oss.str(), 800, 500 + 20 * cnt );
	}



	/* Write text */
	int width = glutGet((GLenum)GLUT_WINDOW_WIDTH);
	int height = glutGet((GLenum)GLUT_WINDOW_HEIGHT);

	writeText( GLUT_BITMAP_HELVETICA_18, std::string("Graph"), 2, 22 );
	writeText( GLUT_BITMAP_9_BY_15, std::string("Press <ESC> to quit."), 2, 5 );
	
	glutSwapBuffers( );
}

void resize( int width, int height )
{
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	

	if( height == 0 )
		height = 1;

	winWidth = width;
	winHeight = height;
		
	glOrtho( 0.0, width, 0.0, height, -10.0, 10.0 );
	glMatrixMode( GL_MODELVIEW );
}

void keyboard_keypress( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 27:
			deinitialize( );
			exit( 0 );
			break;
		default:
			break;
	}

}

void idle( )
{ glutPostRedisplay( ); }

void writeText( void *font, std::string &text, int x, int y )
{
	int width = glutGet( (GLenum) GLUT_WINDOW_WIDTH );
	int height = glutGet( (GLenum) GLUT_WINDOW_HEIGHT );

	glDisable( GL_DEPTH_TEST );
	//glDisable( GL_TEXTURE_2D );
	//glDisable( GL_LIGHTING );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix( );
		glLoadIdentity( );	
		glOrtho( 0, width, 0, height, 1.0, 10.0 );
			
		glMatrixMode( GL_MODELVIEW );
		glPushMatrix( );
			glLoadIdentity( );
			glColor3f( 1.0f, 1.0f, 1.0f );
			glTranslatef( 0.0f, 0.0f, -1.0f );
			glRasterPos2i( x, y );

			for( unsigned int i = 0; i < text.size( ); i++ )
				glutBitmapCharacter( font, text[ i ] );
			
		glPopMatrix( );
		glMatrixMode( GL_PROJECTION );
	glPopMatrix( );
	glMatrixMode( GL_MODELVIEW );

	//glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );
	//glEnable( GL_TEXTURE_2D );

}

/*
 *	Graph Node stuff
 */
CGraphNode::CGraphNode( )
 : m_X(0), m_Y(0), m_Name("")
{
	//pQuadric = gluNewQuadric( );
}

CGraphNode::CGraphNode( float x, float y, string name )
 : m_X(x), m_Y(y), m_Name(name)
{
	//pQuadric = gluNewQuadric( );
}

CGraphNode::CGraphNode( const CGraphNode &other )
 : m_X(other.m_X), m_Y(other.m_Y), m_Name(other.m_Name)
{
	pQuadric = gluNewQuadric( );
}

CGraphNode::~CGraphNode( )
{
	//gluDeleteQuadric( pQuadric );
}

void CGraphNode::render( )
{
	glColor4f( 1.0f, 0.2f, 0.2f, 1.0f );
	
	glPushMatrix( );
		pQuadric = gluNewQuadric( );
		glTranslatef( m_X, m_Y, -1.0f );
		gluSphere( pQuadric, size, 12, 6 );
		gluDeleteQuadric( pQuadric );
	glPopMatrix( );


	writeText( GLUT_BITMAP_9_BY_15, m_Name, m_X-5, m_Y-5 );
}

bool CGraphNode::operator<( const CGraphNode &other ) const
{ 
	return m_Name < other.m_Name;
}

CGraphNode &CGraphNode::operator=( const CGraphNode &rhs )
{
	if( this != &rhs )
	{
		m_X = rhs.m_X;
		m_Y = rhs.m_Y;
		m_Name = rhs.m_Name;
	}

	return *this;
}


CGraphEdge::CGraphEdge( )
 : n1(0), n2(0), weight(0.0f)
{
}

CGraphEdge::CGraphEdge( CGraphNode *N1, CGraphNode *N2, float w )
 : n1(N1), n2(N2), weight(w)
{
}

CGraphEdge::CGraphEdge( const CGraphEdge &other )
 : n1(other.n1), n2(other.n2), weight(other.weight)
{

}

CGraphEdge::~CGraphEdge( )
{
}

void CGraphEdge::renderEdge( )
{
	ostringstream oss;
	glPushAttrib( GL_CURRENT_BIT );
		glColor3f( 1.0f, 1.0f, 0.0f );
		glEnable( GL_LINE_STIPPLE );
		
		glPushMatrix( );
			glBegin( GL_LINES );
				glVertex2f( n1->getX( ), n1->getY( ) );
				glVertex2f( n2->getX( ), n2->getY( ) );

				//glVertex2f( n2->getX( )+8, n2->getY( ) );
				//glVertex2f( n2->getX( ), n2->getY( ) );

				//glVertex2f( n2->getX( )-8, n2->getY( ) );
				//glVertex2f( n2->getX( ), n2->getY( ) );
			glEnd( );

			oss.setf( ios::fixed );
			oss.width( 2 );
			oss.precision( 0 );
			oss << weight;
			writeText( GLUT_BITMAP_8_BY_13, oss.str( ), (n1->getX( ) + n2->getX( ))/2.0f, (n1->getY( ) + n2->getY( ))/2.0f );
		glPopMatrix( );
		glDisable( GL_LINE_STIPPLE );
	glPopAttrib( );
}