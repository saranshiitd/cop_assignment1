#include <math.h>
#include <vector>
#include "structs.h"
#include "TwoDObj.h"
#define FACTOR 300 	
	TwoDObj::TwoDObj(std::vector<vertex3D> vertices, std::vector<edge3D> edgeList) {
        this->vertices = vertices ;
        this->edgeList = edgeList ;
		generateTopView() ; 
		generateSideView() ; 
		generateFrontView() ;
	} 

std::vector<std::vector<edge2D> > getViews(){
	float maxZ = -INFINITY;
	float minZ =  INFINITY; 
	float maxY = -INFINITY;
	float minY = INFINITY; 
	float maxX = -INFINITY; 
	float minX = INFINITY; 
	vertex2D currentVertex ;
	float currentcoord ; 
	for (int i = 0; i < topView.size(); ++i)
	{
		currentVertex = topView[i].v1  ;
		currentcoord = currentVertex.a ;
		if(currentcoord > maxX) maxX = currentcoord ; 
		if(currentcoord < minX) minX = currentcoord ;
	}
	for (int i = 0; i < topView.size(); ++i)
	{
		currentVertex = topView[i].v2  ;
		currentcoord = currentVertex.a ;
		if(currentcoord > maxY) maxY = currentcoord ; 
		if(currentcoord < minY) minY = currentcoord ;
	}
	for (int i = 0; i < frontView.size(); ++i)
	{
		currentVertex = frontView[i].v1  ;
		currentcoord = currentVertex.a ;
		if(currentcoord > maxZ) maxZ = currentcoord ; 
		if(currentcoord < minZ) minZ = currentcoord ;
	}
	float diffx = maxX - minX ; 
	float diffy = maxY - minY ; 
	float diffZ = maxZ - minZ ; 	
	float maxdiff = std::max(diffx , std::max(diffy,diffz)) ;
	float scale = FACTOR/maxdiff ; 
	std::vector<edge2D> dupTopView = topView ;
	std::vector<edge2D> dupFrontView = frontView ;
	std::vector<edge2D> dupSideView = sideView ;

	for (int i = 0; i < dupTopView.size(); ++i)
	{
		dupTopView[i].multiply(scale) ; 
	}

	for (int i = 0; i < dupFrontView; ++i)
	{
		dupFrontView[i].multiply(scale) ; 
		dupFrontView[i].shift(0f,700f) ; 
	}
	for (int i = 0; i < dupSideView; ++i)
	{
		dupSideView[i].multiply(scale) ; 
		dupSideView[i].shift(700f,700f)
	}

	std::vector<std::vector<edge2D> > toReturn;
	toReturn.push_back(dupTopView) ; 
	toReturn.push_back(dupFrontView) ; 
	toReturn.push_back(dupSideView) ; 
	return toReturn ; 
 
};

void TwoDObj::generateTopView() {
	edge2D current2DEdge ;
	edge3D current3DEdge ; 
	vertex2D current2Dv1 ; 
	vertex2D current2Dv2 ; 
	vertex3D current3Dv1 ; 
	vertex3D current3Dv2 ; 
	for (int i = 0; i < edgeList.size(); i++)
	{
		current3DEdge = edgeList[i] ;
		// current2DEdge = {current3DEdge.}
		current3Dv1 = current3DEdge.v1 ; 
		current3Dv2 = current3DEdge.v2 ; 
		current2Dv1 = {current3Dv1.a , current3Dv1.b} ; 
		current2Dv2 = {current3Dv2.a , current3Dv2.b} ;
		current2DEdge = {current2Dv1 , current2Dv2} ;
		if(!(current2Dv1==current2Dv2)) {
			topView.push_back(current2DEdge) ; 
		}
	}
}	 

void TwoDObj::generateFrontView() {
	edge2D current2DEdge ;
	edge3D current3DEdge ; 
	vertex2D current2Dv1 ; 
	vertex2D current2Dv2 ; 
	vertex3D current3Dv1 ; 
	vertex3D current3Dv2 ; 
	for (int i = 0; i < edgeList.size(); i++)
	{
		current3DEdge = edgeList[i] ;
		// current2DEdge = {current3DEdge.}
		current3Dv1 = current3DEdge.v1 ; 
		current3Dv2 = current3DEdge.v2 ; 
		current2Dv1 = {current3Dv1.a , current3Dv1.c} ; 
		current2Dv2 = {current3Dv2.a , current3Dv2.c} ;
		current2DEdge = {current2Dv1 , current2Dv2} ;
		if(!(current2Dv1==current2Dv2)) {
			frontView.push_back(current2DEdge) ; 
		}
	}
}
void TwoDObj::generateSideView(){
	edge2D current2DEdge ;
	edge3D current3DEdge ; 
	vertex2D current2Dv1 ; 
	vertex2D current2Dv2 ; 
	vertex3D current3Dv1 ; 
	vertex3D current3Dv2 ; 
	for (int i = 0; i < edgeList.size(); i++)
	{
		current3DEdge = edgeList[i] ;
		// current2DEdge = {current3DEdge.}
		current3Dv1 = current3DEdge.v1 ; 
		current3Dv2 = current3DEdge.v2 ; 
		current2Dv1 = {current3Dv1.b , current3Dv1.c} ; 
		current2Dv2 = {current3Dv2.b , current3Dv2.c} ;
		current2DEdge = {current2Dv1 , current2Dv2} ;
		if(!(current2Dv1==current2Dv2)) {
			sideView.push_back(current2DEdge) ; 
		}
	}
}
