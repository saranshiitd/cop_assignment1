#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
#include <cmath> 
using namespace std;
/*
* defnition of a 2D vertex 
*/

// tolerance for error in floats
float epsilon ; 

struct vertex2D{
	/**
	* end point 1 
	*/
	float a;
	/**
	* end point 2 
	*/
	float b;

	float epsilon = 0.01 ;

	// equality for two 3D vertices (method overloading)
	bool operator==(const vertex2D& n)
	{
	    return (abs(a - n.a) < epsilon) && (abs(b - n.b) < epsilon);
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
	bool hidden;

	float epsilon = 0.01 ;

	// equality for two 2D edges  (method overloading)
	bool operator==(const edge2D& n)
	{
	    return (v1 == n.v1) && (v2 == n.v2) && ( hidden == n.hidden);
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

 	float epsilon = 0.01 ;

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

	// equality for two vertecies (method overloading)
	bool operator==(const edge3D& n)
	{
	    return (v1 == n.v1) && (v2 == n.v2);
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
	vector<edge3D> e;
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
	float epsilon = 0.01 ;
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
	float epsilon = 0.01 ;
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


#endif