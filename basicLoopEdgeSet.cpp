#include "structs.h"
#include <vector>

void basicLoopEdgeSet::addEdge(edge3D e) {
	if (find(eList.begin(),eList.end(),e)==eList.end()) {
			eList.push_back(e) ;
	} 	
}

void basicLoopEdgeSet::removeEdge(edge3D e) {
	if (find(eList.begin(),eList.end(),e)!=eList.end()){
		eList.erase(remove(eList.begin(),eList.end(),e),eList.end());
	}
	else cout<<"Edge does not exits" ;
}

void basicLoopEdgeSet::sort() {
	
}