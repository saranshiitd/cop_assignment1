#include "wireframe.h"
#include "EdgeList2D.h"
#include "generalMethods.h"
#include "Plane.h"
#include "VertexList2D.h"
#include "basicLoopEdgeSet.h"
#include "bodyLoop.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
╭━━━╮╭━━━╮╭━━━╮
┃╭━╮┃┃╭━╮┃╰╮╭╮┃
┃┃╱╰╯┃┃╱┃┃╱┃┃┃┃
┃┃╱╭╮┃╰━╯┃╱┃┃┃┃
┃╰━╯┃┃╭━╮┃╭╯╰╯┃
╰━━━╯╰╯╱╰╯╰━━━╯
*/


// TODO------------------->
// make all basic Loops on a plane in the direction of plane


int main(){
	
//************************* 1st example ************************//
// cube
	VertexList2D frontProjVertex;
	vertex2D tempVertex2D1;
	vertex2D tempVertex2D2;
	vertex2D tempVertex2D3;
	vertex2D tempVertex2D4;

	tempVertex2D1.a = 0; tempVertex2D1.b = 0;
	frontProjVertex.addVertex(tempVertex2D1);

	tempVertex2D2.a = 0; tempVertex2D2.b = 1;
	frontProjVertex.addVertex(tempVertex2D2);

	tempVertex2D3.a = 1; tempVertex2D3.b = 0;
	frontProjVertex.addVertex(tempVertex2D3);

	tempVertex2D4.a = 1; tempVertex2D4.b = 1;
	frontProjVertex.addVertex(tempVertex2D4);

	EdgeList2D frontProjEdges;
	frontProjEdges.addEdge (tempVertex2D1, tempVertex2D2);
	frontProjEdges.addEdge (tempVertex2D2, tempVertex2D4);
	frontProjEdges.addEdge (tempVertex2D1, tempVertex2D3);
	frontProjEdges.addEdge (tempVertex2D3, tempVertex2D4);

/****************/
	VertexList2D topProjVertex;
	tempVertex2D1.a = 0; tempVertex2D1.b = 0;
	topProjVertex.addVertex(tempVertex2D1);

	tempVertex2D2.a = 0; tempVertex2D2.b = 1;
	topProjVertex.addVertex(tempVertex2D2);

	tempVertex2D3.a = 1; tempVertex2D3.b = 0;
	topProjVertex.addVertex(tempVertex2D3);

	tempVertex2D4.a = 1; tempVertex2D4.b = 1;
	topProjVertex.addVertex(tempVertex2D4);

	EdgeList2D topProjEdges;
	topProjEdges.addEdge (tempVertex2D1, tempVertex2D2);
	topProjEdges.addEdge (tempVertex2D2, tempVertex2D4);
	topProjEdges.addEdge (tempVertex2D1, tempVertex2D3);
	topProjEdges.addEdge (tempVertex2D3, tempVertex2D4);

/****************/
	VertexList2D sideProjVertex;
	tempVertex2D1.a = 0; tempVertex2D1.b = 0;
	sideProjVertex.addVertex(tempVertex2D1);

	tempVertex2D2.a = 0; tempVertex2D2.b = 1;
	sideProjVertex.addVertex(tempVertex2D2);

	tempVertex2D3.a = 1; tempVertex2D3.b = 0;
	sideProjVertex.addVertex(tempVertex2D3);

	tempVertex2D4.a = 1; tempVertex2D4.b = 1;
	sideProjVertex.addVertex(tempVertex2D4);

	EdgeList2D sideProjEdges;
	sideProjEdges.addEdge (tempVertex2D1, tempVertex2D2);
	sideProjEdges.addEdge (tempVertex2D2, tempVertex2D4);
	sideProjEdges.addEdge (tempVertex2D1, tempVertex2D3);
	sideProjEdges.addEdge (tempVertex2D3, tempVertex2D4);

/****************/
	wireFrame wireframe;
	wireframe.generateWireFrame(frontProjVertex, topProjVertex, sideProjVertex, 
		frontProjEdges, topProjEdges, sideProjEdges );

	wireframe.printVertices();
	wireframe.printEdges();
	wireframe.printPlanes();
	wireframe.printFaceLoops();


	wireframe.generateBodyLoops() ; 

/******************/
	// writing object to obj file
	ofstream myfile ("cube.obj");
	string vertices = wireframe.getVertices();
	myfile << vertices;

	string body = wireframe.getBody();
	myfile << body;
	

	myfile.close();
/*****************/

	return 0 ;
}