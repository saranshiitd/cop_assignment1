#include "wireframe.h"
#include "EdgeList2D.h"
#include "generalMethods.h"
#include "Plane.h"
#include "VertexList2D.h"
#include "basicLoopEdgeSet.h"
#include "bodyLoop.h"


/*
╭━━━╮╭━━━╮╭━━━╮
┃╭━╮┃┃╭━╮┃╰╮╭╮┃
┃┃╱╰╯┃┃╱┃┃╱┃┃┃┃
┃┃╱╭╮┃╰━╯┃╱┃┃┃┃
┃╰━╯┃┃╭━╮┃╭╯╰╯┃
╰━━━╯╰╯╱╰╯╰━━━╯
*/


int main(){

	VertexList2D frontProjVertex;
	vertex2D tempVertex2D;

	tempVertex2D.a = 0; tempVertex2D.b = 0;
	frontProjVertex.addVertex(tempVertex2D);

	tempVertex2D.a = 0; tempVertex2D.b = 1;
	frontProjVertex.addVertex(tempVertex2D);

	tempVertex2D.a = 1; tempVertex2D.b = 0;
	frontProjVertex.addVertex(tempVertex2D);

	tempVertex2D.a = 1; tempVertex2D.b = 1;
	frontProjVertex.addVertex(tempVertex2D);

	frontProjVertex.printVertices();
	
	return 0;
}