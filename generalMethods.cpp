#include "structs.h"
#include "basicLoopEdgeSet.h"
#include "faceLoop.h"
#include "bodyLoop.h"
#include "generalMethods.h"
#include <math.h> 
#include <cstdlib>
#include <climits>
#include <iostream>
#include <cmath>
#include <algorithm>
namespace generalMethods{


#define PI 3.141592653f 	
/**
* print methods
*/
//////////////////////////////////////////////////////////////////////////////
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

	void printEdge (edge3D i){
			/**
		* print the edgeList
		*/
		cout << " {"; printVertex(i.v1); cout <<"} {"; printVertex(i.v2); cout << "}" << " || "; 
	}

	void printEdgeList (vector<edge3D> e){
			/**
		* print the edgeList
		*/
		for (vector<edge3D>::const_iterator i = e.begin(); i != e.end(); ++i){
			cout << " {"; printVertex(i->v1); cout <<"} {"; printVertex(i->v2); cout << "}" << " || "; 
		}
		cout << "\n";
	}

	void printPlane (plane i){
			cout<<i.a<<"x + "<<i.b<<"y + "<<i.c<<"z = "<<i.d<< "  " ;
	}

	void printPlanes ( vector<plane> p){
		for (vector<plane>::iterator i = p.begin(); i != p.end(); ++i){
			cout<<i->a<<"x + "<<i->b<<"y + "<<i->c<<"z = "<<i->d<< "  || " ;
		}
	}

	void printVEList (vertexEdgeList veList){
		cout << "Vertex --> ";
		printVertex(veList.v);
		cout << " || ";
		printEdgeList(veList.e);
		cout << "\n";
	}

	void printplaneVEL (planeVEL p){
		cout << "Plane Vertex Edge List for plane --> ";
		printPlane(p.p);
		cout << "\n";
		for (int i = 0; i < p.velList.size(); i++)
		{
			printVEList(p.velList.at(i));	
		}
	}
////////////////////////////////////////////////////////////////////////////

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
			pairList.push_back({vertices[i], e}) ;
		}

		sort(pairList.begin(),pairList.end(),comparePairs) ;

		std::vector<vertex3D> sorted;

		for (int i = 0; i < pairList.size(); ++i)
		{
			sorted.push_back(pairList[i].v) ;
		}

		return sorted ; 
	}
	

	bool checkOverlapCollinear(edge3D e1 , edge3D e2) {

		float vector1[] = {e1.v1.a-e1.v2.a,e1.v1.b-e1.v2.b,e1.v1.c-e1.v2.c} ;
		float vector2[] = {e2.v1.a-e2.v2.a,e2.v1.b-e2.v2.b,e2.v1.c-e2.v2.c} ;
		float* crossv1v2 = crossProduct(vector1 , vector2) ;
		float magnitudeCross = magnitude(crossv1v2) ;
		bool ifColliner = (magnitudeCross < 0.01) ; 
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
		return (magnitudeCross < 0.01) ;
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
		return (p1 == p2);
		// float distancePl = findDistanceBetweenPlanes(p1,p2) ; 
		// return distancePl < 0.01 ;
	}


	std::vector<plane> removeDuplicate(std::vector<plane> planes){
		std::vector<plane> tempPlanes;
		for (int i = 0; i < planes.size(); i++){
			// return true if plane is in tempPlanes
			if (find(tempPlanes.begin(), tempPlanes.end(), planes.at(i)) == tempPlanes.end() ){
				tempPlanes.push_back(planes.at(i));
			}
		}
		return tempPlanes;
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
		return (abs(d)< 0.01);
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
			if((generalMethods::ifEdgeOnPlane(p, currentEdge))) edgeList.push_back(currentEdge) ;
		}
		return edgeList ;
	}

	std::vector<vertex3D> findVerticesOnPlane(plane p, std::vector<vertex3D> eop) {

		std::vector<vertex3D> vertexList;
		vertex3D currentVertex ; 
		for (int i = 0; i < eop.size(); i++)
		{
			currentVertex = eop[i] ; 
			if(ifVertexOnPlane(p, currentVertex)) vertexList.push_back(currentVertex) ;
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

	bool onSegment(vertex3D v , edge3D edge){ // check if edge contains v
		vertex3D v1 = edge.v1 ;
		vertex3D v2 = edge.v2 ;
		if (v.a <= std::max(v1.a,v2.a) && v.a >= std::min(v1.a,v2.a) && v.b <= std::max(v1.b,v2.b) && v.b >= std::min(v1.b,v2.b) && v.c <= std::max(v1.c,v2.c) && v.c >= std::min(v1.c,v2.c)) return true ;
		return false ; 
	}

	// returns 0 if points collinear 
	// returns 1 if points clockwise and 2 otherwise 
	int orientation(vertex3D p, vertex3D q, vertex3D r , plane s )
	{	
		float normal[] = {s.a,s.b,s.c} ;
		float vector1[] = {r.a - q.a , r.b - q.b ,r.c - q.c} ; 
		float vector2[] = {q.a - p.a , q.b - p.b ,q.c - p.c} ;
		float* crossv1v2 = crossProduct(vector1 , vector2) ;
		float magnitudeCross = magnitude(crossv1v2) ;
		// cout<<"---------------------" ;
		// cout<< magnitudeCross << '\n' ;
		// cout<<crossv1v2[0]<<" "<<crossv1v2[1]<<" "<<crossv1v2[2]<<'\n' ;
		if(magnitudeCross < 0.01 ) return 0 ; 
	    float val = dotProduct(crossv1v2 , normal) ;
	    // cout << val << '\n' ;  // colinear
	    return (val > 0)? 1: 2 ; // clock or counterclock wise
	}


	// returns if p1q1 and p2q2 intersect
 	bool doIntersect(vertex3D p1 , vertex3D q1 , vertex3D p2 , vertex3D q2,plane p) {
		int o1 = orientation(p1, q1, p2,p);
		int o2 = orientation(p1, q1, q2,p);
		int o3 = orientation(p2, q2, p1,p);
		int o4 = orientation(p2, q2, q1,p);


		// source https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
		if(o1 != o2 && o3 != o4) return true ;
		// Special Cases
		edge3D edgep1q1 = {p1 , q1 };
		edge3D edgep2q2 = {p2 , q2 }; 		 
		// p1, q1 and p2 are colinear and p2 lies on segment p1q1
		if (o1 == 0 && onSegment(p2, edgep1q1)) return true;

		// p1, q1 and p2 are colinear and q2 lies on segment p1q1
		if (o2 == 0 && onSegment(q2, edgep1q1)) return true;

		// p2, q2 and p1 are colinear and p1 lies on segment p2q2
		if (o3 == 0 && onSegment( p1  , edgep2q2)) return true;

		 // p2, q2 and q1 are colinear and q1 lies on segment p2q2
		if (o4 == 0 && onSegment(q1 , edgep2q2)) return true;

		return false; // Doesn't fall in any of the above cases
 	}

 	
 	bool isInside(std::vector<vertex3D> polygon, int n, vertex3D p , edge3D refEdge, plane q )
	{

		//cout<<"checking_vertex"<<'\n' ;
		//printVertex(p);
		//cout<<'\n' ;
	// There must be at least 3 vertices in polygon[]
		if (n < 3)  return false;
		float refDirection[] = {refEdge.v1.a - refEdge.v2.a , refEdge.v1.b - refEdge.v2.b , refEdge.v1.c - refEdge.v2.c } ;		// Create a point for line segment from p to infinite
		//cout<<"refDirection is here"<<refDirection[0]<<" "<<refDirection[1]<<" "<<refDirection[2]<<" "<<'\n' ;  
		
		vertex3D extreme  = {p.a + INF*refDirection[0] , p.b + INF*refDirection[1] , p.c + INF*refDirection[2]  } ;
		//cout<<"extreme is here"<<extreme.a<<" "<<extreme.b<<" "<<extreme.c<<" "<<'\n' ;  
		// Count intersections of the above line with sides of polygon
		int count = 0, i = 0;
		do
		{
		    int next = (i+1)%n;

		    // Check if the line segment from 'p' to 'extreme' intersects
		    // with the line segment from 'polygon[i]' to 'polygon[next]'
		    if (doIntersect(polygon[i], polygon[next], p, extreme,q))
		    {
		    	//cout<<"intersection here" <<  '\n' ;
		    	//printVertex(polygon[i]) ; printVertex(polygon[next]) ; printVertex(p) ; printVertex(extreme) ;
		        // If the point 'p' is colinear with line segment 'i-next',
		        // then check if it lies on segment. If it lies, return true,
		        // otherwise false
		        if (orientation(polygon[i], p, polygon[next],q) == 0)
		        {	
		        	edge3D tempEdge = {polygon[i] , polygon[next] } ;
		            return onSegment(p ,  tempEdge) ;
		        }
		        	count++;

		    }
		    i = next;
		} while (i != 0);
		//cout<<"count is here :: "<<count << '\n';
		// Return true if count is odd, false otherwise

		return count&1;  // Same as (count%2 == 1)

	}

	// assumes verices are in order 
	int checkConfinement(basicLoopEdgeSet fl1 , basicLoopEdgeSet fl2,plane p){
		std::vector<edge3D> edgesFL1 = fl1.eList;
		std::vector<edge3D> edgesFL2 = fl2.eList ;
		std::vector<vertex3D> verticesFL1 ;
		std::vector<vertex3D> verticesFL2 ;

		for (int i = 0; i < edgesFL1.size() ; ++i)
		{
			verticesFL1.push_back(edgesFL1[i].v1) ; 
		}
		
		for (int i = 0; i < edgesFL2.size() ; ++i)
		{
			verticesFL2.push_back(edgesFL2[i].v1) ; 
		}

		bool fl1InFl2  ;
		for (int i = 0; i < verticesFL1.size() ; ++i)
		{
			fl1InFl2 = isInside(verticesFL2 , verticesFL2.size() , verticesFL1[i] ,edgesFL2[0] ,  p) ; 
			if (!fl1InFl2)
			{
				break ;
			}
		}
		if (fl1InFl2)
		{
			return -1 ;
		}

		bool fl2InFl1  ;
		for (int i = 0; i < verticesFL2.size() ; ++i)
		{
			fl2InFl1 = isInside(verticesFL1 , verticesFL1.size() , verticesFL2[i] , edgesFL1[0] , p) ; 
			if (!fl2InFl1)
			{
				break ;
			}
		}

		if (fl2InFl1)
		{
			return 1 ;
		}

		return 0 ;
	}

	float *getAlphaAndDirection(faceLoop flk , faceLoop fls, edge3D referenceEdge){

		direction ns = fls.normal ; 
		direction nk = flk.normal ; 
		float *nsDirection = ns.getDirectionArray() ; 
		float *nkDirection = nk.getDirectionArray() ; 
		float magNs = magnitude(nsDirection) ; 
		float magNk = magnitude(nkDirection) ;
		float cosTheta = dotProduct(nsDirection,nkDirection);
		cosTheta = cosTheta/(magNs*magNk) ;
		float theta = acos(cosTheta) ;
		float edgeDirection[] = {referenceEdge.v2.a - referenceEdge.v1.a , referenceEdge.v2.b - referenceEdge.v1.b , referenceEdge.v2.c - referenceEdge.v1.c  } ;
		float* nsCrossnk = crossProduct(nsDirection,nkDirection) ; 
		float* directionRight = crossProduct(edgeDirection , nkDirection) ; 
		bool sameDirection = ( dotProduct(nsCrossnk , edgeDirection) > 0 );
		bool isDirectionRight = ( dotProduct(nsDirection, directionRight) > 0 ) ; 
		float *toReturn = new float[2] ;	 
		if (sameDirection && isDirectionRight)
		{
			toReturn[0] = PI - theta ; 
			toReturn[1] = 1.0f ;
			// float toReturn[] = {PI - theta , 1.0} ; 
			// return toReturn ;
		}
		else if (sameDirection && !isDirectionRight) 
		{
			toReturn[0] = 2*PI - theta  ;
			toReturn[1] =  -1.0f ; 
			
		}
		else if (!sameDirection && isDirectionRight) 
		{	
			toReturn[0] = PI + theta  ;
			toReturn[1] = 1.0f ; 
			// float toReturn[] = { , 1.0} ;
			// return toReturn ; 
		}
		else
		{
			toReturn[0] = theta  ;
			toReturn[1] =  -1.0f ; 
			// float toReturn[] = {theta , -1.0} ;
			// return toReturn ; 
		}
		return toReturn ; 
	}

// <<<<<<< HEAD
	// float *matrixMultiplication(float *matrix1 , float* matrix2){
		
	// }
	// float *matrixMultiplication(f){

	// }

// =======

	faceLoop getReversedFaceLoop(faceLoop faceloop) {
		faceLoop reversedFaceLoop ; 
		reversedFaceLoop.normal = {-faceloop.normal.x , -faceloop.normal.y , -faceloop.normal.z} ;
		reversedFaceLoop.p = {-faceloop.p.a , -faceloop.p.b , - faceloop.p.c , -faceloop.p.d} ;
		for (int i = 0; i < faceloop.faceloop.size(); i++)
		 {
			basicLoopEdgeSet  tempLoopEdgeSet ; 
		 	tempLoopEdgeSet = reversebasicLoopEdgeSet(faceloop.faceloop[i]) ;
		 	reversedFaceLoop.faceloop.push_back(tempLoopEdgeSet) ;  
		 }
		 return reversedFaceLoop ;  
		}
// >>>>>>> 064717889af23a512448d93bdebfb86cfa8f73f6
}