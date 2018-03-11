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
		void addEdge (vertex2D v1, vertex2D v2);
		
		//! remove a edge from a edgeList 
		void removeEdge (edge2D e);

		bool containsEdge (edge2D e);

};

#endif