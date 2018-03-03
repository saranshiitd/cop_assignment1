#ifndef FACELOOP_H
#define FACELOOP_H

#include<vector>
#include "structs.h"

//      -------------- definition of face loop ---------------
//		a face loop is formed from
//		L{i} if L{i} does not include any loops and
//		those basic loops included by L{i} directly if any
class faceLoop{

	std::vector<basicLoopEdgeSet> faceLoop;

	// add loop to face loop
	void addLoop(basicLoopEdgeSet loop);

	void removeLoop(basicLoopEdgeSet loop);
};

#endif