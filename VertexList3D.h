#ifndef VERTEXLIST3D_H
#define VERTEXLIST3D_H
#include "structs.h"
using namespace std;


class VertexList3D{
	public :
		vector<vertex3D> vertexList;
		// add a new vertex to a vertex list
		void addVertex(vertex3D v);

		// remove vertex from a vertex lit
		void removeVertex   (vertex3D v);
		void removeVertices (vector<vertex3D> vList);

};

#endif