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

//************************* 3rd example ************************//
// hollow cube
	VertexList2D frontProjVertex;
	vertex2D tempVertex2D1;
	vertex2D tempVertex2D2;
	vertex2D tempVertex2D3;
	vertex2D tempVertex2D4;
	vertex2D tempVertex2D5;
	vertex2D tempVertex2D6;
	vertex2D tempVertex2D7;
	vertex2D tempVertex2D8;

	tempVertex2D1.a = 0; tempVertex2D1.b = 0; // 0,0
	frontProjVertex.addVertex(tempVertex2D1);

	tempVertex2D2.a = 0; tempVertex2D2.b = 1; // 0,1
	frontProjVertex.addVertex(tempVertex2D2);

	tempVertex2D3.a = 1; tempVertex2D3.b = 0; // 1,0
	frontProjVertex.addVertex(tempVertex2D3);

	tempVertex2D4.a = 1; tempVertex2D4.b = 1; // 1,1
	frontProjVertex.addVertex(tempVertex2D4);

	tempVertex2D5.a = 0.25; tempVertex2D5.b = 0; // 0.25,0
	frontProjVertex.addVertex(tempVertex2D5);

	tempVertex2D6.a = 0.75; tempVertex2D6.b = 0; // 0.75,0
	frontProjVertex.addVertex(tempVertex2D6);

	tempVertex2D7.a = 0.25; tempVertex2D7.b = 1; // 0.25,1
	frontProjVertex.addVertex(tempVertex2D7);

	tempVertex2D8.a = 0.75; tempVertex2D8.b = 1; // 0.75,1
	frontProjVertex.addVertex(tempVertex2D8);

	EdgeList2D frontProjEdges;
	frontProjEdges.addEdge (tempVertex2D1, tempVertex2D2);
	frontProjEdges.addEdge (tempVertex2D1, tempVertex2D3);
	frontProjEdges.addEdge (tempVertex2D3, tempVertex2D4);
	frontProjEdges.addEdge (tempVertex2D2, tempVertex2D4);

	frontProjEdges.addEdge (tempVertex2D1, tempVertex2D5);
	frontProjEdges.addEdge (tempVertex2D5, tempVertex2D6);
	frontProjEdges.addEdge (tempVertex2D6, tempVertex2D3);
	frontProjEdges.addEdge (tempVertex2D2, tempVertex2D7);
	frontProjEdges.addEdge (tempVertex2D7, tempVertex2D8);
	frontProjEdges.addEdge (tempVertex2D8, tempVertex2D4);

	frontProjEdges.addEdge (tempVertex2D7, tempVertex2D5);
	frontProjEdges.addEdge (tempVertex2D8, tempVertex2D6);

/****************/
	VertexList2D topProjVertex;
	tempVertex2D1.a = 0; tempVertex2D1.b = 0; // 0,0
	topProjVertex.addVertex(tempVertex2D1);

	tempVertex2D2.a = 0; tempVertex2D2.b = 1; // 0,1
	topProjVertex.addVertex(tempVertex2D2);

	tempVertex2D3.a = 1; tempVertex2D3.b = 0; // 1,0
	topProjVertex.addVertex(tempVertex2D3);

	tempVertex2D4.a = 1; tempVertex2D4.b = 1; // 1,1
	topProjVertex.addVertex(tempVertex2D4);

	tempVertex2D5.a = 0.25; tempVertex2D5.b = 0.25; // 0.25,0.25
	topProjVertex.addVertex(tempVertex2D5);

	tempVertex2D6.a = 0.75; tempVertex2D6.b = 0.25; // 0.75,0.25
	topProjVertex.addVertex(tempVertex2D6);

	tempVertex2D7.a = 0.25; tempVertex2D7.b = 0.75; // 0.25,0.75
	topProjVertex.addVertex(tempVertex2D7);

	tempVertex2D8.a = 0.75; tempVertex2D8.b = 0.75; // 0.75,0.75
	topProjVertex.addVertex(tempVertex2D8);

	EdgeList2D topProjEdges;
	topProjEdges.addEdge (tempVertex2D1, tempVertex2D2);
	topProjEdges.addEdge (tempVertex2D2, tempVertex2D4);
	topProjEdges.addEdge (tempVertex2D1, tempVertex2D3);
	topProjEdges.addEdge (tempVertex2D3, tempVertex2D4);

	topProjEdges.addEdge (tempVertex2D5, tempVertex2D6);
	topProjEdges.addEdge (tempVertex2D5, tempVertex2D7);
	topProjEdges.addEdge (tempVertex2D6, tempVertex2D8);
	topProjEdges.addEdge (tempVertex2D7, tempVertex2D8);

/****************/
	VertexList2D sideProjVertex;
	tempVertex2D1.a = 0; tempVertex2D1.b = 0; // 0,0
	sideProjVertex.addVertex(tempVertex2D1);

	tempVertex2D2.a = 0; tempVertex2D2.b = 1; // 0,1
	sideProjVertex.addVertex(tempVertex2D2);

	tempVertex2D3.a = 1; tempVertex2D3.b = 0; // 1,0
	sideProjVertex.addVertex(tempVertex2D3);

	tempVertex2D4.a = 1; tempVertex2D4.b = 1; // 1,1
	sideProjVertex.addVertex(tempVertex2D4);

	tempVertex2D5.a = 0.25; tempVertex2D5.b = 0; // 0.25,0
	sideProjVertex.addVertex(tempVertex2D5);

	tempVertex2D6.a = 0.75; tempVertex2D6.b = 0; // 0.75,0
	sideProjVertex.addVertex(tempVertex2D6);

	tempVertex2D7.a = 0.25; tempVertex2D7.b = 1; // 0.25,1
	sideProjVertex.addVertex(tempVertex2D7);

	tempVertex2D8.a = 0.75; tempVertex2D8.b = 1; // 0.75,1
	sideProjVertex.addVertex(tempVertex2D8);

	EdgeList2D sideProjEdges;
	sideProjEdges.addEdge (tempVertex2D1, tempVertex2D2);
	sideProjEdges.addEdge (tempVertex2D3, tempVertex2D4);
	sideProjEdges.addEdge (tempVertex2D1, tempVertex2D3);
	sideProjEdges.addEdge (tempVertex2D2, tempVertex2D4);

	sideProjEdges.addEdge (tempVertex2D1, tempVertex2D5);
	sideProjEdges.addEdge (tempVertex2D5, tempVertex2D6);
	sideProjEdges.addEdge (tempVertex2D6, tempVertex2D3);
	sideProjEdges.addEdge (tempVertex2D2, tempVertex2D7);
	sideProjEdges.addEdge (tempVertex2D7, tempVertex2D8);
	sideProjEdges.addEdge (tempVertex2D8, tempVertex2D4);

	sideProjEdges.addEdge (tempVertex2D7, tempVertex2D5);
	sideProjEdges.addEdge (tempVertex2D8, tempVertex2D6);
	

/****************/
	wireFrame wireframe;
	wireframe.generateWireFrame(frontProjVertex, topProjVertex, sideProjVertex, 
		frontProjEdges, topProjEdges, sideProjEdges );

	wireframe.printVertices();
	wireframe.printEdges();
	wireframe.printPlanes();
	wireframe.printFaceLoops();

/******************/
	// writing object to obj file
	ofstream myfile ("object.obj");
	string object;

	object = wireframe.getVertices();
	myfile << object;
	
	myfile.close();
/*****************/
	return 0;
}