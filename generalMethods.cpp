#include "structs.h"
#include "basicLoopEdgeSet.h"
#include "faceLoop.h"
#include "bodyLoop.h"
#include "generalMethods.h"
#include <math.h> 
#include <cstdlib>
#include <climits>
#include <iostream>

namespace generalMethods{

	// class adder: public binary_function<vertex3D, vertex3D, edge3D> {
	// 	public:
	//     bool operator()(vertex3D v1 , vertex3D v2 , edge3D e ) const
	//     {
	//         float vector1[] = {v1.a-v2.a,v1.b-v2.b,v1.c-v2.c} ;
	// 		float vector2[] = {e.v1.a-e.v2.a,e.v1.b-e.v2.b,e.v1.c-e.v2.c} ;
	// 		float scalarProduct = dotProduct(vector1,vector2) ; 

	// 		if(scalarProduct > 0) return true ;
	// 		else return false ;
	//     }
	// };

	bool comparePairs(vertexEdgePair pair1 , vertexEdgePair pair2 ) {
		float vector1[] = {pair1.v.a-pair2.v.a,pair1.v.b-pair2.v.b,pair1.v.c-pair2.v.c} ;
		float vector2[] = {pair2.e.v1.a-pair2.e.v2.a,pair2.e.v1.b-pair2.e.v2.b,pair2.e.v1.c-pair2.e.v2.c} ;
		float scalarProduct = dotProduct(vector1,vector2) ; 

		if(scalarProduct > 0) return true ;
		else return false ;

	}

	std::vector<vertex3D> sortVertices(std::vector<vertex3D> vertices, edge3D e) {

		std::vector<vertexEdgePair> pairList; 
		for (int i = 0; i < vertices.size(); ++i)
		{
			pairList.push_back(vertices[i]) ;
		}

		std::sort(pairList.begin(),pairList.end(),comparePairs) ;

		std::vector<vertex3D> sorted;

		for (int i = 0; i < pairList.size(); ++i)
		{
			sorted.push_back(pairList[i].v) ;
		}

		return sorted ; 
	}

	void printVertex(vertex3D i){
		cout<<i.a<<" "<<i.b<<" "<<i.c ;
	}

	void printVerticesList (vector<vertex3D> v){
			/**
			* print the vertexList
			*/
			cout << "Vertices: "<< "\n";

			for (vector<vertex3D>::const_iterator i = v.begin(); i != v.end(); ++i){
				printVertex(*i);
				cout << "\n";
			}
	}

	void printEdgeList (vector<edge3D> e){
			/**
		* print the edgeList
		*/
		cout << "Edges:" << "\n";
		for (vector<edge3D>::const_iterator i = e.begin(); i != e.end(); ++i){
			cout << "{"; printVertex(i->v1); cout <<"} {"; printVertex(i->v2); cout << "}" << "\n"; 
		}
	}

	


	bool checkOverlapCollinear(edge3D e1 , edge3D e2) {

		float vector1[] = {e1.v1.a-e1.v2.a,e1.v1.b-e1.v2.b,e1.v1.c-e1.v2.c} ;
		float vector2[] = {e2.v1.a-e2.v2.a,e2.v1.b-e2.v2.b,e2.v1.c-e2.v2.c} ;
		float* crossv1v2 = crossProduct(vector1 , vector2) ;
		float magnitudeCross = magnitude(crossv1v2) ;
		bool ifColliner = (magnitudeCross < epsilon) ; 
		if (!ifColliner)
		{
			/* code */
			return false ;
		}
		else {
			float e1v1e2v1[] = {e1.v1.a-e2.v1.a,e1.v1.b-e2.v1.b,e1.v1.c-e2.v1.c} ; // check whether vertex1 of edge1 is in edge2
			float e1v1e2v2[] = {e1.v1.a-e2.v2.a,e1.v1.b-e2.v2.b,e1.v1.c-e2.v2.c} ;
			float e1v1e2 = dotProduct(e1v1e2v1,e1v1e2v2) ; 
			bool e1v1Ine2 = ( e1v1e2 < 0 );
			float e1v2e2v1[] = {e1.v2.a-e2.v1.a,e1.v2.b-e2.v1.b,e1.v2.c-e2.v1.c} ; // check whether vertex2 of edge1 is in edge2
			float e1v2e2v2[] = {e1.v2.a-e2.v2.a,e1.v2.b-e2.v2.b,e1.v2.c-e2.v2.c} ;
			float e1v2e2 = dotProduct(e1v2e2v1,e1v2e2v2) ; 
			bool e1v2Ine2 = ( e1v2e2 < 0 );
			float e2v1e1v1[] = {e2.v1.a-e1.v1.a,e2.v1.b-e1.v1.b,e2.v1.c-e1.v1.c} ; // check whether vertex1 of edge2 is in edge1
			float e2v1e1v2[] = {e2.v1.a-e1.v2.a,e2.v1.b-e1.v2.b,e2.v1.c-e1.v2.c} ;
			float e2v1e1 = dotProduct(e2v1e1v1,e2v1e1v2) ; 
			bool e2v1Ine1 = ( e2v1e1 < 0 );
			float e2v2e1v1[] = {e2.v2.a-e1.v1.a,e2.v2.b-e1.v1.b,e2.v2.c-e1.v1.c} ; // check whether vertex2 of edge2 is in edge1
			float e2v2e1v2[] = {e2.v2.a-e1.v2.a,e2.v2.b-e1.v2.b,e2.v2.c-e1.v2.c} ;
			float e2v2e1 = dotProduct(e2v2e1v1,e2v2e1v2) ; 
			bool e2v2Ine1 = ( e2v2e1 < 0 ) ;
			
			return e1v1Ine2 || e1v2Ine2 || e2v1Ine1 || e2v2Ine1 ;

		}

	}


	bool checkCoplanar(edge3D e1 , edge3D e2 , edge3D e3) {

		float vector1[] = {e1.v1.a-e1.v2.a,e1.v1.b-e1.v2.b,e1.v1.c-e1.v2.c} ;
		float vector2[] = {e2.v1.a-e2.v2.a,e2.v1.b-e2.v2.b,e2.v1.c-e2.v2.c} ;
		float vector3[] = {e3.v1.a-e3.v2.a,e3.v1.b-e3.v2.b,e3.v1.c-e3.v2.c} ;
		float* crossv1v2 = crossProduct(vector1 , vector2) ; 
		float* crossv1v3 = crossProduct(vector1 , vector3) ; 
		float* crossNormals = crossProduct(crossv1v2 , crossv1v3) ; 
		float magnitudeCross = magnitude(crossNormals) ; 
		return (magnitudeCross < epsilon) ;
	}

	plane makePlane (edge3D e1 , edge3D e2){

		float vector1[] = {e1.v1.a-e1.v2.a,e1.v1.b-e1.v2.b,e1.v1.c-e1.v2.c} ;
		float vector2[] = {e2.v1.a-e2.v2.a,e2.v1.b-e2.v2.b,e2.v1.c-e2.v2.c} ;
		float* normal = crossProduct(vector1,vector2) ; 
		float maxCoeffp = std::max((std::abs(normal[0])),(std::abs(normal[1]))) ; 
		float maxCoeff = std::max(maxCoeffp,(std::abs(normal[2]))) ;
		float coefficients[] = {normal[0]/maxCoeff , normal[1]/maxCoeff , normal[2]/maxCoeff} ; 
		float intercept = coefficients[0]*(e1.v1.a) + coefficients[1]*(e1.v1.b) + coefficients[2]*(e1.v1.c) ;
		plane thePlane = {coefficients[0],coefficients[1],coefficients[2],intercept} ;  
		return thePlane ; 
	}

	bool planeEqual(plane p1 , plane p2) {
		float distancePl = findDistanceBetweenPlanes(p1,p2) ; 
		return distancePl < epsilon ;
	}

	void printPlanes ( vector<plane> p){
		for (vector<plane>::iterator i = p.begin(); i != p.end(); ++i){
			cout<<i->a<<" "<<i->b<<" "<<i->c<<" "<<i->d<<"\n" ;
		}
	}
	void removeDuplicate(std::vector<plane> planes){

		std::unique (planes.begin(), planes.end(), planeEqual); 

	}  

	float findDistanceBetweenPlanes(plane p, plane q) {

		float vectorMag1 = sqrt(p.a*p.a+p.b*p.b+p.c*p.c) ;		
		float vectorMag2 = sqrt(q.a*q.a+q.b*q.b+q.c*q.c) ;
		float d1 = p.d/vectorMag1 ;		
		float d2 = q.d/vectorMag2 ;		
		return abs(d1-d2) ; 
	}

	bool ifVertexOnPlane(plane p, vertex3D v) {
		float magnitudeP = sqrt(p.a*p.a+p.b*p.b+p.c*p.c) ;
		float d = ( p.a*v.a+p.b*v.b + p.c*v.c - p.d ) / magnitudeP ;
		return d< epsilon;
	}

	bool ifEdgeOnPlane(plane p, edge3D e) {
		bool checkV1 = ifVertexOnPlane(p,e.v1) ;
		bool checkV2 = ifVertexOnPlane(p,e.v2) ;
		return checkV1 && checkV2 ;
	}

	std::vector<edge3D> findEdgesOnPlane(plane p, std::vector<edge3D> eList) {

		std::vector<edge3D> edgeList;
		edge3D currentEdge ; 
		for (int i = 0; i < eList.size(); i++)
		{
			currentEdge = eList[i] ; 
			if(!(generalMethods::ifEdgeOnPlane(p, currentEdge))) edgeList.push_back(currentEdge) ;
		}
		return edgeList ;
	}

	std::vector<vertex3D> findVerticesOnPlane(plane p, std::vector<vertex3D> eop) {

		std::vector<vertex3D> vertexList;
		vertex3D currentVertex ; 
		for (int i = 0; i < eop.size(); i++)
		{
			currentVertex = eop[i] ; 
			if(!(ifVertexOnPlane(p, currentVertex))) vertexList.push_back(currentVertex) ;
		}
		return vertexList ;
	}

	bool checkHidden(plane p, edge3D e, float direction[]) {
		float largeNumber = 100000.0f ; 
		float farAwayVector[] = {direction[0]*largeNumber , direction[1]*largeNumber , direction[2]*largeNumber  }	;
		vertex3D vertex1 =  e.v1 ; 
		vertex3D vertex2 =  e.v2 ; 
		float pv1 = vertex1.a*p.a + vertex1.b*p.b + vertex1.c*p.c - p.d ;
		float pv2 = vertex2.a*p.a + vertex2.b*p.b + vertex2.c*p.c - p.d ;
		if (pv1*pv2 < 0)
		{
			return false ;
		}

		float pln = farAwayVector[0]*p.a + farAwayVector[1]*p.b + farAwayVector[2]*p.c  - p.d ;   
		return ( pln*pv1 < 0 )  ;

	}

}