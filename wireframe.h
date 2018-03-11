#ifndef WIREFRAME_H
#define WIREFRAME_H

#include<vector>
#include "structs.h"

using namespace std;
class wireFrame
{
public:


	vector<vertex3D> vertexList;
	vector<edge3D> edgeList;
	
	//! generate wireframe form 3 vertices list --> front, top, side
	//! and from three edges list --> front, top side
	generateWireFrame(vector<vertex2D> v_listF, vector<vertex2D> v_listT, vector<vertex2D> v_listS,
			vector<edge2D> e_listF, vector<edge2D> e_listT, vector<edge2D> e_listS );

	//! print function for wireframe
	void printVertices();
	void printEdges();
	/**
	* add/remove vertex and edge to wireframe 
	*/
	void addVertex(vertex3D v);
	void removeVertex(vertex3D v);


	void addEdge(vertex3D v1, vertex3D v2);
	void addEdge(edge3D e) ; 
	void removeEdge (edge3D e); 


	/**
	* it could be just an edge 
	*/


	/**
	* apply process PEVR at the end of it 
	*/

	/**
	* perform provedure RER as in paper 
	*/
	void resolveOverlap() ;

	/**
	* sort the vertices of this wireframe with respect to the give edge (helper function for resolveOverlap) 
	*/
	void sortVertice(edge3D e) ; 

	/**
	* returns the number of edges shared at vertex v 
	*/
	int numberOfEdgesAtVertex (vertex3D v);	
	
	/**
	* takes a vertex and returns a struct of adjacent edges at the vertex' 
	*/
	vertexEdgeList adjEdgesAtVertex (vertex3D v);

	/**
	* takes a vertexList and returns a list of 'adjacent edges at each vertex' 
	*/
	vector<vertexEdgeList> adjEdgesAtVertexList (vector<vertex3D> vList);

	/**
	* this method to perform procedure PEVR adss given in paper 
	*/
	void procedurePEVR() ;

	/**
	* check if edges overlap and collinear 
	*/
	bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

	/**
	* check edges coplanar 
	*/
	bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ; 

	/**
	* this method will generate all possible planes with given edges 
	*/
	vector<plane> generatePlanes() ; 



};


#endif