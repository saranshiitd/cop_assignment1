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

	//procedurePEVR();
	planes = generatePlanes();
	generateFaceLoops();
}

void wireFrame::reverseFaceLoops(){
	for (int i = 0; i < faceloops.size(); i++){
		faceLoop fl = faceloops.at(i);
		faceloops.at(i) = generalMethods::getReversedFaceLoop(faceloops.at(i));
	}
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

vector<edge3D> reverseEdgeSet(vector<edge3D> bles){
	vector<edge3D> tempEdges;
	edge3D tempEdge;
	// append the vector in reverse order
	for (int i = bles.size()-1; i >= 0 ; i--){
		tempEdge = { bles.at(i).v2, bles.at(i).v1 };
		tempEdges.push_back(tempEdge);
	}
	// form basicLoopEdgeSet and return
	return tempEdges;
}

string getAFace(vector<edge3D> eList, vector<vertex3D> vList){
	string s;
	vector<vertex3D>::iterator it;
	s += "f ";
	for (int i = 0; i < eList.size(); i++){
		it = find(vList.begin(), vList.end(), eList.at(i).v1);
		int pos = distance(vList.begin(), it) + 1;

		s+= to_string(pos);
		s+= " ";
	}	
	return s;
}

string wireFrame::getBody(){

	string s;
//	for (int i = 0; i < bodyloops.size(); i++){
//			s+= "# bodyLoop No. ";
//			s+= to_string(i);
//			s+= "\n";
		bodyLoop bl = body;
		cout << bl.bodyloop.size();
		for (int j = 0; j < bl.bodyloop.size(); j++){
			// face loop on bodyloop
			faceLoop fl = bl.bodyloop.at(j);
			for (int k = 0; k < fl.faceloop.size(); k++){
				// basic Loop Edge Set on faceLoop
				basicLoopEdgeSet bles = fl.faceloop.at(k);
				int numberOfLoopsOnFaceLoop = fl.faceloop.size();
				if(numberOfLoopsOnFaceLoop == 1){
					s += getAFace(bles.eList, vertexList);
					s += "\n";
				}
				else if(numberOfLoopsOnFaceLoop == 2){
					if(k==1){
						s += getAFace(bles.eList, vertexList);
						s += "\n";
					}
					else{
						s += getAFace((bles.eList), vertexList);
						s += "\n";			
					}
				}
				else if(numberOfLoopsOnFaceLoop == 3){
					if(k==1){
						s += getAFace(bles.eList, vertexList);
						s += "\n";
					}
					else if(k==2){
						s += getAFace((bles.eList), vertexList);
						s += "\n";
					}
					else{
// 						s += getAFace(reverseEdgeSet(bles.eList), vertexList);
						s += getAFace((bles.eList), vertexList);
						s += "\n";			
					}				
				}
				else{
					cout << "4 loops on a faceLoop :(" << "\n";
				}
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

void printFaceLoop(faceLoop argFace){

	for (int j = 0; j < argFace.faceloop.size(); j++){
			cout << j << "--> ";
			generalMethods::printEdgeList(argFace.faceloop.at(j).eList);
		}

} ;

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

bool areCollinear(edge3D e1, edge3D e2){

	float vector1[] = {e1.v1.a-e1.v2.a,e1.v1.b-e1.v2.b,e1.v1.c-e1.v2.c} ;
	float vector2[] = {e2.v1.a-e2.v2.a,e2.v1.b-e2.v2.b,e2.v1.c-e2.v2.c} ;
	float* crossv1v2 = crossProduct(vector1 , vector2) ;
	float magnitudeCross = magnitude(crossv1v2) ;
	return (magnitudeCross < 0.01) ;

}

bool areNotCollinear(edge3D e1, edge3D e2, edge3D e3){
	return !(areCollinear(e1,e2) || areCollinear(e2,e3) || areCollinear(e1,e3));
}
 
bool areAllNOnCollinear(edge3D e1, edge3D e2, edge3D e3, edge3D e4){
	return !(areCollinear(e1,e2) || areCollinear(e1,e3) || areCollinear(e1,e4) || areCollinear(e2,e3) || areCollinear(e2,e4) || areCollinear(e3,e4));
}

bool twoOfThreeAreCollinear(edge3D e1, edge3D e2, edge3D e3){
	return (areCollinear(e1,e2) || areCollinear(e2,e3) || areCollinear(e1,e3));
}

bool twoPairsAreCollinear(edge3D e1, edge3D e2, edge3D e3, edge3D e4){
	return (areCollinear(e1,e2) && areCollinear(e3,e4)) || (areCollinear(e1,e3) && areCollinear(e2,e4))
			|| (areCollinear(e1,e4) && areCollinear(e2,e3));
}

bool onlyTwoareCollinear(edge3D e1, edge3D e2, edge3D e3, edge3D e4){
	bool b;
	b= (areCollinear(e1,e2) && !areCollinear(e1,e3) && !areCollinear(e1,e4));
	b = b || (areCollinear(e1,e3) && !areCollinear(e1,e2) && !areCollinear(e1,e4));
	b = b || (areCollinear(e1,e4) && !areCollinear(e1,e2) && !areCollinear(e1,e3));
	b = b || (areCollinear(e2,e3) && !areCollinear(e2,e1) && !areCollinear(e2,e4));
	b = b || (areCollinear(e2,e4) && !areCollinear(e2,e1) && !areCollinear(e1,e3));
	b = b || (areCollinear(e3,e4) && !areCollinear(e3,e1) && !areCollinear(e3,e2));

	return b;
}

bool are4Coplanar(edge3D e1, edge3D e2, edge3D e3, edge3D e4){
	return generalMethods::checkCoplanar(e1,e2,e3) && generalMethods::checkCoplanar(e1,e2,e4) ;
}

vector<edge3D> getNonCollinearEdge(edge3D e1, edge3D e2, edge3D e3){
	vector<edge3D> tempEdges;
	if(areCollinear(e1,e2)){
		tempEdges.push_back(e3);
		tempEdges.push_back(e1);
		tempEdges.push_back(e2);
	}
	else if(areCollinear(e2,e3)){
		tempEdges.push_back(e1);
		tempEdges.push_back(e2);
		tempEdges.push_back(e3);
	}
	else {
		tempEdges.push_back(e2);
		tempEdges.push_back(e1);
		tempEdges.push_back(e3);
	}
	return tempEdges;
}

vector<edge3D> getNonCollinearEdge4(edge3D e1, edge3D e2, edge3D e3, edge3D e4){
	vector<edge3D> tempEdges;
	if(areCollinear(e1,e2)){
		tempEdges.push_back(e3);
		tempEdges.push_back(e4);
		tempEdges.push_back(e1);
		tempEdges.push_back(e2);
	}
	else if(areCollinear(e1,e3)){
		tempEdges.push_back(e2);
		tempEdges.push_back(e4);
		tempEdges.push_back(e1);
		tempEdges.push_back(e3);
	}
	else if(areCollinear(e1,e4)){
		tempEdges.push_back(e2);
		tempEdges.push_back(e3);
		tempEdges.push_back(e1);
		tempEdges.push_back(e4);
	}
	else if(areCollinear(e2,e3)){
		tempEdges.push_back(e1);
		tempEdges.push_back(e4);
		tempEdges.push_back(e2);
		tempEdges.push_back(e3);
	}
	else if(areCollinear(e2,e4)){
		tempEdges.push_back(e1);
		tempEdges.push_back(e3);
		tempEdges.push_back(e2);
		tempEdges.push_back(e4);
	}
	else {
		tempEdges.push_back(e1);
		tempEdges.push_back(e2);
		tempEdges.push_back(e3);
		tempEdges.push_back(e4);
	}
	
	return tempEdges;
}



edge3D getRemovedVertexEdge(edge3D e1, edge3D e2, vertex3D v){
	edge3D anEdge;
	if(!(e1.v1 == v)){
		anEdge.v1 = e1.v1;
	}
	else{
		anEdge.v1 = e1.v2;
	}
	if(!(e2.v1 == v)){
		anEdge.v2 = e2.v1;
	}
	else{
		anEdge.v2 = e2.v2;
	}
	return anEdge;
}
void wireFrame::procedurePEVR(){

	int flag = 1;
	while(flag!=0)
	{
		flag = 0;
		for (int i = 0; i < vertexList.size(); i++)
		{
			vertexEdgeList veListatV = adjEdgesAtVertex(vertexList.at(i));
			
			if(veListatV.e.size() == 0){
				flag = 1;
				removeVertex(vertexList.at(i));
			}
			else if(veListatV.e.size() == 1){
				flag = 1;
				removeVertex(vertexList.at(i));
				removeEdge(veListatV.e.at(0));
			}
			else if(veListatV.e.size() == 2){
				flag = 1;
				if(areCollinear(veListatV.e.at(0), veListatV.e.at(1))){
					removeEdge(veListatV.e.at(0));
					removeEdge(veListatV.e.at(1));
					removeVertex(veListatV.v);
					addEdge(getRemovedVertexEdge(veListatV.e.at(0), veListatV.e.at(1), veListatV.v));
				}
				else{
					removeEdge(veListatV.e.at(0));
					removeEdge(veListatV.e.at(1));
					removeVertex(veListatV.v);					
				}
			}
			else if(veListatV.e.size() == 3){
				edge3D e1,e2,e3;
				e1= veListatV.e.at(0);
				e2= veListatV.e.at(1);
				e3= veListatV.e.at(2);
				if(generalMethods::checkCoplanar(e1, e2, e3) && areNotCollinear(e1,e2,e3)){
					flag =1;
					removeVertex(veListatV.v);
					removeEdges(veListatV.e);
				}
				else if(twoOfThreeAreCollinear(e1,e2,e3)){
					flag=1;
					vector<edge3D> tempEdges = getNonCollinearEdge(e1,e2,e3);
					removeEdge(tempEdges.at(0));
					removeVertex(veListatV.v);
					addEdge(getRemovedVertexEdge(tempEdges.at(1), tempEdges.at(2), veListatV.v));
				}
			}
			else{
				edge3D e1,e2,e3,e4;
				e1= veListatV.e.at(0);
				e2= veListatV.e.at(1);
				e3= veListatV.e.at(2);
				e4= veListatV.e.at(3);	

				if(are4Coplanar(e1,e2,e3,e4)){
					flag =1;
					if(onlyTwoareCollinear(e1,e2,e3,e4)){
						vector<edge3D> tempEdges = getNonCollinearEdge4(e1,e2,e3,e4);
						removeEdge(tempEdges.at(0));
						removeEdge(tempEdges.at(1));
						removeVertex(veListatV.v);
						addEdge(getRemovedVertexEdge(tempEdges.at(2), tempEdges.at(3), veListatV.v));						
					}
					else if(twoPairsAreCollinear(e1,e2,e3,e4) || areAllNOnCollinear(e1,e2,e3,e4)){
						removeVertex(veListatV.v);
						removeEdges(veListatV.e);
					}
				}
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

std::vector<int> wireFrame::getFaceLoopsContainingEdge(edge3D refEdge, faceLoop notInclude) {
	std::vector<int> faceLoopContainingEdge ;	
	faceLoop currentFaceLoop ;
	std::vector<edge3D> edgesInCurrentFL ;
	for (int i = 0; i < faceloops.size(); ++i)
	{
		currentFaceLoop = faceloops[i] ; 
		if (currentFaceLoop.ifFaceLoopContains(refEdge) && !(currentFaceLoop == notInclude))
		 {
		 	faceLoopContainingEdge.push_back(i)  ;
		 } 
	}
	return faceLoopContainingEdge ; 
}


std::vector<pair<int , bool>> wireFrame::expandFaceLoop(faceLoop fl) {

	edge3D currentEdge ;
	std::vector<int> faceContainingCurrentEdge ;
	std::vector<edge3D> allEdgesInFaceLoop = fl.getAllEdges() ;
	// printf("%d number of edges\n", allEdgesInFaceLoop.size()) ;
	std::vector<pair<int , bool >> selectedPairsList ;
	for (int i = 0; i < allEdgesInFaceLoop.size(); ++i)
	 {	

	 	currentEdge = allEdgesInFaceLoop[i]  ;
	 	// generalMethods::printEdge(currentEdge) ; 
	 	faceContainingCurrentEdge = wireFrame::getFaceLoopsContainingEdge(currentEdge,fl) ;
	 	float *alphaAndDirection  = generalMethods::getAlphaAndDirection(fl , faceloops[faceContainingCurrentEdge[0]] , currentEdge) ; // here assuming that there is atleast one face containing the edge other than orignal plane
		
		// printf("%f\n",alphaAndDirection[0] );
		// printf("%f\n",alphaAndDirection[1] );
		//  for (int k =0; k < (sizeof(alphaAndDirection)/sizeof(*alphaAndDirection)); k++){
     	//	printf("%f\n", alphaAndDirection[k]);	
		// } 
	 	float minTheta = alphaAndDirection[0] ;
	 	int minIndex = 0 ;
	 	float minDirection = alphaAndDirection[1] ;
	 	float currentTheta ;
	 	// float currentDirection ; 
	 	// int currnetMinIndex ; 
	 	for (int i = 1 ; i < faceContainingCurrentEdge.size(); i++)
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
	 	pair<int , bool> selectedPair(faceContainingCurrentEdge[minIndex] , (minDirection > 0)) ;
	 	selectedPairsList.push_back(selectedPair) ;
	 }
	 // printf("%s\n","return expandFaceLoop" );
	 return selectedPairsList ;
}

// return 1 if edge in same direction --> -1 if opposite 
int directionOfFaceLoop(edge3D e, faceLoop fl){

	for (int i = 0; i < fl.faceloop.size(); i++){
		basicLoopEdgeSet bs = fl.faceloop.at(i);
		vector<edge3D> el = bs.eList;

		for(int j=0; j< el.size(); j++){
			if(el.at(j) == e){
				if(el.at(j).v1 == e.v1)
					return 1;
				else
					return -1;
			}
		}	
	}
	return 1;
}

void wireFrame::generateBodyLoops() 
{

	bool isMarked[faceloops.size()];
	bool isVisited[faceloops.size()];

	for (int i = 0; i < faceloops.size(); i++){
		isMarked[i] = false;
		isVisited[i] = false;
	}

	// get the first face --> mark it visited
	faceLoop tempFaceLoop = faceloops.at(0);
	isMarked[0] = true;
	isVisited[0] =false;
	// select with the faceLoop with more number of basicLoops
	for(int i = 0; i < faceloops.size(); i++){
		if(faceloops.at(i).faceloop.size() > 1){
			// mark this face visited and 0 unvisited
			tempFaceLoop = faceloops.at(i);
			isMarked[i] = true;
			isVisited[i] = true;
			isMarked[0] = false;
			isVisited[0] = false;
			break;
		}
	}

	// ??? termination condition
	int count = 1;
	while(true)
	{
		// update tempFaceLoop------------------------
		// for every edge of that faceloop do
		for(int i = 0; i < tempFaceLoop.faceloop.size(); i++){
			basicLoopEdgeSet tempBasicLoop = tempFaceLoop.faceloop.at(i);
			for(int j = 0; j < tempBasicLoop.eList.size(); j++){
				edge3D tempEdge = tempBasicLoop.eList.at(j);

				vector<int> faceLoopsAtThisEdge = getFaceLoopsContainingEdge(tempEdge, tempFaceLoop);
				for(int k = 0; k<faceLoopsAtThisEdge.size(); k++){
					if( isMarked[faceLoopsAtThisEdge.at(k)] == false) count++ ;
					isMarked[faceLoopsAtThisEdge.at(k)] = true;
					if(directionOfFaceLoop(tempEdge, faceloops.at(faceLoopsAtThisEdge.at(k))) == 1){
						faceloops.at(faceLoopsAtThisEdge.at(k)) = generalMethods::getReversedFaceLoop(faceloops.at(faceLoopsAtThisEdge.at(k)));
					}
				}
			}
		}
		for(int i=0; i<faceloops.size();i++){
			if(faceloops.at(i) == tempFaceLoop)
				isVisited[i] = true;
		}
		if(count == faceloops.size()) break;
		for(int i=0;i<faceloops.size();i++){
			if(isMarked[i]==true && isVisited[i]==false){
				tempFaceLoop = faceloops.at(i);
				isMarked[i] = true;
				isVisited[i] = true;
				break;
			}
		}
	}
	body.bodyloop = faceloops; 
}

bool oneContainsTwo(int** confinement){
	int count = 0;
	for (int i = 0; i < 3; i++){
		count = 0;
		for (int j = 0; j < 3; j++){
			if(i!=j){
				if(*( *(confinement + i*3) + j) == 1)
					count ++;
			}
		}	
		if(count == 2) return true;		
	}
	return false;
}

bool oneContainsOne(int** confinement){
	int count = 0;
	for (int i = 0; i < 3; i++){
		count = 0;
		for (int j = 0; j < 3; j++){
			if(i!=j){
				if(*( *(confinement + i*3) + j) == 1)
					count ++;
			}
		}	
		if(count == 1) return true;		
	}
	return false;
}

bool threeLoopsOneInsideOther(int* confinement){
	if(oneContainsTwo(&confinement) && oneContainsOne(&confinement))
		return true;
	else
		return false;
}

int firstLoop(int *confinement){
	int count = 0;
	for (int i = 0; i < 3; i++){
		count = 0;
		for (int j = 0; j < 3; j++){
			if(i!=j){
				if( *( (confinement + i*3) + j) == 1)
					count ++;
			}
		}	
		if(count == 2) return i;		
	}	
	cout << "Fitst Loop not found" <<"\n";
	return 0;
}

int secondLoop(int *confinement){
	int count =0;	
	for (int i = 0; i < 3; i++){
		count = 0;
		for (int j = 0; j < 3; j++){
			if(i!=j){
				if(*( (confinement + i*3) + j) == 1)
					count ++;
			}
		}	
		if(count == 1) return i;		
	}	
	cout << "second Loop not found" <<"\n";
	return 0;
}

int thirdLoop(int* confinement){
	int count = 0;
	for (int i = 0; i < 3; i++){
		count = 0;
		for (int j = 0; j < 3; j++){
			if(i!=j){
				if(*( (confinement + i*3) + j) == 1)
					count ++;
			}
		}	
		if(count == 0) return i;		
	}	
	cout << "third Loop not found" <<"\n";
	return 0;
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
		//vector<basicLoopEdgeSet> tempBaiscSet;

		for (int j = 0; j < temp; j++ ){
			for (int k = 0; k < temp; k++)
			confinement[j][k] = generalMethods::checkConfinement(tempBasicLoopEdgeSet.at(j), tempBasicLoopEdgeSet.at(k), planes.at(i) );
		}

		if(temp == 1 ){
			int flag = 0 ;
			for (int j = 0; j < temp; j++ ){
				vector<basicLoopEdgeSet> tempBaiscSet;
				tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(0));
				// make this loop a faceloop
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
		else if(temp == 2){
			if(confinement[0][1] == 1){
				cout << "----------------------------- Before" <<"\n";
				generalMethods::printEdgeList(tempBasicLoopEdgeSet.at(0).eList);
				generalMethods::printEdgeList(tempBasicLoopEdgeSet.at(1).eList);
				vector<basicLoopEdgeSet> tempBaiscSet;
				// 0 contains 1 --> 0 is parent loop
				//				--> 1 is child loop
				//				--> push 0 first and then 1
				tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(0));
				tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(1));
				// makes these loops 1 faceloop
				tempFaceLoop.faceloop = tempBaiscSet;
				tempFaceLoop.p = planes.at(i);
				if(planes.at(i).d>= -0.01)
					tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
				else
					tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
				tempFaceLoop.arrange();
				tempFaceLoop.faceloop.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
				//tempBaiscSet.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
				cout << "----------------------------- After" <<"\n";
				generalMethods::printEdgeList(tempBaiscSet.at(0).eList);
				generalMethods::printEdgeList(tempBaiscSet.at(1).eList);
				faceLoops.push_back(tempFaceLoop);
			}
			else if(confinement[1][0] == 1){
				cout << "----------------------------- Before" <<"\n";
				generalMethods::printEdgeList(tempBasicLoopEdgeSet.at(0).eList);
				generalMethods::printEdgeList(tempBasicLoopEdgeSet.at(1).eList);
				vector<basicLoopEdgeSet> tempBaiscSet;
				// 0 contains 1 --> 0 is parent loop
				//				--> 1 is child loop
				//				--> push 0 first and then 1
				tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(1));
				tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(0));
				// makes these loops 1 faceloop
				tempFaceLoop.faceloop = tempBaiscSet;
				tempFaceLoop.p = planes.at(i);
				if(planes.at(i).d>= -0.01)
					tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
				else
					tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
				tempFaceLoop.arrange();
				tempFaceLoop.faceloop.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
				//tempBaiscSet.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
				cout << "----------------------------- After" <<"\n";
				generalMethods::printEdgeList(tempBaiscSet.at(0).eList);
				generalMethods::printEdgeList(tempBaiscSet.at(1).eList);
				faceLoops.push_back(tempFaceLoop);
			}
			else{
				// 1st faceloop
				vector<basicLoopEdgeSet> tempBaiscSet;
				tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(0));
				// makes these loops 1 faceloop
				tempFaceLoop.faceloop = tempBaiscSet;
				tempFaceLoop.p = planes.at(i);
				if(planes.at(i).d>= -0.01)
					tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
				else
					tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
				tempFaceLoop.arrange();
				faceLoops.push_back(tempFaceLoop);	

				// 2nd faceloop
				vector<basicLoopEdgeSet> tempBaiscSet1;
				tempBaiscSet1.push_back(tempBasicLoopEdgeSet.at(0));
				// makes these loops 1 faceloop
				tempFaceLoop.faceloop = tempBaiscSet1;
				tempFaceLoop.p = planes.at(i);
				if(planes.at(i).d>= -0.01)
					tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
				else
					tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
				tempFaceLoop.arrange();
				faceLoops.push_back(tempFaceLoop);	
			}
		}

		else if(temp == 3)
		{

		  if(!threeLoopsOneInsideOther(confinement[0])){
		  	int flag = 0;
			for (int j = 0; j < temp; j++ )
			{
				vector<basicLoopEdgeSet> tempBaiscSet;
				flag = 0;
				for (int k = 0; k < temp; k++)
				{
					if(confinement[j][k]==-1 and j!=k)
						flag = 1;
				}
				// if this loop is contained in other --> leave it --> it is useless
				if(flag == 1) continue;
				int count = 0;
				for (int k = 0; k < temp; k++)
				{
					if(confinement[j][k]==1 || (confinement[j][k]==-1 && j==k)){
						tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(k));
						count ++;
					}
				}

				if(count > 1){
					vector<basicLoopEdgeSet> tempBaiscSet1;
					tempBaiscSet1.push_back(tempBasicLoopEdgeSet.at(j));
					for (int k = 0; k < temp; k++)
					{
						if(confinement[j][k]==1)
							tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(k));
					}
					tempBaiscSet = tempBaiscSet1;
				}

				tempFaceLoop.faceloop = tempBaiscSet;
				tempFaceLoop.p = planes.at(i);
				if(planes.at(i).d>= -0.01)
					tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
				else
					tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
				tempFaceLoop.arrange();
				if(count == 2){
					tempBaiscSet.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
				}
				else if(count ==3){
					//tempFaceLoop.faceloop.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
					//tempFaceLoop.faceloop.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
					tempBaiscSet.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
					tempBaiscSet.at(2) = reversebasicLoopEdgeSet(tempBaiscSet.at(2));
				}
				faceLoops.push_back(tempFaceLoop);
			}
		  }
		  // three loops one inside other
		  else{
		  	int a = firstLoop(confinement[0]);
		  	int b = secondLoop(confinement[0]);
		  	int c = thirdLoop(confinement[0]);

		  	vector<basicLoopEdgeSet> tempBaiscSet;
		  	tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(a));
		  	tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(b));

	  		tempFaceLoop.faceloop = tempBaiscSet;
			tempFaceLoop.p = planes.at(i);
			if(planes.at(i).d>= -0.01)
				tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
			else
				tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
			tempFaceLoop.arrange();
			//tempFaceLoop.faceloop.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
			tempBaiscSet.at(1) = reversebasicLoopEdgeSet(tempBaiscSet.at(1));
			faceLoops.push_back(tempFaceLoop);

			// inside most loop is another faceLoop
			vector<basicLoopEdgeSet> tempBaiscSet1;
			tempBaiscSet1.push_back(tempBasicLoopEdgeSet.at(c));
			tempBaiscSet = tempBaiscSet1;
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

		else{
			cout << "4 basicLopps on a Plane :(" << "\n";
		}

		// int flag = 0;
		// for (int j = 0; j < temp; j++ ){
		// 	vector<basicLoopEdgeSet> tempBaiscSet;
		// 	flag = 0;
		// 	for (int k = 0; k < temp; k++){
		// 		if(confinement[j][k]==-1 and j!=k)
		// 			flag = 1;
		// 	}
		// 	// if this loop is contained in other --> leave it --> it is useless
		// 	if(flag == 1) continue;

		// 	for (int k = 0; k < temp; k++){
		// 		if(confinement[j][k]==1 || (confinement[j][k]==-1 && j==k)){
		// 			tempBaiscSet.push_back(tempBasicLoopEdgeSet.at(k));
		// 		}
		// 	}

		// tempFaceLoop.faceloop = tempBaiscSet;
		// tempFaceLoop.p = planes.at(i);
		// if(planes.at(i).d>= -0.01)
		// 	tempFaceLoop.normal = {planes.at(i).a, planes.at(i).b, planes.at(i).c};
		// else
		// 	tempFaceLoop.normal = {-planes.at(i).a, -planes.at(i).b, -planes.at(i).c};
		// tempFaceLoop.arrange();
		// faceLoops.push_back(tempFaceLoop);
		// }

		}
		wireFrame::faceloops = faceLoops;
	}





/////////////***************************////////////////
// generate body loops written by saransh


	// std::vector<int> positivesUsed(faceloops.size() , 0) ;
	// std::vector<int> negativesUsed(faceloops.size() , 0) ;
	// // printf("%d  faceloop size \n",faceloops.size());
	// // std::std::vector<bool> positivesExpanded(faceloops.size(),false);
	// // std::std::vector<bool> negativesExpanded(faceloops.size(),false);

	// faceLoop startingLoop ; 
	// int numberOfFLvisited = 0 ;
	// bool somethingSelected ; 
	// // printf("%d faceloops size \n", faceloops.size());
	// int inthisloop ;
	// while(numberOfFLvisited < 2*faceloops.size()) {
	// 	for (int i = 0; i < positivesUsed.size(); ++i)
	// 	{
	// 		std::cout<<positivesUsed[i]<<" " ; 
	// 	}
	// 	std::cout<<'\n' ; 
	// 	for (int i = 0; i < negativesUsed.size(); ++i)
	// 	{
	// 		std::cout<<negativesUsed[i]<<" " ; 
	// 	}
	// 	std::cout<<'\n' ; 
	// 	printf("%d\n", numberOfFLvisited);
	// 	// printf("%s\n","stck in loop" );
	// 	inthisloop = 0 ; 
	// 	bodyLoop currentBodyLoop ;
	// 	for (int i = 0; i < faceloops.size(); ++i)
	// 		{
			
	// 		somethingSelected = false ; 
	// 		if (positivesUsed[i] == 0)
	// 		{
	// 			somethingSelected = true ; 
	// 			positivesUsed[i] = 1 ;
	// 			startingLoop = faceloops[i] ;
	// 			numberOfFLvisited += 1 ; 
	// 			inthisloop ++ ;
	// 			// cout<<"not here" ; 
	// 		}
	// 		else if (negativesUsed[i] == 0)
	// 		{
	// 			somethingSelected = true ;
	// 			negativesUsed[i] = 1 ;
	// 			// faceLoop newFaceLoop ;
	// 			// newFaceLoop.faceloop = faceloops[i].faceloop ;
	// 			// std::reverse(newFaceLoop.faceloop.begin(),newFaceLoop.faceloop.end()) ; // this reverse is not cool
	// 			// newFaceLoop.normal = { -faceloops[i].normal.x , -faceloops[i].normal.y , -faceloops[i].normal.z } ;
	// 			// newFaceLoop.p = {-faceloops[i].p.a,-faceloops[i].p.b,-faceloops[i].p.c,-faceloops[i].p.d} ; 
	// 			// startingLoop = newFaceLoop ;
	// 			startingLoop = faceloops[i].getReversedFaceLoop() ; 
	// 			numberOfFLvisited += 1 ;
	// 			inthisloop ++ ;
	// 		}

	// 		if (somethingSelected)
	// 		{
	// 			currentBodyLoop.addLoop(startingLoop) ;
	// 			printf("%s\n", "see arg face here");
	// 			printFaceLoop(startingLoop) ;
	// 			printf("%s\n","finish" );
	// 			// printf("%s\n","maka bhosda madarchod" );
	// 			// throw std::exception() ; 
	// 			std::vector<pair<int , bool>> selectedLoops ;
	// 			// std::vector<int> expandedLoops ;
	// 			// expandedLoops.push_back(0) ; 
	// 			faceLoop currentLoop = startingLoop ;
	// 			int loopCount = 0 ;  
	// 			// printf("%s\n", "entering while loop ");
			
	// 			selectedLoops = expandFaceLoop(currentLoop) ;
	// 			// printf("%s\n","returned from alphaAndDirection");
	// 			// expandedLoops[loopCount] = 1 ; 
	// 			pair<int , bool > currentPair ; 
	// 			for (int i = 0; i < selectedLoops.size(); ++i)
	// 			{	
	// 				currentPair = selectedLoops[i] ;
	// 				faceLoop loopToInsert = faceloops[currentPair.first] ;
	// 				bool canUse = false ;
	// 				bool posused = false ; 
	// 				bool negused = false ;   
	// 				if (!currentPair.second)
	// 				{
	// 					// loopToInsert.normal = {-loopToInsert.normal.x , -loopToInsert.normal.y , -loopToInsert.normal.z } ;
	// 					// loopToInsert.p = {-loopToInsert.p.a , -loopToInsert.p.b , -loopToInsert.p.c , -loopToInsert.p.d  } ;
	// 					// std::reverse(loopToInsert.faceloop.begin() , loopToInsert.faceloop.end()) ; // this reverse is not cool
	// 					if(negativesUsed[currentPair.first]==0) { 
	// 						canUse = true ;
	// 						loopToInsert = loopToInsert.getReversedFaceLoop() ; 
	// 						// negativesUsed[currentPair.first] = 1 ; 
	// 						negused = true ; 
	// 					 }
						
	// 				}
	// 				else {
	// 					if(positivesUsed[currentPair.first]==0){
	// 						canUse = true ;
	// 						posused = true ; 
	// 						// positivesUsed[currentPair.first]  = 1 ; 
	// 					} 
	// 				}
	// 				if(!canUse) {
	// 					break ; 
	// 				}
	// 				bool ifInserted = currentBodyLoop.addLoop(loopToInsert) ; 
	// 				if(ifInserted) {

	// 					if(posused) {
	// 						positivesUsed[currentPair.first] = 1 ;
	// 					}

	// 					else{
	// 						negativesUsed[currentPair.first] = 1 ;
	// 					}

	// 					numberOfFLvisited += 1 ;
	// 					inthisloop ++ ;
	// 					printf("%s\n", "see selected Loop here");
	// 					printFaceLoop(loopToInsert) ; 
	// 					printf("%s\n", "finish selected Loop");
	// 				}
	// 			}

					 
	// 			int k = 1 ; 
	// 			while(k<currentBodyLoop.bodyloop.size()){
	// 				selectedLoops = expandFaceLoop(currentBodyLoop.bodyloop[k]) ;
	// 				printf("%s\n","***********************************" );
	// 				printFaceLoop(currentBodyLoop.bodyloop[k]) ;  
	// 				for (int i = 0; i < selectedLoops.size(); i++)
	// 				{	

	// 					currentPair = selectedLoops[i] ;
	// 					faceLoop loopToInsert = faceloops[currentPair.first] ; 
	// 					// printf("%f\n",currentPair.second );
	// 					// std::cout<<currentPair.second()<<	
	// 					bool POSUSED = false ; 
	// 					bool canuse = false ; 
	// 					if (!currentPair.second)
	// 					{
	// 						// loopToInsert.normal = {-loopToInsert.normal.x , -loopToInsert.normal.y , -loopToInsert.normal.z } ;
	// 						// loopToInsert.p = {-loopToInsert.p.a , -loopToInsert.p.b , -loopToInsert.p.c , -loopToInsert.p.d  } ;
	// 						// std::reverse(loopToInsert.faceloop.begin() , loopToInsert.faceloop.end()) ; // this reverse is not cool
	// 						if(negativesUsed[currentPair.first]==0) { 
	// 							canuse = true ;
	// 							loopToInsert = loopToInsert.getReversedFaceLoop() ; 
	// 							// negativesUsed[currentPair.first] = 1 ; 
	// 							// negused = true ; 
	// 					 	}
	// 					}
	// 					else {
	// 						if(positivesUsed[currentPair.first]==0){
	// 							canuse = true ;
	// 							POSUSED = true ; 
	// 							// positivesUsed[currentPair.first]  = 1 ; 
	// 						} 
	// 					}
						
	// 					if (canuse)
	// 					{
	// 						bool ifInserted = currentBodyLoop.addLoop(loopToInsert) ; 
	// 						if(ifInserted) {

	// 						if (POSUSED)
	// 						{
	// 							positivesUsed[currentPair.first] = 1 ; 
	// 						}
	// 						else{
	// 							negativesUsed[currentPair.first] = 1 ; 
	// 						}
	// 						numberOfFLvisited += 1 ;
	// 						inthisloop ++ ;
	// 						printf("%s\n", "see selected Loop here");
	// 						printFaceLoop(loopToInsert) ; 
	// 						printf("%s\n", "finish selected Loop");
	// 						}
	// 						else{
	// 						printf("%s\n", "cant add this ******************" );
	// 						printFaceLoop(loopToInsert);

	// 						}
	// 					}
						
	// 				}
	// 				k+=1;

	// 			}
	// 				// printf("%d\n",k );
									
	// 			bodyloops.push_back(currentBodyLoop) ;   
	// 			break ;  
	// 		}
	// 	}

	// 	// printf("%d\n",inthisloop );
	// 	printf("%s\n", "----------------------------------------------------------");
	// 	printf("%s\n", "----------------------------------------------------------");

	// }
	// printf("%d\n", numberOfFLvisited);
