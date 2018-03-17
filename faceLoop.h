#ifndef FACELOOP_H
#define FACELOOP_H

#include<vector>
#include "structs.h"
#include "basicLoopEdgeSet.h"

/**    
*  -------------- definition of face loop ---------------
*		a face loop is formed from
*		L{i} if L{i} does not include any loops and
*		those basic loops included by L{i} directly if any 
*/

basicLoopEdgeSet reversebasicLoopEdgeSet(basicLoopEdgeSet bles);

class faceLoop{

public:
	vector<basicLoopEdgeSet> faceloop;
	direction normal ;
	plane p;
	/**
	* add loop to face loop 
	*/
	void addLoop(basicLoopEdgeSet loop);

	void removeLoop(basicLoopEdgeSet loop);

	void arrange(); 
	/** 
	* will arrange all the basicLoopEdgeSet such that their direction is same as that of normal  
	*/

	bool operator==(faceLoop other) const;

	std::vector<edge3D> getAllEdges() ;

	bool ifFaceLoopContains(edge3D edge) ;

	 
	// basicLoopEdgeSet reversebasicLoopEdgeSet(basicLoopEdgeSet bles) ; 

};

#endif