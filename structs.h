#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
#include <cmath> 
using namespace std;
/*
* defnition of a 2D vertex 
*/

// tolerance for error in floats
#define epsilon 0.01
 
struct vertex2D{
	/**
	* end point 1 
	*/
	float a;
	/**
	* end point 2 
	*/
	float b;

	vertex2D(){
		a = b = 0;
	}

	vertex2D(float m, float n){
		a = m;
		b = n;
	}

	// equality for two 3D vertices (method overloading)
	bool operator==(const vertex2D& n)
	{
	    return ((abs(a - n.a) < epsilon) && (abs(b - n.b) < epsilon));
	}
};

/**
* definition of a 2D edge 
*/
struct edge2D{
	/**
	* end point 1 
	*/
	vertex2D v1;
	/**
	* end point 2 
	*/
	vertex2D v2;

	edge2D(){

	}
	edge2D(vertex2D m, vertex2D n){
		v1.a = m.a;
		v1.b = m.b;
		v2.a = n.a;
		v2.b = n.b;
	}

	bool hidden = false;


	// equality for two 2D edges  (method overloading)
	bool operator==(const edge2D& n)
	{
	    return ((v1 == n.v1) && (v2 == n.v2) && ( hidden == n.hidden)) || ((v1 == n.v2) && (v2 == n.v1) && ( hidden == n.hidden));
	}
};

/**
* defnition of a vertex 
*/
struct vertex3D{
	/**
	* end point 1 
	*/
	float a;
	/**
	 end point 2 
	*/
	float b;
	/**
	* end point 3 
	*/
 	float c;

 	vertex3D(){
 		a = b = c = 0;
 	}

 	vertex3D(float m, float n, float o){
		a = m;
		b = n;
		c = o;
	}


 	// equality for two 3D vertices (method overloading)
	bool operator==(const vertex3D& n)
	{
	    return (abs(a - n.a) < epsilon) && (abs(b - n.b) < epsilon) && (abs(c - n.c) < epsilon);
	}
};

/**
* definition of a 3D edge 
*/
struct edge3D{
	/**
	* end point 1 
	*/
	vertex3D v1;
	/**
	* end point 2 
	*/
	vertex3D v2;

	edge3D(){

	}

	edge3D(vertex3D m, vertex3D n){
		v1 = {m.a, m.b, m.c};
		v2 = {n.a, n.b, n.c};
	}

	// equality for two vertecies (method overloading)
	bool operator==(const edge3D& n)
	{
	    return ((v1 == n.v1) && (v2 == n.v2)) || ((v1 == n.v2) && (v2 == n.v1));
	}
};

/**
* is used in both 
* 1. PEVR where we need degree of every vertex and the corrosponding edges
* 2. During face-loop generation method in which we need vertex-edge list of 
*    every vertex on each plane 
*/
struct vertexEdgeList
{
	vertex3D v;
	vector<edge3D> e ;
};

//////////////////////////////////////////////////////////////////////////////////////////

//! helping methods
float dotProduct(float vector1[] , float vector2[] );

float *crossProduct(float vector1[] , float vector2[]);

float magnitude(float vector1[]);

///////////////////////////////////////////////////////////////////////////////////////////

struct plane
{
	float a;
	float b;
	float c;
	float d;	


	bool operator==(const plane& rhs )
	{	
		// float scalarProduct = dotProduct([a,b,c],[rhs.a,rhs.b,rhs.c]) ; 
		float v1[] = {a, b, c};
		float v2[] = {rhs.a,rhs.b,rhs.c} ; 
		float* vectorProduct = crossProduct(v1, v2); 
		float crossMagnitude = magnitude(vectorProduct) ; 
		return (crossMagnitude < epsilon)  &&  (abs(a*rhs.d - d*rhs.a)< epsilon) &&  (abs(b*rhs.d - d*rhs.b)< epsilon) &&  (abs(c*rhs.d - d*rhs.c)< epsilon) ;
	}

};

struct direction
{	
	float x;
	float y;
	float z;

	bool operator==(const direction& rhs )
	{
		float v1[] = {x, y, z};
		float v2[] = {rhs.x,rhs.y,rhs.z} ;
		float scalarProduct = dotProduct(v1, v2) ; 
		float* vectorProduct = crossProduct(v1, v2) ; 
		float crossMagnitude = magnitude(vectorProduct) ; 
		return (crossMagnitude < epsilon) && (scalarProduct > 0 ) ; 
	}

};

struct vertexEdgePair
{
	vertex3D v ;
	edge3D e ;

	vertexEdgePair(vertex3D vertex , edge3D  edge) {
		v = vertex ;
		e = edge ; 
	}

};

struct edgeVertexTriplet
{
	vertex3D v ;
	edge3D e ;
	edge3D reference ; 
	plane p ;
	edgeVertexTriplet(){}
	edgeVertexTriplet(vertex3D vertex , edge3D edge, edge3D r, plane pln) {
		v = vertex ; 
		e = edge ;
		reference = r ;
		p = pln ;
	}
};

struct planeVEL{  // plane vertexEdgeList
	plane  p ;
	std::vector<vertexEdgeList> velList;

	// costructors
	planeVEL(){} 
	planeVEL(plane pl , std::vector<vertexEdgeList> v) {
		p = pl ;
		velList = v ; 
	}

} ; 

#endif