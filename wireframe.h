#ifndef WIREFRAME_H
#define WIREFRAME_H
#include "structs.h"
#include<vector>
using namespace std;
class wireFrame
{
public:


	vector<vertex3D> vertexList;
	vector<edge3D> edgeList;
	
	/**
	* add vertex and edge to wireframe 
	*/
	void addVertex(vertex3D v);
	void addEdge(vertex3D v1, vertex3D v2);
	void removeEdge (edge3D e); 
	/**
	* it could be just an edge 
	*/


	void removeVertex(vertex3D v);
	void addEdge(edge3D e) ; 
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
	* check edges collinear 
	*/
	bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ; 

	/**
	* this method will generate all possible planes with given edges 
	*/
	vector<plane> generatePlanes() ; 



};


#endif