#include "structs.h"
#include "Plane.h" 
using namespace std;

float Plane::findAngle(edge3D refEdge, edge3D otherEdge, vertex3D refVertex, plane p) {
	vertex3D v2ref = (refVertex==refEdge.v1) ? refEdge.v2 : refEdgev1 ; 
	vertex3D v2other = (refVertex==otherEdge.v1) ? refEdge.v2 : refEdgev1 ; 

	float referenceVector[] = {v2ref.a - refEdge.a , v2ref.b - refEdge.b , v2ref.c - refEdge.c} ;	
	float otherVector[] = {v2other.a - refEdge.a , v2other.b - refEdge.b , v2other.c - refEdge.c} ;
	float magV1 
	float dot = dotProduct(referenceVector , otherVector) ;

	float* cross = crossProduct(referenceVector , otherVector) ;



}