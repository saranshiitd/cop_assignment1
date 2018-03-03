#ifndef GENERALMETHODS_H
#define GENERALMETHODS_H
#include "structs.h"

namespace generalMethods{
		//-----------------methods of vertices--------------------------

	// sort the vertices along a given edge
	std::vector<vertex2D> sortVertices(std::vector<vertex2D> V, edge2D e);



	//-----------------methods of edges-----------------------------
	// check if edges overlap and collinear
	bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

	// check whether two edges coplanar
	bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ;
		


	//-----------------methods of planes----------------------------

	// make a plane using two adjacent edges
	plane makePlane (edge3D e1, edge3D e2);
	// use this to make all possible planes and then remove the duplicate ones

	// returns distance between two planes
	float findDistanceBetweenPlanes (plane p, plane q);

	// returns distance between a edge and a plane
	float findDistanceOfEdgeFromPlane (plane p, edge3D e);

	// takes a plane and e_list and returns the list of edges on that plane
	edgesOnPlane findEdgesOnPlane (plane p, std::vector<edge3D> eList);

	// takes a plane all edges on a plane (found using findEdgesOnPlane) 
	// and returns all the vertices on that plane 
	std::vector<vertex3D> findVerticesOnPlane (plane p, edgesOnPlane eop);	

	// check if edges overlap and collinear
	bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

	// check edges collinear
	bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ;

	// check if plane hides an edge from direction
	bool checkHidden(plane p , edge3D e , edge3D direction) ; // still trying to formulate the probelem
	// HOW TO CHECK HIDDEN :
	// first check both end points of edge lie on same side of plane substitute the take product and multiply result should be greater than 0
	// take an obnoxiously large coordinate in the direction you want to see like if you are observing from +y direction put (0,INF,0) where INF is large number
	// take a point and return if substitution product less than 0


}

#endif