#ifndef WIREFRAME_H
#define WIREFRAME_H
#include "structs.h"
using namespace std;

class WireFrame
{
public:
//	WireFrame();
//	~WireFrame();

	std::vector<vertex3D> vertexList;
	std::vector<edge3D> edgeList;
	
	// perform provedure RER as in paper
	void resolveOverlap() ;

	// sort the vertices of this wireframe with respect to the give edge (helper function for resolveOverlap)
	void sortVertice(edge3D e) ; 

	// this method to perform procedure PEVR adss given in paper
	void procedurePEVR() ;

	// check if edges overlap and collinear
	bool checkOverlapCollinear(edge3D e1, edge3D e2) ;

	// check edges collinear
	bool checkCoplanar(edge3D e1, edge3D e2 , edge3D e3) ; 

	// this method will generate all possible planes with given edges
	std::vector<plane> generatePlanes() ; 

	// removes duplicate planes
	std::vector<plane> removeDuplicate(std::vector<plane> v;);

	// 

};


#endif