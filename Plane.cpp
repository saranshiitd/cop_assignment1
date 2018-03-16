#include "structs.h"
#include "Plane.h" 
#include <cmath>
#include "structs.h"
#include <algorithm>
using namespace std;

#define PI 3.14159265

float findAngle(edge3D refEdge, edge3D otherEdge, vertex3D refVertex,plane p) {
	float normal[] = {p.a, p.b, p.c};
	vertex3D v2ref = (refVertex==refEdge.v1) ? refEdge.v2 : refEdge.v1 ; 
	vertex3D v2other = (refVertex==otherEdge.v1) ? otherEdge.v2 : otherEdge.v1 ; 

	float referenceVector[] = {v2ref.a - refVertex.a , v2ref.b - refVertex.b , v2ref.c - refVertex.c} ;	
	float otherVector[] = {v2other.a - refVertex.a , v2other.b - refVertex.b , v2other.c - refVertex.c} ;
	float magV1 = magnitude(referenceVector) ; 
	float magV2 =  magnitude(otherVector) ; 
	float dot = dotProduct(referenceVector , otherVector) ;
	float cosTheta = dot/(magV1*magV2);
	float theta = acos(cosTheta) * 180 / PI ; 
	float* cross = crossProduct(referenceVector , otherVector) ;	
	float dotNormal = dotProduct(cross,normal) ; 

	if(dotNormal <0) {
		return -theta ; 
	}
	else {
		return theta ;
	}

}

bool compareTriplets(edgeVertexTriplet t1 , edgeVertexTriplet t2) {

	float angle1 = findAngle(t1.reference , t1.e , t1.v, t1.p) ;
	float angle2 = findAngle(t2.reference, t2.e, t2.v , t2.p ) ; 
	return (angle1 > angle2) ;	

}

vertexEdgeList Plane::sortEdgesOnVertex (vertexEdgeList veList) {
	std::vector<edgeVertexTriplet> triplets ;
	std::vector<edge3D> edgeList = veList.e ;
	edgeVertexTriplet currentTriplet ;
	edge3D ref = edgeList[0] ;
	
	for (int i = 0; i < edgeList.size(); i++)
	{
		currentTriplet = {veList.v , edgeList[i] , ref, p} ;
		triplets.push_back(currentTriplet) ;

	}

	sort(triplets.begin(),triplets.end(), compareTriplets) ; 

	std::vector<edge3D> sortedList;

	for (int i = 0; i < triplets.size(); i++)
	{
		sortedList.push_back(triplets[i].e)  ;
	}

	vertexEdgeList sortedStruct = {veList.v , sortedList}  ;
	return sortedStruct ;
}

void Plane::sortEdgesOnVertices(){
	std::vector<vertexEdgeList> newListList ;
	for (int i = 0; i < veListList.size(); i++)
	{
		newListList.push_back(sortEdgesOnVertex(veListList[i])) ;
	}

	veListList = newListList ;
}

