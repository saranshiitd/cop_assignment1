#include "wireframe.h"
#include "EdgeList2D.h"
#include "generalMethods.h"
#include "Plane.h"
#include "VertexList2D.h"
#include "basicLoopEdgeSet.h"
#include "bodyLoop.h"
#include <iostream>
using namespace std;

/*
╭━━━╮╭━━━╮╭━━━╮
┃╭━╮┃┃╭━╮┃╰╮╭╮┃
┃┃╱╰╯┃┃╱┃┃╱┃┃┃┃
┃┃╱╭╮┃╰━╯┃╱┃┃┃┃
┃╰━╯┃┃╭━╮┃╭╯╰╯┃
╰━━━╯╰╯╱╰╯╰━━━╯
*/


int main(){
/////////////////////////////////////////////
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

///////////////////////////////////////////////
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

//////////////////////////////////////////////
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
/////////////////////////////////////////////

	wireFrame wireframe;
	wireframe.generateWireFrame(frontProjVertex, topProjVertex, sideProjVertex, 
		frontProjEdges, topProjEdges, sideProjEdges );

	wireframe.printVertices();
	wireframe.printEdges();

	vector<plane> tempPlanes = wireframe.generatePlanes();
	cout << "Planes initially: \n";
	cout << tempPlanes.size() << "\n";
	generalMethods::printPlanes(tempPlanes);

	cout << "Planes Finally: \n";
	tempPlanes = generalMethods::removeDuplicate(tempPlanes);
	cout << tempPlanes.size() << "\n";
	generalMethods::printPlanes(tempPlanes);

	return 0;
}