#include "structs.h"
#include "Plane.h" 
#include <cmath>
#include "structs.h"
using namespace std;

#define PI 3.14159265

float Plane::findAngle(edge3D refEdge, edge3D otherEdge, vertex3D refVertex, float[] normal) {
	vertex3D v2ref = (refVertex==refEdge.v1) ? refEdge.v2 : refEdgev1 ; 
	vertex3D v2other = (refVertex==otherEdge.v1) ? otherEdge.v2 : otherEdgev1 ; 

	float referenceVector[] = {v2ref.a - refEdge.a , v2ref.b - refEdge.b , v2ref.c - refEdge.c} ;	
	float otherVector[] = {v2other.a - refEdge.a , v2other.b - refEdge.b , v2other.c - refEdge.c} ;
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
bool Plane::compareTriplet(edgeVertexTriplet t1 , edgeVertexTriplet t2) {

	float normal[] = {p.a,p.b,p.c} ; 
	float angle1 = findAngle(t1.reference , t1.e , t1.v , normal) ;
	float angle2 = findAngle(t2.reference, t2.e, t2.v , normal ) ; 
	return (angle1 > angle2)
	

}

vertexEdgeList sortEdgesOnVertex (vertexEdgeList veList) {
	std::vector<edgeVertexTriplet> triplets ;
	std::vector<edge3D> edgeList = veList.e ;
	edgeVertexTriplet currentTriplet ;
	edge3D ref = edgeList[0] ;
	
	for (int i = 0; i < veList.size(); i++)
	{
		currentTriplet = {veList.v , edgeList[i] , ref } ;
		triplets.push_back(currentTriplet) ;

	}

	std::sort(triplets.begin(),triplets.end(),compareTriplet) ; 

	std::vector<edge3D> sortedList;

	for (int i = 0; i < triplets.size(); i++)
	{
		sortedList.push_back(triplets[i].e)  ;
	}

	vertexEdgeList sortedStruct = {veList.v , sortedList}  ;
	return sortedStruct ;
}

void Plane::sortedEdgesOnVertices(){
	std::vector<vertexEdgeList> newListList ;
	for (int i = 0; i < veListList.size(); i++)
	{
		newListList.push_back(sortEdgesOnVertex(veListList[i])) ;
	}

	veListList = newListList ;
}

