#ifndef BODYLOOP_H
#define BODYLOOP_H

#include <vector>
#include "structs.h"


class bodyLoop{

	std::vector< pair<faceLoop, bool> > bodyLoop;

	// add loop/remove to face loop
	void addLoop(faceLoop loop, bool b);
	void removeLoop(faceLoop loop);

	// sets a loop in bodyLoop as 'expanded' or 'unexpanded'
	void setLoop (faceLoop loop, bool b);

	// does bodyLoop contain a faceLoop
	bool containsLoop (faceLoop loop);
	
};

#endif