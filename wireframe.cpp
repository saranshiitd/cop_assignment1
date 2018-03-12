#include<vector>
#include<algorithm>
#include<iostream>
#include "wireframe.h"
#include "VertexList2D.h"
#include "EdgeList2D.h"
#include "structs.h"
#include "generalMethods.h"
using namespace std;

//! data structures inside wireframe class
// vector<vertex3D> vertexList;
// vector<edge3D> edgeList;

/** convention
* top -->  (x, y, 0)
* front -> (0, y, z)
* side ->. (x, 0, z)
*/

void wireFrame::generateWireFrame(VertexList2D v_listF, VertexList2D v_listT, VertexList2D v_listS,
			EdgeList2D e_listF, EdgeList2D e_listT, EdgeList2D e_listS ){

	/**
	* choose a vertex from each projection and match its coordinates
	* with those form other views --> if thet match --> a 3D vertex is found
	*/

// generate all the 3D vertices
	// travese the front-vertices list
	for (vector<vertex2D>::const_iterator i = v_listT.vertexList.begin(); i != v_listT.vertexList.end(); ++i){
		// traverse the top-vertices list
		for (vector<vertex2D>::const_iterator j = v_listF.vertexList.begin(); j != v_listF.vertexList.end(); ++j){
			// traverse the side vertices list
			for (vector<vertex2D>::const_iterator k = v_listS.vertexList.begin(); k != v_listS.vertexList.end(); ++k){
				// == operator is overloaded in structs
				if (( i->a == k->a ) && ( i->b == j->a ) && ( j->b == k->b ) ){
					vertex3D tempVertex = {i->a, i->b, j->b};
					wireFrame::addVertex(tempVertex);
				}

			}
		}
	}

// generate all the 3D edges
	for (vector<vertex3D>::const_iterator i = vertexList.begin(); i != vertexList.end(); ++i){
		for (vector<vertex3D>::const_iterator j = vertexList.begin(); j != vertexList.end(); ++j){
			// edges between different vertices
			if (!(i == j)){
				// make 3 temp edges to check if they exist in real projections
				edge2D topTempEdge =    { { i->a, i->b } , { j->a, j->b } };
				edge2D frontTempEdge =  { { i->b, i->c } , { j->b, j->c } };
				edge2D sideTempEdge =   { { i->a, i->c } , { j->a, j->c } };

				if( e_listT.containsEdge(topTempEdge) && e_listF.containsEdge(frontTempEdge) && e_listS.containsEdge(sideTempEdge)){
					wireFrame::addEdge (*i, *j);
				}
			}
		}
	}
}

void wireFrame::printVertex(vertex3D i){
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


void wireFrame::removeEdges (vector<edge3D> eList){
	/**
	* removes edges from edgeList
	*/
	// return true if edge is in edgeList

	for (vector<edge3D>::const_iterator i = eList.begin(); i != eList.end(); ++i){
		if (find(edgeList.begin(), edgeList.end(), *i) != edgeList.end() )
	  	 	edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), *i), edgeList.end());
		else
	  		printf("%s\n", "Edge does not exist in the wireframe!");	
	}	
}

// takes a edgesList and edges to be removed and removes them from that edgesList
void removeEdgesFromEdgeList (vector<edge3D> EdgeList, vector<edge3D> eList){
	/**
	* removes edges from EdgeList
	*/
	// return true if edge is in edgeList

	for (vector<edge3D>::const_iterator i = eList.begin(); i != eList.end(); ++i){
		if (find(EdgeList.begin(), EdgeList.end(), *i) != EdgeList.end() )
	  	 	EdgeList.erase(std::remove(EdgeList.begin(), EdgeList.end(), *i), EdgeList.end());
		else
	  		printf("%s\n", "Edge does not exist in the EdgeList!");	
	}	
}

// takes a edgeList and returns a vertexList
vector<vertex3D> getVerticesFromEdges(vector<edge3D> e){
	vector<vertex3D> tempList;

	for (vector<edge3D>::iterator i = e.begin(); i != e.end(); ++i){
		// if vector does not exist in list --> push it
		if (find(tempList.begin(), tempList.end(), i->v1) == tempList.end() ){
			tempList.push_back(i->v1);
		}
		if (find(tempList.begin(), tempList.end(), i->v2) == tempList.end() ){
			tempList.push_back(i->v2);
		}	
	}
	return tempList;
}

vector<edge3D> findAllCollinearOverlapingEdges(vector<edge3D> edgeList, vector<edge3D> E, edge3D ei){
	for (vector<edge3D>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		if(!(*i == ei)){
			for (vector<edge3D>::iterator j = E.begin(); j != E.end(); ++j){
				if( generalMethods::checkOverlapCollinear(*i, *j)){
					E.push_back(*i);
					break;
				}
			}		
		}
	}
	return E;
}

//! remove all overlapping edges and insert non-overlapping edges in place of them
void wireFrame::resolveOverlap(){

	vector<edge3D> unexaminedEdges = edgeList;

	// until there is some unexamined edge
	while(unexaminedEdges.size()!=0){
		vector<edge3D> E;
		// put a element from unexamined edges in E ==>  E <- {e{i}}  
		E.push_back(unexaminedEdges.at(0));

		E = findAllCollinearOverlapingEdges(edgeList, E, E.at(0));

		// if no edge is collinear and overlaping then mark that edge as examined
		if(E.size()==1)
		  	 unexaminedEdges.erase(remove(unexaminedEdges.begin(), unexaminedEdges.end(), E.at(0)), unexaminedEdges.end());
		else{
			removeEdges(E);
			removeEdgesFromEdgeList(unexaminedEdges, E);
			vector<vertex3D> collinearOverlappingVertices = getVerticesFromEdges(E);
			vector<vertex3D> sortedVertices = generalMethods::sortVertices(collinearOverlappingVertices, E.at(0));
			for(vector<vertex3D>::size_type i = 0; i != sortedVertices.size()-1; i++) {
			   	addEdge({sortedVertices.at(i), sortedVertices.at(1)});
			}
		}
	}
}

// returns the number of edges shared at vertex v 
int wireFrame::numberOfEdgesAtVertex( vertex3D v){
	int count = 0;
	// loop over the edgeList
	for (vector<edge3D>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		if( i->v1 == v || i->v2 == v){
			count++;
		}
	}
	return count;
}


vertexEdgeList wireFrame::adjEdgesAtVertex (vertex3D v){
	vertexEdgeList tempList;
	tempList.v = v;

	for (vector<edge3D>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		if( i->v1 == v || i->v2 == v){
			tempList.e.push_back(*i);
		}
	}
	return tempList;
}

vector<vertexEdgeList> wireFrame::adjEdgesAtVertexList (vector<vertex3D> vList){

	vector<vertexEdgeList> tempVectorList;

	for (vector<vertex3D>::iterator i = vList.begin(); i != vList.end(); ++i){
		tempVectorList.push_back(wireFrame::adjEdgesAtVertex(*i));
	}		

	return tempVectorList;
}

vector<plane> wireFrame::generatePlanes(){

	vector<plane> tempPlanes;

	vector<vertexEdgeList> tempvertexEdgeList;

	tempvertexEdgeList = adjEdgesAtVertexList(vertexList);

	// over each vertex
	for (vector<vertexEdgeList>::iterator i = tempvertexEdgeList.begin(); i != tempvertexEdgeList.end(); ++i){
		// for evey edge pair
		for (vector<edge3D>::iterator j = i->e.begin(); j != i->e.end(); ++j){
			// for evey edge pair
			for (vector<edge3D>::iterator k = i->e.begin(); k != i->e.end(); ++k){
				// for every adjacent edge
				if(!(j == k )){
					tempPlanes.push_back(generalMethods::makePlane(*j, *k));
				}
			}
		}
	}
	return tempPlanes;
}

