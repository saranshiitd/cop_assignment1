#include "structs.h"
#include "VertexList2D.h"
#include <vector>
#include <algorithm>

void VertexList2D::addVertex(vertex2D v){
	/**
	* add a vertex to vertexList
	*/
	if (std::find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	printf("%s\n", "Vertex Already Exists");
	else
  		vertexList.push_back(v);
}

void VertexList2D::removeVertex(vertex2D v){
	/**
	* removes a vertex to vertexList
	*/
	if (std::find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	vertexList.erase(std::remove(vertexList.begin(), vertexList.end(), v), vertexList.end());
	else
  		printf("%s\n", "Vertex does not exist!");	
}