#include "wireframe.h"
#include "EdgeList2D.h"
#include "generalMethods.h"
#include "Plane.h"
#include "VertexList2D.h"
#include "basicLoopEdgeSet.h"
#include "bodyLoop.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;
#include "TwoDObj.h"
/*
╭━━━╮╭━━━╮╭━━━╮
┃╭━╮┃┃╭━╮┃╰╮╭╮┃
┃┃╱╰╯┃┃╱┃┃╱┃┃┃┃
┃┃╱╭╮┃╰━╯┃╱┃┃┃┃
┃╰━╯┃┃╭━╮┃╭╯╰╯┃
╰━━━╯╰╯╱╰╯╰━━━╯
*/


// TODO------------------->
// make all basic Loops on a plane in the direction of plane


int main(){

    int from32 = 0;
      cout << "Which conversion do you want\n"<< "1. From 2D to 3D reconstruction.\n" << "2. From 3D to 2D projections\n";
      while(from32!=1 and from32!=2){
        cin >> from32;
      }

    if(from32 == 1){
        vertex2D tempVertex;
        VertexList2D frontProjVertex;
        EdgeList2D frontProjEdges;
        VertexList2D topProjVertex;
        EdgeList2D topProjEdges;
        VertexList2D sideProjVertex;
        EdgeList2D sideProjEdges;
        wireFrame wireframe;
        cout << " For the reconstruction of solid please enter the details about the 3 projections\n";


        FILE * file;
        char filename[255];
        char outFilename[255];
        int fileOpenFlag = 0;
        while(fileOpenFlag!=1){
            cout << "Enter the name of file containing projection information\n";
            scanf("%s",filename);
            strcpy(outFilename,filename);
            strcat(filename,".txt");
            //cout << filename;
            file = fopen(filename, "r");
            fileOpenFlag = 1;
            if( file == NULL ){
                fileOpenFlag = 0;
                printf("Impossible to open the file !\n");
                //return false;
            }
        }

        // parsing the file
        while( 1 ){
            int firstVertex, secondVertex;
            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF){
                //cout << "EOF :(\n";
                break; // EOF = End Of File. Quit the loop.
            }

            // else : parse lineHeader
            if ( strcmp( lineHeader, "//" ) == 0 ){
                //cout  << " Read // \n";
                // ignore the comments
            }
            else if ( strcmp( lineHeader, "f" ) == 0 ){
                // potential cause of error --|
                cout  << "f ";
                fscanf(file, "%f %f\n", &tempVertex.a, &tempVertex.b);
                cout << tempVertex.a << " " << tempVertex.b <<"\n";
                frontProjVertex.addVertex(tempVertex);
            }
            else if ( strcmp( lineHeader, "t" ) == 0 ){
                // potential cause of error --|
                cout  << "t ";
                fscanf(file, "%f %f\n", &tempVertex.a, &tempVertex.b);
                cout << tempVertex.a << " " << tempVertex.b <<"\n";
                topProjVertex.addVertex(tempVertex);
            }
            else if ( strcmp( lineHeader, "s" ) == 0 ){
                // potential cause of error --|
                cout  << "v ";
                fscanf(file, "%f %f\n", &tempVertex.a, &tempVertex.b);
                cout << tempVertex.a << " " << tempVertex.b <<"\n";
                sideProjVertex.addVertex(tempVertex);
            }
            else if ( strcmp( lineHeader, "fe" ) == 0 ){
                // potential cause of error --|
                fscanf(file, "%d %d\n", &firstVertex, &secondVertex);
                frontProjEdges.addEdge({ frontProjVertex.vertexList.at(firstVertex-1), frontProjVertex.vertexList.at(secondVertex-1) });
                //generalMethods::printVertex2D(frontProjVertex.vertexList.at(firstVertex-1));
                //generalMethods::printVertex2D(frontProjVertex.vertexList.at(secondVertex-1));
                //cout << "\n";
                //generalMethods::printEdge(frontProjEdges.edgeList[(frontProjEdges.edgeList.end()-1]);
            }
            else if ( strcmp( lineHeader, "te" ) == 0 ){
                // potential cause of error --|
                fscanf(file, "%d %d\n", &firstVertex, &secondVertex);
                topProjEdges.addEdge({ topProjVertex.vertexList.at(firstVertex-1), topProjVertex.vertexList.at(secondVertex-1) });
            }
            else if ( strcmp( lineHeader, "se" ) == 0 ){
                // potential cause of error --|
                fscanf(file, "%d %d\n", &firstVertex, &secondVertex);
                sideProjEdges.addEdge({ sideProjVertex.vertexList.at(firstVertex-1), sideProjVertex.vertexList.at(secondVertex-1) });
            }
        }
            fclose(file);   
            wireframe.generateWireFrame(frontProjVertex, topProjVertex, sideProjVertex,
            frontProjEdges, topProjEdges, sideProjEdges );

            //wireframe.printVertices();
            //wireframe.printEdges();
            //wireframe.printPlanes();
            //wireframe.printFaceLoops();

            strcat(outFilename, ".obj");
            cout <<"A file with the name "<<outFilename<< " has been generated.\n";
            /******************/
            // writing object to obj file
            ofstream myfile (outFilename);
            string vertices = wireframe.getVertices();
            myfile << vertices;

            string body = wireframe.getBody();
            myfile << body;


            myfile.close();
            /*****************/
    }
    // end 2d -> 3d reconstruction

    // start 3d->2d projection
    else{
        FILE * file;
        char filename[255];
        char outFilename[255];
        int fileOpenFlag = 0;
        while(fileOpenFlag!=1){
            cout << "Enter the name of file containing information about 3D object\n";
            scanf("%s",filename);
            strcpy(outFilename,filename);
            strcat(filename,".obj");
            //cout << filename;
            file = fopen(filename, "r");
            fileOpenFlag = 1;
            if( file == NULL ){
                fileOpenFlag = 0;
                printf("Impossible to open the file !\n");
                //return false;
            }
        }
        // generate a body with this obj file and take its projection
        wireFrame wireframe;
        vertex3D localVertex;
        edge3D localEdge;
        int firstVertex, secondVertex;
        int flagEndOfFile = 0;
        while( 1 ){

            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; // EOF = End Of File. Quit the loop.

            // else : parse lineHeader
            if ( strcmp( lineHeader, "v" ) == 0 ){
                cout << "v ";
                fscanf(file, "%f %f %f\n", &localVertex.a, &localVertex.b, &localVertex.c );
                wireframe.addVertex(localVertex);
                generalMethods::printVertex(localVertex);cout << "\n";

            }
            else if ( strcmp( lineHeader, "vt" ) == 0 ){
                char c = ' ';
                cout << "vt ";
                while(c!='\n'){
                    fscanf(file, "%c", &c);
                    cout << c;
                }
            }
            else if ( strcmp( lineHeader, "vn" ) == 0 ){
                char c = ' ';
                cout <<"vn ";
                while(c!='\n'){
                    fscanf(file, "%c", &c);
                    cout << c;
                }
            }
            else if ( strcmp( lineHeader, "f" ) == 0 ){
                cout << "f ";
                fscanf(file, "%d",&firstVertex);
                cout << firstVertex;
                while(1){
                    char c;
                    fscanf(file, "%c", &c);
                    if(c == '/'){
                        cout << c;
                        while(c!=' '){
                            fscanf(file, "%c", &c);
                            cout << c;
                        }
                    }
                    else if(c == ' '){
                        cout << c;
                    }
                    else if(c == EOF){
                        flagEndOfFile =1;
                        break;
                    }
                    else if(c == '\n'){
                        cout << c;
                        break;
                    }
                    fscanf(file, "%d",&secondVertex);
                    cout << secondVertex;
                    wireframe.addEdge({ wireframe.vertexList.at(firstVertex-1), wireframe.vertexList.at(secondVertex-1) });

                    firstVertex = secondVertex;
                } 
                if(flagEndOfFile == 1) break;  
            }
            else if( strcmp( lineHeader, "\n" ) == 0)
                {cout <<"\n";}
            else{
                char c = ' ';
                while(c!='\n'){
                    fscanf(file, "%c", &c);
                }                
            }
        // end of while
        }

        wireframe.getFullBody();
        TwoDObj *twodObj = new TwoDObj(wireframe.vertexList, wireframe.edgeList ,  wireframe.getfaces() ) ;
        cout<<"calling getviews" << endl ;
        float angles[] = {0.0 , 0.0 , 1.0 } ;
        twodObj->applyRotation(angles);
        std::vector< std::vector<edge2D> > views = twodObj->getViews() ;
        std::vector<edge2D> topViewEdges = views[0] ;
        std::vector<edge2D> frontViewEdges = views[1] ;
        std::vector<edge2D> sideViewEdges = views[2] ;
        std::vector<edge2D> isometricView = views[3] ;
        std::vector<edge2D> topViewHidden = views[4] ;
        std::vector<edge2D> frontViewHidden = views[5] ;
        std::vector<edge2D> sideViewHidden = views[6] ;
        float* firstPoint ;
        float* secondPoint ;
        QApplication a(argc, argv);
        QLabel l;
        QPicture pi;
        QPainter p(&pi);
        edge2D currentEdge ;
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
        p.scale(0.9,-0.9);
    //    p.translate(-600,-600);

        // p.drawLine(0, 0, 200, 200);
        float x, y, prev_x=0, prev_y=0 ;
        for(unsigned i = 0 ; i < frontViewHidden.size();i+=1){
            currentEdge = frontViewHidden[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        for(unsigned i = 0 ; i < sideViewHidden.size();i+=1){
            currentEdge = sideViewHidden[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        for(unsigned i = 0 ; i < topViewHidden.size();i+=1){
            currentEdge = topViewHidden[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        p.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
        for(unsigned i = 0 ; i < topViewEdges.size();i+=1){
            currentEdge = topViewEdges[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        for(unsigned i = 0 ; i < frontViewEdges.size();i+=1){
            currentEdge = frontViewEdges[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        for(unsigned i = 0 ; i < sideViewEdges.size();i+=1){
            currentEdge = sideViewEdges[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        for(unsigned i = 0 ; i < isometricView.size();i+=1){
            currentEdge = isometricView[i] ;
            firstPoint = currentEdge.v1.getCoordinates() ;
            secondPoint = currentEdge.v2.getCoordinates() ;
            p.drawLine(firstPoint[0],firstPoint[1],secondPoint[0],secondPoint[1] );
        }
        float* set = twodObj->getMinXY() ;
        p.drawLine(400+set[1],-100+set[0],400+set[1],1000+set[0]);
        p.drawLine(0+set[1],400+set[0],900+set[1],400+set[0]);


        p.end(); // Don't forget this line!

        l.setPicture(pi);
        l.show();
        QLabel l2 ;
        l2.setPicture(pi);
        l2.show();
        return a.exec();
        // end of 3d->2d
    }
	return 0 ;
}
