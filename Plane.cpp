#include "structs.h"
#include "Plane.h" 
#include <cmath>
#include "structs.h"
using namespace std;

#define PI 3.14159265

float Plane::findAngle(edge3D refEdge, edge3D otherEdge, vertex3D refVertex, float[] normal) {
	vertex3D v2ref = (refVertex==refEdge.v1) ? refEdge.v2 : refEdgev1 ; 
	vertex3D v2other = (refVertex==otherEdge.v1) ? refEdge.v2 : refEdgev1 ; 

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