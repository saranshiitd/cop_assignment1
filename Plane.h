#ifndef PLANE_H
#define PLANE_H
#include "structs.h"
using namespace std;


float findAngle(edge3D refEdge, edge3D otherEdge, vertex3D refVertex,plane p) ;

bool compareTriplets(edgeVertexTriplet t1 , edgeVertexTriplet t2) ;

class Plane
{
	public:
		//! struct plane that defines a plane
		plane p;

		//!	list of all vertices on the plane
		std::vector<vertex3D> vList;

		//! list of all edges on the plane
		std::vector<edge3D> eList;

		//! list of vetex-edgesOnVertex for all vertices on the plane
		std::vector<vertexEdgeList> veListList;

		//! applies the method sortEdgesOnVertex on each vertex of a plane
		//! just modifies the "std::vector<vertexEdgeList> veList" with edges sorted on 
		//! each vertex
		void sortEdgesOnVertices();

	private:

		//! finds clockwise angle between two edges with a common vertex wrt a plane normal

		//float findAngle(edge3D refEdge, edge3D otherEdge, vertex3D refVertex) ; 
		
		//! find by getting vectors witth initial vertex refVertex clockwise angle is found by getting dot product 
		//! of the two vectors with normal vector if dot product greater than 0 then negative 
		//! of angle found by cos inverse dot product and vice versa 


		//! sort edges on a vertex of a plane in ascending order on the basis of the clockwise
		//! angle with respect to a edge e (can be any edge on that vertex)
		//! takes a vertex and edges on that vertex i.e a vertexEdgeList
		vertexEdgeList sortEdgesOnVertex (vertexEdgeList veList);

		//bool compareTriplets(edgeVertexTriplet t1 , edgeVertexTriplet t2) ; 

};


#endif
