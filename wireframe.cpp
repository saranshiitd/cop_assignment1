#include<vector>
#include<algorithm>
#include<iostream>
#include "wireframe.h"

using namespace std;

//! data structures inside wireframe class
// vector<vertex3D> vertexList;
// vector<edge3D> edgeList;

/** convention
* top -->  (x, y, 0)
* front -> (0, y, z)
* side ->. (x, 0, z)
*/

void wireFrame::generateWireFrame(vector<vertex2D> v_listF, vector<vertex2D> v_listT, vector<vertex2D> v_listS,
			vector<edge2D> e_listF, vector<edge2D> e_listT, vector<edge2D> e_listS ){

	/**
	* choose a vertex from each projection and match its coordinates
	* with those form other views --> if thet match --> a 3D vertex is found
	*/

// generate all the 3D vertices
	// travese the front-vertices list
	for (vector<vertex2D>::const_iterator i = v_listT.begin(); i != v_listT.end(); ++i){
		// traverse the top-vertices list
		for (vector<vertex2D>::const_iterator j = v_listF.begin(); j != v_listF.end(); ++j){
			// traverse the side vertices list
			for (vector<vertex2D>::const_iterator k = v_listS.begin(); k != v_listS.end(); ++k){
				// == operator is overloaded in structs
				if (( i->v1 == k->v1 ) && ( i->v2 == j->v2 ) && ( j->v2 == k->v2 ) ){
					vertex3D tempVertex = {i->v1, i->v2, j->v2};
					wireFrame::addVertex(tempVertex);
				}

			}
		}
	}



}

void printVertex(vertex3D i){
	std::cout<<i.a<<" "<<i.b<<" "<<i.c ;
}

void wireFrame::printVertices(){
	/**
	* print the vertexList
	*/
	cout << "Vertices in wireFrame: "<< "\n";

	for (vector<vertex3D>::const_iterator i = vertexList.begin(); i != vertexList.end(); ++i){
		printVertex(*i);
		cout << "\n";
	}
}

void wireFrame::printEdges(){
	/**
	* print the edgeList
	*/
	cout << "Edges in wireFrame:" << "\n";
	for (vector<edge3D>::const_iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		cout << "{"; printVertex(i->v1); cout <<"} {"; printVertex(i->v2); cout << "}" << "\n"; 
	}
}

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
