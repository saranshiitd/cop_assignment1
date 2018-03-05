#ifndef EDGELIST2D_H
#define EDGELIST2D_H
#include "structs.h"
using namespace std;

class EdgeList2D{
	public :

		//! a edge list containing all the edges 
		vector<edge2D> edgeList;

		//! add a edge to edgeList 
		void addEdge (edge2D e);

		//! remove a edge from a edgeList 
		void removeEdge (edge2D e);

};

#endif