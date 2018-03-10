#include "wireframe.h"
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

	//! data structures inside wireframe class
	// vector<vertex3D> vertexList;
	// vector<edge3D> edgeList;
	

	void wireFrame::addVertex(vertex3D v){
		// return true if vertex is in vertexList
		if (std::find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
	  	 	printf("%s\n", "Vertex Already Exists");
		else
	  		vertexList.push_back(v);
	}


	void wireFrame::addEdge(vertex3D v1, vertex3D v2){
		// return true if vertex is in vertexList
		// make a new 3D edge and check if it already exists
		edge3D tempEdge;
		tempEdge.v1 = v1; tempEdge.v2 = v2;

		if (std::find(edgeList.begin(), edgeList.end(), tempEdge) != edgeList.end() )
	  	 	printf("%s\n", "Edge Already Exists");
		else
	  		edgeList.push_back(tempEdge);
	}	


	
