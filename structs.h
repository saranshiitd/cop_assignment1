#ifndef STRUCTS_H
#define STRUCTS_H
#include <vector>
using namespace std;
/*
* defnition of a 2D vertex 
*/
struct vertex2D{
	/**
	* end point 1 
	*/
	int a;
	/**
	* end point 2 
	*/
	int b;
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
};

/**
* defnition of a vertex 
*/
struct vertex3D{
	/**
	* end point 1 
	*/
	int a;
	/**
	 end point 2 
	*/
	int b;
	/**
	* end point 3 
	*/
 	int c;
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

struct plane
{
	float a;
	float b;
	float c;
	float d;	
	float epsilon ; 
	bool operator==(const direction& rhs )
	{	
		// float scalarProduct = dotProduct([a,b,c],[rhs.a,rhs.b,rhs.c]) ; 
		float[] vectorProduct = crossProduct([a,b,c],[rhs.a,rhs.b,rhs.c]) ; 
		float crossMagnitude = magnitude(vectorProduct) ; 
		return (crossMagnitude < epsilon)  &&  (abs(a*rhs.d - d*rhs.a)< epsilon) &&  (abs(b*rhs.d - d*rhs.b)< epsilon) &&  (abs(c*rhs.d - d*rhs.c)< epsilon) ;
	}

};

struct direction
{	
	float x;
	float y;
	float z;
	float epsilon ; 
	bool operator==(const direction& rhs )
	{
		float scalarProduct = dotProduct([x,y,z],[rhs.x,rhs.y,rhs.z]) ; 
		float[] vectorProduct = crossProduct([x,y,z],[rhs.x,rhs.y,rhs.z]) ; 
		float crossMagnitude = magnitude(vectorProduct) ; 
		return (crossMagnitude < epsilon) && (scalarProduct > 0 ) ; 
	}

};

float dotProduct(float vector1[] , float vector2[] ) {
	return vector1[0]*vector2[0] + vector1[1]*vector2[1] + vector1[2]*vector2[2] ; 
}

float[] crossProduct(float vector1[] , float vector2[]) {
	float product[3] ;
	product[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1] ; 
	product[1] = vector1[2]*vector2[0] - vector1[0]*vector2[2] ; 
	product[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0] ; 
	return product ; 
}

float magnitude(float vector1[]) {
	return vector1[0]*vector1[0] + vector1[1]*vector1[1] + vector1[2]*vector1[2] ;  
}

#endif