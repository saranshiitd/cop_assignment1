#include<vector>
#include<algorithm>
#include<iostream>
#include "wireframe.h"

using namespace std;

//! data structures inside wireframe class
// vector<vertex3D> vertexList;
// vector<edge3D> edgeList;


void wireFrame::addVertex(vertex3D v){
	// return true if vertex is in vertexList
	if (find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	printf("%s\n", "Vertex Already Exists");
	else
  		vertexList.push_back(v);
}


void wireFrame::removeVertex(vertex3D v){
	/**
	* removes a vertex to vertexList
	*/
	// return true if vertex is in vertexList
	if (find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	vertexList.erase(std::remove(vertexList.begin(), vertexList.end(), v), vertexList.end());
	else
  		printf("%s\n", "Vertex does not exist in the wireframe!");	
}


void wireFrame::addEdge(vertex3D v1, vertex3D v2){
	// return true if vertex is in vertexList
	// make a new 3D edge and check if it already exists
	edge3D tempEdge;
	tempEdge.v1 = v1; tempEdge.v2 = v2;

	wireFrame::addEdge(tempEdge);
}	


void wireFrame::addEdge(edge3D e){
	// return true if edge is in edgeList
	if (find(edgeList.begin(), edgeList.end(), e) != edgeList.end() )
  	 	printf("%s\n", "Edge Already Exists in the wireframe");
	else
  		edgeList.push_back(e);
}


void wireFrame::removeEdge (edge3D e){
	/**
	* removes a edge from edgeList
	*/
	// return true if edge is in edgeList
	if (find(edgeList.begin(), edgeList.end(), e) != edgeList.end() )
  	 	edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), e), edgeList.end());
	else
  		printf("%s\n", "Edge does not exist in the wireframe!");	
}
