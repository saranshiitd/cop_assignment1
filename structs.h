#ifndef STRUCTS_H
#define STRUCTS_H

using namespace std;
// defnition of a 2D vertex
struct vertex2D{
	// end point 1
	int a;
	// end point 2
	int b;
};

// definition of a 2D edge
struct edge2D{
	// // end point 1
	vertex2D v1;
	// end point 2
	vertex2D v2;
	bool hidden;
};

// defnition of a vertex
struct vertex3D{
	// end point 1
	int a;
	// end point 2
	int b;
	// end point 3
	int c;
};

// definition of a 3D edge
struct edge3D{
	// // end point 1
	vertex3D v1;
	// end point 2
	vertex3D v2;
};

// is used in both 
// 1. PEVR where we need degree of every vertex and the corrosponding edges
// 2. During face-loop generation method in which we need vertex-edge list of 
//    every vertex on each plane
struct vertexEdgeList
{
	vertex3D v;
	std::vector<edge3D> e;
};

struct plane
{
	int a;
	int b;
	int c;
	int d;	
};

#endif