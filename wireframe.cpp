#include<vector>
#include<algorithm>
#include<iostream>
#include "wireframe.h"
#include "VertexList2D.h"
#include "EdgeList2D.h"
#include "structs.h"
#include "generalMethods.h"
#include "basicLoopEdgeSet.h"
#include "Plane.h"
#include "bodyLoop.h"
#include "faceLoop.h"
#include <string>

using namespace std;


//! data structures inside wireframe class
// vector<vertex3D> vertexList;
// vector<edge3D> edgeList;

/** convention
* top -->  (x, y, 0)
* front -> (0, y, z)
* side ->. (x, 0, z)
*/

void wireFrame::generateWireFrame(VertexList2D v_listF, VertexList2D v_listT, VertexList2D v_listS,
			EdgeList2D e_listF, EdgeList2D e_listT, EdgeList2D e_listS ){

	/**
	* choose a vertex from each projection and match its coordinates
	* with those form other views --> if thet match --> a 3D vertex is found
	*/

// generate all the 3D vertices
	// travese the front-vertices list
	for (vector<vertex2D>::const_iterator i = v_listT.vertexList.begin(); i != v_listT.vertexList.end(); ++i){
		// traverse the top-vertices list
		for (vector<vertex2D>::const_iterator j = v_listF.vertexList.begin(); j != v_listF.vertexList.end(); ++j){
			// traverse the side vertices list
			for (vector<vertex2D>::const_iterator k = v_listS.vertexList.begin(); k != v_listS.vertexList.end(); ++k){
				// == operator is overloaded in structs
				if (( i->a == k->a ) && ( i->b == j->a ) && ( j->b == k->b ) ){
					vertex3D tempVertex = {i->a, i->b, j->b};
					wireFrame::addVertex(tempVertex);
				}

			}
		}
	}

// generate all the 3D edges
	for (vector<vertex3D>::const_iterator i = vertexList.begin(); i != vertexList.end(); ++i){
		for (vector<vertex3D>::const_iterator j = vertexList.begin(); j != vertexList.end(); ++j){
			// edges between different vertices
			if (!(i == j)){
				// make 3 temp edges to check if they exist in real projections
				edge2D topTempEdge =    { { i->a, i->b } , { j->a, j->b } };
				edge2D frontTempEdge =  { { i->b, i->c } , { j->b, j->c } };
				edge2D sideTempEdge =   { { i->a, i->c } , { j->a, j->c } };

				if( e_listT.containsEdge(topTempEdge) && e_listF.containsEdge(frontTempEdge) && e_listS.containsEdge(sideTempEdge)){
					wireFrame::addEdge (*i, *j);
				}
			}
		}
	}

	planes = generatePlanes();
	generateFaceLoops();
}

void wireFrame::printVertex(vertex3D i){
	std::cout<<i.a<<" "<<i.b<<" "<<i.c ;
}

void wireFrame::printVertices(){
	/**
	* print the vertexList
	*/
	cout << "# Vertices in wireFrame: "<< "\n";

	for (vector<vertex3D>::const_iterator i = vertexList.begin(); i != vertexList.end(); ++i){
		cout << "v ";printVertex(*i);
		cout << "\n";
	}
}

string wireFrame::getVertices(){
	/**
	* print the vertexList
	*/
	string v;
	v = "# Vertices in wireFrame: \n";

	for (vector<vertex3D>::const_iterator i = vertexList.begin(); i != vertexList.end(); ++i){
		v += "v ";
		v += "" + to_string(i->a) + " " + to_string(i->b) + " " + to_string(i->c) ;
		v += "\n";
	}
	v += "\n";
	return v;
}

//std::vector<bodyLoop> bodyloops ;
//std::vector<faceLoop > bodyLoop;
//std::vector<basicLoopEdgeSet> faceloop;
//std::vector<edge3D> eList;

string wireFrame::getBody(){

	string s;

	for (int i = 0; i < bodyloops.size(); i++){
		bodyLoop bl = bodyloops.at(i);

		for (int j = 0; j < bl.bodyloop.size(); j++){

			// face loop on bodyloop
			faceLoop fl = bl.bodyloop.at(j);
			
			
		}

	}
	return s;
}

void wireFrame::printEdges(){
	/**
	* print the edgeList
	*/
	cout << "Edges in wireFrame:" << "\n";
	for (vector<edge3D>::const_iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		cout << "{"; printVertex(i->v1); cout <<"} {"; printVertex(i->v2); cout << "}" << "\n"; 
	}
}

void wireFrame::printPlanes (){
	cout<<"Planes in wireFrame: "<<"\n";
	for (vector<plane>::iterator i = planes.begin(); i != planes.end(); ++i){
		cout<<i->a<<"x + "<<i->b<<"y + "<<i->c<<"z = "<<i->d<< "\n" ;
	}
}

void wireFrame::printFaceLoops(){
	for (int i = 0; i < faceloops.size(); i++){

		cout << "FaceLoop for plane: ";
		generalMethods::printPlane(faceloops.at(i).p); cout <<"\n";

		for (int j = 0; j < faceloops.at(i).faceloop.size(); j++){
			cout << j << "--> ";
			generalMethods::printEdgeList(faceloops.at(i).faceloop.at(j).eList);
		}
	}
}

void wireFrame::addVertex(vertex3D v){
	// return true if vertex is in vertexList
	if (find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	printf("%s\n", "Vertex Already Exists in the wireframe");
	else
  		vertexList.push_back(v);
}


void wireFrame::removeVertex(vertex3D v){
	/**
	* removes a vertex to vertexList
	*/
	// return true if vertex is in vertexList
	if (find(vertexList.begin(), vertexList.end(), v) != vertexList.end() )
  	 	vertexList.erase(std::remove(vertexList.begin(), vertexList.end(), v), vertexList.end());
	else
  		printf("%s\n", "Vertex does not exist in the wireframe!");	
}


void wireFrame::addEdge(vertex3D v1, vertex3D v2){
	// return true if vertex is in vertexList
	// make a new 3D edge and check if it already exists
	edge3D tempEdge;
	tempEdge.v1 = v1; tempEdge.v2 = v2;

	wireFrame::addEdge(tempEdge);
}	


void wireFrame::addEdge(edge3D e){
	// return true if edge is in edgeList
	if (find(edgeList.begin(), edgeList.end(), e) == edgeList.end() )
		edgeList.push_back(e);
}


void wireFrame::removeEdge (edge3D e){
	/**
	* removes a edge from edgeList
	*/
	// return true if edge is in edgeList
	if (find(edgeList.begin(), edgeList.end(), e) != edgeList.end() )
  	 	edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), e), edgeList.end());
	else
  		printf("%s\n", "Edge does not exist in the wireframe!");	
}


void wireFrame::removeEdges (vector<edge3D> eList){
	/**
	* removes edges from edgeList
	*/
	// return true if edge is in edgeList

	for (vector<edge3D>::const_iterator i = eList.begin(); i != eList.end(); ++i){
		if (find(edgeList.begin(), edgeList.end(), *i) != edgeList.end() )
	  	 	edgeList.erase(std::remove(edgeList.begin(), edgeList.end(), *i), edgeList.end());
		else
	  		printf("%s\n", "Edge does not exist in the wireframe!");	
	}	
}

// takes a edgesList and edges to be removed and removes them from that edgesList
vector<edge3D> removeEdgesFromEdgeList (vector<edge3D> EdgeList, vector<edge3D> eList){
	/**
	* removes edges from EdgeList
	*/
	// return true if edge is in edgeList
	vector<edge3D> tempVector;

	for (int i = 0; i < EdgeList.size(); i++)
	{	
		if (find(eList.begin(), eList.end(), EdgeList.at(i)) == eList.end() ){
			tempVector.push_back(EdgeList.at(i));
		}

	}
	return tempVector;
}

// takes a edgeList and returns a vertexList
vector<vertex3D> getVerticesFromEdges(vector<edge3D> e){
	vector<vertex3D> tempList;

	for (vector<edge3D>::iterator i = e.begin(); i != e.end(); ++i){
		// if vector does not exist in list --> push it
		if (find(tempList.begin(), tempList.end(), i->v1) == tempList.end() ){
			tempList.push_back(i->v1);
		}
		if (find(tempList.begin(), tempList.end(), i->v2) == tempList.end() ){
			tempList.push_back(i->v2);
		}	
	}
	return tempList;
}

vector<edge3D> findAllCollinearOverlapingEdges(vector<edge3D> edgeList, vector<edge3D> E, edge3D ei){
	for (vector<edge3D>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		if(!(*i == ei)){
			for (vector<edge3D>::iterator j = E.begin(); j != E.end(); ++j){
				if( generalMethods::checkOverlapCollinear(*i, *j)){
					E.push_back(*i);
					break;
				}
			}		
		}
	}
	return E;
}

//! remove all overlapping edges and insert non-overlapping edges in place of them
void wireFrame::resolveOverlap(){

	vector<edge3D> unexaminedEdges = edgeList;

	// until there is some unexamined edge
	while(unexaminedEdges.size()!=0){
		vector<edge3D> E;
		// put a element from unexamined edges in E ==>  E <- {e{i}}  
		E.push_back(unexaminedEdges.at(0));

		E = findAllCollinearOverlapingEdges(edgeList, E, E.at(0));

		// if no edge is collinear and overlaping then mark that edge as examined
		if(E.size()==1)
		  	 unexaminedEdges.erase(remove(unexaminedEdges.begin(), unexaminedEdges.end(), E.at(0)), unexaminedEdges.end());
		else{
			removeEdges(E);
			unexaminedEdges = removeEdgesFromEdgeList(unexaminedEdges, E);
			vector<vertex3D> collinearOverlappingVertices = getVerticesFromEdges(E);
			vector<vertex3D> sortedVertices = generalMethods::sortVertices(collinearOverlappingVertices, E.at(0));
			for(vector<vertex3D>::size_type i = 0; i != sortedVertices.size()-1; i++) {
			   	addEdge({sortedVertices.at(i), sortedVertices.at(1)});
			}
		}
	}
}

// returns the number of edges shared at vertex v 
int wireFrame::numberOfEdgesAtVertex( vertex3D v){
	int count = 0;
	// loop over the edgeList
	for (vector<edge3D>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		if( i->v1 == v || i->v2 == v){
			count++;
		}
	}
	return count;
}


vertexEdgeList wireFrame::adjEdgesAtVertex (vertex3D v){
	vertexEdgeList tempList;
	tempList.v = v;

	for (vector<edge3D>::iterator i = edgeList.begin(); i != edgeList.end(); ++i){
		if( i->v1 == v || i->v2 == v){
			tempList.e.push_back(*i);
		}
	}
	return tempList;
}


// for gettind veList with edges on plane
vertexEdgeList wireFrame::adjEdgesAtVertexPlane (vertex3D v , std::vector<edge3D> edges){
	vertexEdgeList tempList;
	tempList.v = v;

	for (vector<edge3D>::iterator i = edges.begin(); i != edges.end(); ++i){
		if( i->v1 == v || i->v2 == v){
			tempList.e.push_back(*i);
		}
	}
	return tempList;
}

vector<vertexEdgeList> wireFrame::adjEdgesAtVertexList (vector<vertex3D> vList){

	vector<vertexEdgeList> tempVectorList;

	for (vector<vertex3D>::iterator i = vList.begin(); i != vList.end(); ++i){
		tempVectorList.push_back(wireFrame::adjEdgesAtVertex(*i));
	}		

	return tempVectorList;
}

vector<plane> wireFrame::generatePlanes(){

	vector<plane> tempPlanes;

	vector<vertexEdgeList> tempvertexEdgeList;

	tempvertexEdgeList = adjEdgesAtVertexList(vertexList);

	// over each vertex
	for (vector<vertexEdgeList>::iterator i = tempvertexEdgeList.begin(); i != tempvertexEdgeList.end(); ++i){
		// for evey edge pair
		for (vector<edge3D>::iterator j = i->e.begin(); j != i->e.end(); ++j){
			// for evey edge pair
			for (vector<edge3D>::iterator k = i->e.begin(); k != i->e.end(); ++k){
				// for every adjacent edge
				if(!(j == k )){
					tempPlanes.push_back(generalMethods::makePlane(*j, *k));
				}
			}
		}
	}
	return removeRedundentPlanes(tempPlanes);
}


// used in F3.3
vector<edge3D> findAdjacentEdgesAtVertexFromplaneVEL(planeVEL pvel, vertex3D vertex){
	vector<vertexEdgeList> tempvelList = pvel.velList;

	for (int i = 0; i < tempvelList.size(); i++)
	{
		if(tempvelList.at(i).v == vertex){
			return tempvelList.at(i).e;
		}
	}
	// should not happen
	cout << "Could not find adjacent edgeList for this vertex";
	return tempvelList.at(0).e; ;
}

vertex3D otherVertexOfEdge(edge3D e, vertex3D v){
	if (e.v2 == v) return e.v1;
	else if( e.v1 == v) return  e.v2;
	else{
		cout << "Vertex does not belong to this edge";
		return v;
	}
}

edge3D findNextEdge(vector<edge3D> eList, edge3D e){
	int size = eList.size();

	for (int i = 0; i < size; i++)
	{
		if(eList.at(i) == e){
			//cout << "Current Edge: ";
			//generalMethods::printEdge(eList.at(i));
			//cout << "Next Edge: ";
			//generalMethods::printEdge(eList.at((i+1)%size));
			return eList.at((i+1)%size);
		}
	}

	// should not happen
	cout << "Could not find Next edge for edge: ";
	// generalMethods::printVertex(e.v1);
	// cout << ", ";
	// generalMethods::printVertex(e.v2);
	// cout<<"\n";
	return eList.at(0);
}

// arrange the vertices in one direction -->   v1-->v2-->v3-->v4-->v1
basicLoopEdgeSet arrangeVerticesInOneDirecton(basicLoopEdgeSet bles){

	edge3D eTemp;
	vector<edge3D> tempEList;
	eTemp = {bles.eList.at(0).v2, bles.eList.at(0).v1};
	tempEList.push_back(eTemp);
	vertex3D vTemp = tempEList.at(0).v2;
	for (int i = 0; i < bles.eList.size()-1; i++)
	{
		if(bles.eList.at(i+1).v1 == vTemp){
			tempEList.push_back(bles.eList.at(i+1));
			vTemp = tempEList.at(i+1).v2;
		}
		else{
			eTemp = {bles.eList.at(i+1).v2, bles.eList.at(i+1).v1};
			tempEList.push_back(eTemp);
			vTemp = bles.eList.at(i+1).v1;
		}
	}

	basicLoopEdgeSet b;
	b.eList = tempEList;
	return b;
}

// takes a plane vertex Edge List and returns all basic loops on that plane
vector<basicLoopEdgeSet> wireFrame::generateBasicLoopsOnPlane(planeVEL pvel, vector<edge3D> edgesOnPlane){
	
	//cout << "Gererating basicLoops of plane: " ;
	//generalMethods::printPlane(pvel.p);cout <<"\n";
	// vector of all basic loops on the plane	
	vector<basicLoopEdgeSet> basicLoopVectorToBeReturned;

	// to mark which edges are still present
	vector<edge3D> tempEdgesOnPlane = edgesOnPlane;

	// starting and ending vertex of loop
	vertex3D vStart, vEnd;

	vector<edge3D> tempEdgeList;
	// until there is a remaining edge on plane do
	while(tempEdgesOnPlane.size()!=0){
		// a temp loop set to hold current loop
		basicLoopEdgeSet tempBasicLoop;
		// select a edge from edgesLeft
		edge3D tempEdge = tempEdgesOnPlane.at(0);

		vStart = tempEdge.v1;
		vEnd   = tempEdge.v2;

		tempBasicLoop.addEdge(tempEdge);


		// until vStart != vEnd go on to make the loop
		while (!( vStart == vEnd )){
			//cout << "this ---:"; generalMethods::printVertex(vStart);cout<<"\n";
			tempEdgeList = findAdjacentEdgesAtVertexFromplaneVEL(pvel, vStart);
			//generalMethods::printEdgeList(tempEdgeList);
			// find next edge at vStart adjcacent to tempEdge
			//cout << "that :"; generalMethods::printVertex(vEnd);cout <<"\n";
			//generalMethods::printEdge(tempEdge);
			tempEdge = findNextEdge(tempEdgeList, tempEdge);
			// vStart = other endPoint of edge
			vStart = otherVertexOfEdge(tempEdge, vStart);
			tempBasicLoop.addEdge(tempEdge);
			//generalMethods::printEdgeList(tempBasicLoop.eList);cout <<"\n";

		}
		//cout << "Anyone here"<<"\n";
		// add this loop to set and remove all the edges of this loop
		tempBasicLoop = arrangeVerticesInOneDirecton(tempBasicLoop);
		basicLoopVectorToBeReturned.push_back(tempBasicLoop);
		//cout << "Before: ";
		//generalMethods::printEdgeList(tempEdgesOnPlane);cout << "\n";
		tempEdgesOnPlane = removeEdgesFromEdgeList (tempEdgesOnPlane, tempBasicLoop.eList);
		//cout << "After: ";
		//generalMethods::printEdgeList(tempEdgesOnPlane);cout << "\n\n";

	}

	return basicLoopVectorToBeReturned;
}

vertexEdgeList wireFrame::sortVEList(vertexEdgeList veList , plane p) {
	std::vector<edgeVertexTriplet> triplets ;
	std::vector<edge3D> edgeList = veList.e ;
	edgeVertexTriplet currentTriplet ;
	edge3D ref = edgeList[0] ;
	
	for (int i = 0; i < edgeList.size(); i++)
	{
		currentTriplet = {veList.v , edgeList[i] , ref , p} ;
		triplets.push_back(currentTriplet) ;

	}

	std::sort(triplets.begin(),triplets.end(), compareTriplets) ; 

	std::vector<edge3D> sortedList;

	for (int i = 0; i < triplets.size(); i++)
	{
		sortedList.push_back(triplets[i].e)  ;
	}

	vertexEdgeList sortedStruct = {veList.v , sortedList}  ;
	return sortedStruct ;	
}


planeVEL wireFrame::getVEListOnPlane(plane p){

		std::vector<edge3D> edgesOnPlane = generalMethods::findEdgesOnPlane(p , edgeList);
		std::vector<vertex3D> verticesOnPlane = generalMethods::findVerticesOnPlane(p , vertexList);

		std::vector<vertexEdgeList> velList ;
		vertexEdgeList current_veList ; 
		vertexEdgeList			 currentvel ;  ;
		for (int i = 0; i < verticesOnPlane.size(); i++) 
		{
			 currentvel = adjEdgesAtVertexPlane(verticesOnPlane[i],edgesOnPlane) ;
			 currentvel = sortVEList(currentvel , p) ;
			 velList.push_back(currentvel)  ;
		}

		planeVEL toReturn = {p , velList} ;
		return toReturn ; 

}

/**
* removes redundent planes 
*/
std::vector<plane> wireFrame::removeRedundentPlanes(std::vector<plane> v){

	vector<plane> tempPlanes = generalMethods::removeDuplicate(v);

	vector<plane> moreTempPlanes;
	for (int i = 0; i < tempPlanes.size(); i++)
	{
		if((generalMethods::findEdgesOnPlane (tempPlanes.at(i), edgeList)).size() > 2){
			moreTempPlanes.push_back(tempPlanes.at(i));
		}	
	}
	return moreTempPlanes;
}

// std::vector<faceLoop> getFaceLoopsContainingEdge(edge3D refEdge){
// 	std::vector<faceLoop> faceLoopsContaingEdge ;
// 	faceLoop currentFaceLoop ;
// 	std::vector<edge3D> edgesInCurrentFL;
// 	for (int i = 0; i < faceloops.size(); ++i)
// 	{
// 		currentFaceLoop = faceloops[i] ; 
// 		if (currentFaceLoop.ifFaceLoopContains(refEdge))
// 		 {
// 		 	faceLoopsContaingEdge.push_back(currentFaceLoop)  ;
// 		 } 
// 	}	
// 	return faceLoopsContaingEdge ;
// }

std::vector<int> wireFrame::getFaceLoopsContainingEdge(edge3D refEdge) {
	std::vector<int> faceLoopContainingEdge ;	
	faceLoop currentFaceLoop ;
	std::vector<edge3D> edgesInCurrentFL ;
	for (int i = 0; i < faceloops.size(); ++i)
	{
		currentFaceLoop = faceloops[i] ; 
		if (currentFaceLoop.ifFaceLoopContains(refEdge))
		 {
		 	faceLoopContainingEdge.push_back(i)  ;
		 } 
	}
	return faceLoopContainingEdge ; 
}


std::vector<pair<int , bool>> wireFrame::expandFaceLoop(faceLoop fl) {	
	edge3D currentEdge ;
	std::vector<int> faceContainingCurrentEdge;
	std::vector<edge3D> allEdgesInFaceLoop = fl.getAllEdges() ;
	std::vector<pair<int , bool >> selectedPairsList ;
	for (int i = 0; i < allEdgesInFaceLoop.size(); ++i)
	 {
	 	currentEdge = allEdgesInFaceLoop[i]  ;
	 	faceContainingCurrentEdge = wireFrame::getFaceLoopsContainingEdge(currentEdge) ;
	 	float *alphaAndDirection  = generalMethods::getAlphaAndDirection(fl , faceloops[faceContainingCurrentEdge[0]] , currentEdge) ;
	 	float minTheta = alphaAndDirection[0] ; 
	 	int minIndex = 0 ; 
	 	float minDirection = alphaAndDirection[1] ; 
	 	float currentTheta ;
	 	// float currentDirection ; 
	 	// int currnetMinIndex ; 
	 	for (int i = 1; i < faceContainingCurrentEdge.size(); ++i)
	 	{
	 		alphaAndDirection = generalMethods::getAlphaAndDirection(fl , faceloops[faceContainingCurrentEdge[i]] , currentEdge ) ;
	 		currentTheta = alphaAndDirection[0] ; 
	 		// currentDirection = alphaAndDirection[1] ; 
	 		if(currentTheta < minTheta ) {
	 			minTheta = currentTheta ; 
	 			minIndex = i ;
	 			minDirection = alphaAndDirection[1] ;  
	 		} 
	 	}
	 	pair<int , bool> selectedPair(minIndex , (minDirection > 0)) ; 
	 	selectedPairsList.push_back(selectedPair) ; 
	 }
	 return selectedPairsList ;   
}

void wireFrame::generateBodyLoops() {

	std::vector<int> positivesUsed(faceloops.size() , 0) ;
	std::vector<int> negativesUsed(faceloops.size() , 0) ;
	// std::std::vector<bool> positivesExpanded(faceloops.size(),false);
	// std::std::vector<bool> negativesExpanded(faceloops.size(),false);

	faceLoop startingLoop ; 
	int numberOfFLvisited = 0 ;
	bool somethingSelected ; 
	while(numberOfFLvisited < 2*faceloops.size()){
		bodyLoop currentBodyLoop ;
		for (int i = 0; i < faceloops.size(); ++i)
			{
			somethingSelected = false ; 
			if (positivesUsed[i] == 0)
			{
				somethingSelected = true ; 
				positivesUsed[i] = 1 ;
				startingLoop = faceloops[i] ;

			}
			else if (negativesUsed[i] == 0)
			{
				somethingSelected = true ; 
				negativesUsed[i] = 1 ; 
				faceLoop newFaceLoop ;
				newFaceLoop.faceloop = faceloops[i].faceloop ; 
				std::reverse(newFaceLoop.faceloop.begin(),newFaceLoop.faceloop.end()) ;
				newFaceLoop.normal = { -faceloops[i].normal.x , -faceloops[i].normal.y , -faceloops[i].normal.z } ;   
				startingLoop = newFaceLoop ;  

			}
			if (somethingSelected)
			{
				currentBodyLoop.addLoop(startingLoop) ;
				std::vector<pair<int , bool>> selectedLoops ;
				// std::vector<int> expandedLoops ;
				// expandedLoops.push_back(0) ; 
				faceLoop currentLoop = startingLoop ;
				int loopCount = 0 ;  
				while(true){
					selectedLoops = expandFaceLoop(currentLoop) ;
					// expandedLoops[loopCount] = 1 ; 
					pair<int , bool > currentPair ; 
					for (int i = 0; i < selectedLoops.size(); ++i)
					{	
						currentPair = selectedLoops[i] ;
						faceLoop loopToInsert = faceloops[currentPair.first] ; 
						if (!currentPair.second)
						{
							loopToInsert.normal = {-loopToInsert.normal.x , -loopToInsert.normal.y , -loopToInsert.normal.z } ; 
							std::reverse(loopToInsert.faceloop.begin() , loopToInsert.faceloop.end()) ; 
							negativesUsed[currentPair.first] = 1 ; 
						}
						else {
							positivesUsed[currentPair.first]  = 1 ; 
						}
						bool ifInserted = currentBodyLoop.addLoop(loopToInsert) ; 
						
						
					}

					loopCount += 1 ; 
					if (loopCount == currentBodyLoop.bodyloop.size())
					{
						break ; 
					}
				}
				bodyloops.push_back(currentBodyLoop) ;   
				break ;  
			}
		}
	}
}

// generate all face loops from the planes generated
void wireFrame::generateFaceLoops(){

	vector<faceLoop> faceLoops;
	planeVEL tempPlaneVEL;
	faceLoop tempFaceLoop;
	vector<basicLoopEdgeSet> tempBasicLoopEdgeSet;
	for (int i = 0; i < planes.size(); i++)
	{
		// find all the edges on a plane
		vector<edge3D> tempEdgesOnPlane = generalMethods::findEdgesOnPlane(planes.at(i), edgeList);
		// generate plane-edge-vertex list
		tempPlaneVEL = getVEListOnPlane(planes.at(i));
		// 
		tempBasicLoopEdgeSet = generateBasicLoopsOnPlane(tempPlaneVEL, tempEdgesOnPlane); 
		
		int temp = tempBasicLoopEdgeSet.size();

		int confinement[temp][temp];

		for (int j = 0; j < temp; j++ ){
			for (int k = 0; k < temp; k++){
				confinement[j][k] = generalMethods::checkConfinement(tempBasicLoopEdgeSet.at(j), tempBasicLoopEdgeSet.at(k), planes.at(i) );
			}
		}

		int flag = 0;
		for (int j = 0; j < temp; j++ ){
			vector<basicLoopEdgeSet> tempBaiscSet;
			flag = 0;
			for (int k = 0; k < temp; k++){
				if(confinement[j][k]==-1 and j!=k)
					flag = 1;
			}
			// if this loop is contained in other --> leave it --> it is useless
			if(flag == 1) continue;

			for (int k = 0; k < temp; k++){
				if(confinement[j][k]==1 || (confinement[j][k]==-1 && j==k)){
					tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(k));
				}
			}

			tempFaceLoop.faceloop = tempBaiscSet;
			tempFaceLoop.p = planes.at(i);
			if(planes.at(i).d>= -0.01)
				tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
			else
				tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
			tempFaceLoop.arrange();
			faceLoops.push_back(tempFaceLoop);
		}

	}
	wireFrame::faceloops = faceLoops;
}

