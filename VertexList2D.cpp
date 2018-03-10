#include "structs.h"
#include "VertexList2D.h"
#include <vector>
#include <algorithm>

VertexList2D::addVertex(vertex2D v){
	/**
	* add a vertex to vertexList
	*/

	if (std::find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	vertexList.push_back(v);
	else
  	
}

VertexList2D::addVertex(vertex2D v){
	/**
	* add a vertex to vertexList
	*/
	VertexList2D::vertexList.push_back(v)	
}