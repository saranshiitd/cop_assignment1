#ifndef FACELOOP_H
#define FACELOOP_H

#include<vector>
#include "structs.h"

/*****      -------------- definition of face loop ---------------
*		a face loop is formed from
*		L{i} if L{i} does not include any loops and
*		those basic loops included by L{i} directly if any 
*****/
class faceLoop{

	std::vector<basicLoopEdgeSet> faceLoop;
	direction normal ;
	/*****
	* add loop to face loop 
	*****/
	void addLoop(basicLoopEdgeSet loop);

	void removeLoop(basicLoopEdgeSet loop);

	void arrange(); /***** 
	* will arrange all the basicLoopEdgeSet such that their direction is same as that of normal  
	*****/


};

#endif