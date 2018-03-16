#ifndef BODYLOOP_H
#define BODYLOOP_H

#include <vector>
#include "structs.h"
#include "faceLoop.h"

class bodyLoop{
public :
	std::vector<faceLoop > bodyloop;

	/**
	* add loop/remove to face loop 
	*/
	bool addLoop(faceLoop loop);
	void removeLoop(faceLoop loop);
	// void addMultipleLoops(std::vector<faceLoop>) ; 
	/**
	* sets a loop in bodyLoop as 'expanded' or 'unexpanded' 
	*/
	// void setLoop (faceLoop loop);

	/**
	* does bodyLoop contain a faceLoop 
	*/
	bool containsLoop (faceLoop loop);
	/**
	* returns whether bodyloop is legal 
	*/
	bool legal() ;
};

#endif