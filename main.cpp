#include "wireframe.h"
#include "EdgeList2D.h"
#include "generalMethods.h"
#include "Plane.h"
#include "VertexList2D.h"
#include "basicLoopEdgeSet.h"
#include "bodyLoop.h"


int main(){

	VertexList2D frontProjVertex;
	vertex2D tempVertex;

	tempVertex.a = 0; tempVertex.b = 0;
	frontProjVertex.addVertex(tempVertex);

	tempVertex.a = 0; tempVertex.b = 1;
	frontProjVertex.addVertex(tempVertex);

	tempVertex.a = 1; tempVertex.b = 0;
	frontProjVertex.addVertex(tempVertex);

	tempVertex.a = 1; tempVertex.b = 1;
	frontProjVertex.addVertex(tempVertex);

	frontProjVertex.printVertices();

	return 0;
}