#ifndef EDGELIST3D_H
#define EDGELIST3D_H
#include "structs.h"
using namespace std;

class EdgeList3D{
	public :

		// a edge list containing all the edges
		vector<edge3D> edgeList;

		// add edge to edgeList
		void addEdge  (edge3D e);
		void addEdges (vector<edge3D> eList);

		// remove edge from a edgeList
		void removeEdge  (edge3D e);
		void removeEdges (vector<edge3D> eList);

		// returns the number of edges shared at vertex v
		int numberOfEdgesAtVertex (vertex3D v);	

		// takes a vertex and returns a struct of adjacent edges at the vertex'
		vertexEdgeList adjEdgesAtVertex (vertex3D v);

		// takes a vertexList and returns a list of 'adjacent edges at each vertex'
		vector<vertexEdgeList> adjEdgesAtVertexList (vector<vertex3D> vList);

};

#endif