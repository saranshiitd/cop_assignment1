# Makefile for compiling CAD Module

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -std=c++11

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o VertexList2D.o wireframe.o EdgeList2D.o generalMethods.o structs.o Plane.o basicLoopEdgeSet.o faceLoop.o
	$(CXX) $(CXXFLAGS) -o main main.o VertexList2D.o wireframe.o EdgeList2D.o generalMethods.o structs.o Plane.o basicLoopEdgeSet.o faceLoop.o


main.o: wireframe.h EdgeList2D.h generalMethods.h Plane.h VertexList2D.h basicLoopEdgeSet.h bodyLoop.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# make is smart to infer that .o file needs corrosponding .cpp file hence we may not write it explicitely

VertexList2D.o: VertexList2D.h structs.h	
	$(CXX) $(CXXFLAGS) -c VertexList2D.cpp

wireframe.o: wireframe.h structs.h EdgeList2D.h VertexList2D.h generalMethods.h basicLoopEdgeSet.h bodyLoop.h
	$(CXX) $(CXXFLAGS) -c wireframe.cpp

EdgeList2D.o: EdgeList2D.h structs.h
	$(CXX) $(CXXFLAGS) -c EdgeList2D.cpp

generalMethods.o: generalMethods.h structs.h basicLoopEdgeSet.h faceLoop.h bodyLoop.h
	$(CXX) $(CXXFLAGS) -c generalMethods.cpp

structs.o: structs.cpp structs.h
	$(CXX) $(CXXFLAGS) -c structs.cpp

Plane.o: Plane.h structs.h
	$(CXX) $(CXXFLAGS) -c Plane.cpp

basicLoopEdgeSet.o: basicLoopEdgeSet.h VertexList2D.h EdgeList2D.h structs.h
	$(CXX) $(CXXFLAGS) -c basicLoopEdgeSet.cpp

faceLoop.o: structs.h faceLoop.h basicLoopEdgeSet.h generalMethods.h
	$(CXX) $(CXXFLAGS) -c faceLoop.cpp
	

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) main *.o *~