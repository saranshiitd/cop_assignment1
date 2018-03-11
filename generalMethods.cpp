#include "structs.h"
#include "basicLoopEdgeSet.h"
#include "faceLoop.h"
#include "bodyLoop.h"

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

	
	bool compareVertices(vertex3D v1 , vertex3D v2 , edge3D e) {
		float vector1[] = {v1.a-v2.a,v1.b-v2.b,v1.c-v2.c} ;
		float vector2[] = {e.v1.a-e.v2.a,e.v1.b-e.v2.b,e.v1.c-e.v2.c} ;
		float scalarProduct = dotProduct(vector1,vector2) ; 

		if(scalarProduct > 0) return true ;
		else return false ;

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
			float e2v2e1 = dotProduct(e2v2e1v1,e1v2e2v2) ; 
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


}