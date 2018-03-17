#ifndef GENERALMETHODS_H
#define GENERALMETHODS_H
#include "structs.h"
#include "basicLoopEdgeSet.h"
#include "faceLoop.h"
#include "bodyLoop.h"

#define INF 10000.0f

namespace generalMethods{

	//! print methods
	void printVertex(vertex3D i);
	void printVerticesList (vector<vertex3D> v);
	void printEdge (edge3D i);
	void printEdgeList (vector<edge3D> e);
	void printPlane (plane p);
	void printPlanes (vector<plane> p);
	void printVEList (vertexEdgeList veList);
	void printplaneVEL (planeVEL p);


	/**
	* -----------------methods of vertices-------------------------- 
	*/

	/**
	* sort the vertices along a given edge 
	*/
	std::vector<vertex3D> sortVertices(std::vector<vertex3D> V, edge3D e);


	/**
	* -----------------methods of edges----------------------------- 
	*/


	/**
	* check if edges overlap and collinear 
	*/
	bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

	/**
	* check whether two edges coplanar 
	*/
	bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ;
	
	/**
	*take dot procuct 
	*/
	//direction dotProduct(direction v1, direction v2) ;
	/**
	* take cross product 
	*/
	//direction crossProduct(direction v1, direction v2) ;

	/**
	* -----------------methods of planes---------------------------- 
	*/

	/**
	* make a plane using two adjacent edges 
	*/
	plane makePlane (edge3D e1, edge3D e2);
	/**
	* use this to make all possible planes and then remove the duplicate ones 
	*/


	// remove duplicate planes
	std::vector<plane> removeDuplicate(std::vector<plane> v);
	
	/**
	* returns distance between two planes 
	**/
	float findDistanceBetweenPlanes (plane p, plane q);

	/**
	* returns distance between a edge and a plane 
	*/
	bool ifEdgeOnPlane (plane p, edge3D e);

	bool ifVertexOnPlane(plane p,  vertex3D v ) ;
	/**
	* takes a plane and e_list and returns the list of edges on that plane 
	*/
	std::vector<edge3D> findEdgesOnPlane (plane p, std::vector<edge3D> eList);

	/**
	* takes a plane and all vertices and returns all the vertices on that plane 
	*/ 
	std::vector<vertex3D> findVerticesOnPlane (plane p, std::vector<vertex3D> eop);	


	/**
	* check if plane hides an edge from direction 
	*/
	bool checkHidden(plane p , edge3D e , float direction) ; /* still trying to formulate the probelem */
	/**
	* HOW TO CHECK HIDDEN : 
	* first check both end points of edge lie on same side of plane substitute the take product and multiply result should be greater than 0
	* take an obnoxiously large coordinate in the direction you want to see like if you are observing from +y direction put (0,INF,0) where INF is large number
	* take a point and return if substitution product less than 0 
	*/

	int checkConfinement(basicLoopEdgeSet fl1 , basicLoopEdgeSet fl2, plane p) ; /* returns 1 if fl1 contains fl2 -1 if vice versa and 0 otherwise */

	/**
	* returns alpha as described in paper and whether to select +Fs or -Fs 
	*/
	float *getAlphaAndDirection(faceLoop flk , faceLoop fls, edge3D referenceEdge);

	/**
	* to determine whether the bodyloop is outer or inner by the method described in paper 
	*/
	bool getIfOuter(bodyLoop b) ;

	bool onSegment(vertex3D v , edge3D edge) ; // check if edge contains v

	int orientation(vertex3D p, vertex3D q, vertex3D r , plane s );

 	bool doIntersect(vertex3D p1 , vertex3D q1 , vertex3D p2 , vertex3D q2,plane p) ;

 	bool isInside(std::vector<vertex3D> polygon, int n, vertex3D p , edge3D refEdge, plane q ) ;

 	faceLoop getReversedFaceLoop(faceLoop faceloop) ;
}

#endif