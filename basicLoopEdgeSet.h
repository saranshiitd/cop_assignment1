#ifndef BASICLOOPEDGESET_H
#define BASICLOOPEDGESET_H
#include "structs.h"
#include <vector>


/**
* this class contains all the edges in a basic loop 
*/
class basicLoopEdgeSet{

	public:
	/**
	* all the edges in a basic loop 
	*/
	std::vector<edge3D> eList;

	/**
	* methods to add and remove edge from basic loop 
	*/
	void addEdge(edge3D e);
	void removeEdge(edge3D e);
	void sort() ; 
	// std::vector<edge3D> getAllEdges();
};

#endif
