#ifndef VERTEXLIST2D_H
#define VERTEXLIST2D_H
#include "structs.h"
using namespace std;


class VertexList2D{
	public :
		vector<vertex2D> vertexList;
		/**
		* add a new vertex to a vertex list 
		*/
		void addVertex(vertex2D v);

		/**
		* remove a vertex from a vertex lit 
		*/
		void removeVertex (vertex2D v);
		
		void printVertices ();

};

#endif