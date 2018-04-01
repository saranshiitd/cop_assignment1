#ifndef WIREFRAME_H
#define WIREFRAME_H

#include <vector>
#include "structs.h"
#include "VertexList2D.h"
#include "EdgeList2D.h"
#include "basicLoopEdgeSet.h"
#include "faceLoop.h"
#include "bodyLoop.h"
#include <string>
using namespace std;
class wireFrame
{
public:


	vector<vertex3D> vertexList;
	vector<edge3D> edgeList;
	
	vector<plane> planes;
	vector<faceLoop> faceloops;
// <<<<<<< HEAD
// 	std::vector<bodyLoop> bodyloops ;
// 	std::vector<edge2D> frontView ;
// 	std::vector<edge2D> topView; 
// 	std::vector<edge2D> sideView ;
// =======
	//std::vector<bodyLoop> bodyloops ;
	bodyLoop body;

// >>>>>>> 064717889af23a512448d93bdebfb86cfa8f73f6
	//! generate wireframe form 3 vertices list --> front, top, side
	//! and from three edges list --> front, top side
	//! gernerate vertices, edges, faces and faceLoops
	void generateWireFrame(VertexList2D v_listF, VertexList2D v_listT, VertexList2D v_listS,
			EdgeList2D e_listF, EdgeList2D e_listT, EdgeList2D e_listS );

	//! print function for wireframe
	void printVertex (vertex3D i);
	void printVertices();
	string getVertices();
	string getBody();
	void printEdges();
	void printPlanes ();
	void printFaceLoops();
	/**
	* add/remove vertex and edge to wireframe 
	*/
	void addVertex(vertex3D v);
	void removeVertex(vertex3D v);


	void addEdge(vertex3D v1, vertex3D v2);
	void addEdge(edge3D e) ; 
	void removeEdge (edge3D e); 
	void removeEdges (vector<edge3D> eList);

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
	* sort the vertices of a list with respect to the give edge (helper function for resolveOverlap) 
	*/
	void sortVertices (vector<vertex3D> vList, edge3D e) ; 

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

	vertexEdgeList adjEdgesAtVertexPlane (vertex3D v , std::vector<edge3D> edges) ; 


	planeVEL getVEListOnPlane(plane p) ;
	// /**
	// * check if edges overlap and collinear 
	// */
	// bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

	// /**
	// * check edges coplanar 
	// */
	// bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ; 

	// generate face loops from the planes generated
	void generateFaceLoops();

	// takes a plane vertex Edge List and returns all basic loops on that plane
	vector<basicLoopEdgeSet> generateBasicLoopsOnPlane(planeVEL pvel, vector<edge3D> edgesOnPlane);

	void generateBodyLoops() ;
	std::vector<int> getFaceLoopsContainingEdge(edge3D refEdge, faceLoop fl);


	void reverseFaceLoops();
private:
		// sort all edges at a vertex in clockwise direction
	vertexEdgeList sortVEList(vertexEdgeList veList , plane p);

	/**
	* this method will generate all possible planes with given edges 
	*/
	vector<plane> generatePlanes() ; 

	/**
	* removes redundent planes 
	*/
	std::vector<plane> removeRedundentPlanes(std::vector<plane> v);

	std::vector<pair<int , bool>> expandFaceLoop(faceLoop fl);
	std::vector<pair<int , bool>> wireFexpandFaceLoop(faceLoop fl);

    vector<edge3D> reverseEdgeSet(vector<edge3D> bles);
};


#endif
