#include <iostream>
#include "structs.h"
#include "EdgeList2D.h"
#include <algorithm>
using namespace std ;

void EdgeList2D::addEdge(edge2D e) {

	if (std::find(edgeList.begin(),edgeList.end(),e)==edgeList.end()) {
			edgeList.push_back(e) ;
	}	
}

void EdgeList2D::addEdge (vertex2D v1, vertex2D v2){
	edge2D tempEdge = {v1, v2};
	EdgeList2D::addEdge(tempEdge);
}

void EdgeList2D::removeEdge(edge2D e) {

	if (std::find(edgeList.begin(),edgeList.end(),e)!=edgeList.end()){
		edgeList.erase(remove(edgeList.begin(),edgeList.end(),e),edgeList.end());
	}
	else cout<<"Edge does not exits" ;	

}

bool EdgeList2D::containsEdge (edge2D e){
	if (std::find(edgeList.begin(), edgeList.end(), e) != edgeList.end() )
		return true;
	else{
		// elsif they have the same projection on a plane --> there exists a edge
		if (e.v1 == e.v2)
			return true;
		else
			return false;
	}	
}



