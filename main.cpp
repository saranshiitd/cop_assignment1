#include "structs.h"
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

	tempVertex = {0, 0};
	frontProjVertex.addVertex(tempVertex);

	tempVertex = {0, 1};
	frontProjVertex.addVertex(tempVertex);

	tempVertex = {1, 0};
	frontProjVertex.addVertex(tempVertex);

	tempVertex = {1, 1};
	frontProjVertex.addVertex(tempVertex);


	return 0;
}