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


	wireFrame wireframe;
	vertex3D tempVertex1;
	vertex3D tempVertex2;
	vertex3D tempVertex3;
	vertex3D tempVertex4;
	vertex3D tempVertex5;
	vertex3D tempVertex6;
	vertex3D tempVertex7;
	vertex3D tempVertex8;

	tempVertex1.a = 0; tempVertex1.b = 0; tempVertex1.c = 0;
	wireframe.addVertex(tempVertex1);

	tempVertex2.a = 0; tempVertex2.b = 0; tempVertex2.c = 1;
	wireframe.addVertex(tempVertex2);

	tempVertex3.a = 0; tempVertex3.b = 1; tempVertex3.c = 0;
	wireframe.addVertex(tempVertex3);

	tempVertex4.a = 0; tempVertex4.b = 1; tempVertex4.c = 1;
	wireframe.addVertex(tempVertex4);

	tempVertex5.a = 1; tempVertex5.b = 0; tempVertex5.c = 0;
	wireframe.addVertex(tempVertex5);

	tempVertex6.a = 1; tempVertex6.b = 0; tempVertex6.c = 1;
	wireframe.addVertex(tempVertex6);

	tempVertex7.a = 1; tempVertex7.b = 1; tempVertex7.c = 0;
	wireframe.addVertex(tempVertex7);

	tempVertex8.a = 1; tempVertex8.b = 1; tempVertex8.c = 1;
	wireframe.addVertex(tempVertex8);

	wireframe.addEdge(tempVertex1, tempVertex2);
	wireframe.addEdge(tempVertex1, tempVertex3);
	wireframe.addEdge(tempVertex1, tempVertex5);
	wireframe.addEdge(tempVertex3, tempVertex4);
	wireframe.addEdge(tempVertex3, tempVertex7);
	wireframe.addEdge(tempVertex5, tempVertex7);
	wireframe.addEdge(tempVertex5, tempVertex6);
	wireframe.addEdge(tempVertex2, tempVertex6);
	wireframe.addEdge(tempVertex2, tempVertex4);
	wireframe.addEdge(tempVertex4, tempVertex8);
	wireframe.addEdge(tempVertex6, tempVertex8);
	wireframe.addEdge(tempVertex7, tempVertex8);


	wireframe.printVertices();
	wireframe.printEdges();
	return 0;
}