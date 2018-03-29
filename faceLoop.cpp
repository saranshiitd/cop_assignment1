#include<vector>
#include "structs.h"
#include "faceLoop.h"
#include "basicLoopEdgeSet.h"
#include "generalMethods.h"
#include <iostream>
#include <algorithm>
void faceLoop::addLoop(basicLoopEdgeSet loop){

	// if (find(faceloop.begin(), faceloop.end(), loop) != faceloop.end() )
 //  	 	printf("%s\n", "Vertex Already Exists in the wireframe");
	// else
  		faceloop.push_back(loop);
}

void faceLoop::removeLoop(basicLoopEdgeSet loop){
	for (int i = 0; i < faceloop.size(); i++)
	{
		bool flag = true;
		for (int j = 0; j < loop.eList.size(); j++)
		{	
			if(!(faceloop.at(i).eList.at(j) == loop.eList.at(j))){
				flag = false;
			}
		}
		if(flag == true){
			faceloop.erase(faceloop.begin()+i);
			return;
		}
	}
}

basicLoopEdgeSet reversebasicLoopEdgeSet(basicLoopEdgeSet bles){
	basicLoopEdgeSet temp;
	vector<edge3D> tempEdges;
	edge3D tempEdge;
	// append the vector in reverse order
	for (int i = bles.eList.size()-1; i >= 0 ; i--){
		tempEdge = { bles.eList.at(i).v2, bles.eList.at(i).v1 };
		tempEdges.push_back(tempEdge);
	}
	// form basicLoopEdgeSet and return
	temp.eList = tempEdges;
	return temp;
}

/////// arranged according to (a,b,c) irrespective of d
void faceLoop::arrange(){
	// arrange every basic loop in the direction of 
	for (int i = 0; i < faceloop.size(); i++){
		
		vertex3D m = faceloop.at(i).eList.at(0).v1;
		vertex3D n = faceloop.at(i).eList.at(0).v2;
		vertex3D o = faceloop.at(i).eList.at(1).v2;
		float e1[] = {n.a-m.a, n.b-m.b, n.c-m.c};
		float e2[] = {o.a-n.a, o.b-n.b, o.c-n .c};

		float loopDirection[] = {crossProduct(e1, e2)[0], crossProduct(e1, e2)[1], crossProduct(e1, e2)[2]};
		float normalDirection[] = {normal.x, normal.y, normal.z};
		if(dotProduct(loopDirection, normalDirection) < 0.01){
			faceloop.at(i) = reversebasicLoopEdgeSet(faceloop.at(i));
		}

	}
}



bool faceLoop::operator==(faceLoop other) const{

	if(faceloop.size() != other.faceloop.size()){
		return false;
	}	
	else if ( !( other.p == p)){
		return false;
	}
	else{
		if( faceloop.size() == 1){
			if (generalMethods::checkConfinement(faceloop.at(0) , other.faceloop.at(0), p) == 0 ){
				return false;
			}
			else{
				return true;
			} 
		}
		else if ( faceloop.size() == 2 ){
			if ((generalMethods::checkConfinement(faceloop.at(0) , other.faceloop.at(0), p) == 0) && (generalMethods::checkConfinement(faceloop.at(0) , other.faceloop.at(1), p) == 0) ){
				return false;
			}
			else if ((generalMethods::checkConfinement(faceloop.at(1) , other.faceloop.at(0), p) == 0) && (generalMethods::checkConfinement(faceloop.at(1) , other.faceloop.at(1), p) == 0) ){
				return false;
			} 
			else {
				return true;
			}
		}
		else if ( faceloop.size() == 3 ){
			if ((   generalMethods::checkConfinement(faceloop.at(0) , other.faceloop.at(0), p) == 0) 
				&& (generalMethods::checkConfinement(faceloop.at(0) , other.faceloop.at(1), p) == 0) 
				&& (generalMethods::checkConfinement(faceloop.at(0) , other.faceloop.at(2), p) == 0)){
				return false;
			}
			else if ((generalMethods::checkConfinement(faceloop.at(1) , other.faceloop.at(0), p) == 0) 
				&& (generalMethods::checkConfinement(faceloop.at(1) , other.faceloop.at(1), p) == 0) 
				&& (generalMethods::checkConfinement(faceloop.at(1) , other.faceloop.at(2), p) == 0)){
				return false;
			}
			else if ((generalMethods::checkConfinement(faceloop.at(2) , other.faceloop.at(0), p) == 0) 
				&& (generalMethods::checkConfinement(faceloop.at(2) , other.faceloop.at(1), p) == 0) 
				&& (generalMethods::checkConfinement(faceloop.at(2) , other.faceloop.at(2), p) == 0)){
				return false;
			}
			else{
				return true;
			}
		}
		else {
			std::cout << "faceLoop with more than 4 basic loops!" << "\n";
			return true;
		}
	}
}

std::vector<edge3D> faceLoop::getAllEdges(){
	std::vector<edge3D> allEdges ;
	std::vector<edge3D> edgesInCurrentLoop;
	for (int i = 0; i < faceloop.size(); ++i)
	{
		edgesInCurrentLoop = faceloop[i].eList ; 
		allEdges.insert(allEdges.end(),edgesInCurrentLoop.begin() , edgesInCurrentLoop.end()) ;
	}
	return allEdges ; 
}

bool faceLoop::ifFaceLoopContains(edge3D edge) {
	std::vector<edge3D> edgesInCurrentLoop ;
	for (int i = 0; i < faceloop.size(); ++i)
	{
		edgesInCurrentLoop = faceloop[i].eList ; 
		if(std::find(edgesInCurrentLoop.begin(), edgesInCurrentLoop.end(), edge) != edgesInCurrentLoop.end()) {
			return true  ;
		} 
	}
	return false ; 

}