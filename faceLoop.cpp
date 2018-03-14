#include<vector>
#include "structs.h"
#include "faceLoop.h"
#include "basicLoopEdgeSet.h"

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

void arrange(){

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