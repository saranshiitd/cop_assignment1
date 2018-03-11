#include "structs.h"
#include <vector>
#include <cmath> 
using namespace std;


float dotProduct(float vector1[] , float vector2[] ) {
	return vector1[0]*vector2[0] + vector1[1]*vector2[1] + vector1[2]*vector2[2] ; 
}

float *crossProduct(float vector1[] , float vector2[]) {
	float *product = new float[3] ;
	product[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1] ; 
	product[1] = vector1[2]*vector2[0] - vector1[0]*vector2[2] ; 
	product[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0] ; 
	return product ; 
}

float magnitude(float vector1[]) {
	return sqrt(vector1[0]*vector1[0] + vector1[1]*vector1[1] + vector1[2]*vector1[2]) ;  
}