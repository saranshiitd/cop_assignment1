#include "structs.h"
#include "EdgeList2D.h"
using namespace std ;

void EdgeList2D::addEdge(edge2D e) {

	if (std::find(edgeList.begin(),edgeList.end(),e)==edgeList.end()) 
		{
			edgeList.push_back(e) ; 
			/* code */
		}	
}

void EdgeList2D::removeEdge(edge2D e) {

	if (std::find(edgeList.begin(),edgeList.end(),e)!=edgeList.end()){
		edgeList.erase(std::remove(edgeList.begin(),edgeList.end(),e),edgeList.end());
	}
	else std::cout<<"Edge does not exits" ;	

}




