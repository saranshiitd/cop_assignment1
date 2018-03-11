# Makefile for compiling CAD Module

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o VertexList2D.o
	$(CXX) $(CXXFLAGS) -o main main.o VertexList2D.o

# The main.o target can be written more simply by removing main.cpp

main.o: main.cpp structs.h wireframe.h EdgeList2D.h generalMethods.h Plane.h VertexList2D.h basicLoopEdgeSet.h bodyLoop.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# make is smart to infer that .o file needs corrosponding .cpp file hence we may not write it explicitely
VertexList2D.o: VertexList2D.h structs.h	
	$(CXX) $(CXXFLAGS) -c VertexList2D.cpp
structs.h : structs.cpp 
	$(CXX) $(CXXFLAGS) -c structs.cpp