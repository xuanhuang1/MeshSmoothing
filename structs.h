//
//  face.h
//  
//
//  Created by Xuan Huang on 6/23/16.
//
//

#ifndef structs_h
#define structs_h

#include <vector>
#include <string>

class face{
public:
    int numOfV;
    double aspectR, det;
    std::vector<int> listOfV;
    face(std::vector<int>);
    int hasV(int);
    std::string listToS();
};

class vertex{
public:
    double x,y,z;
    int onBound;
    vertex(double, double,double);
    std::vector<face> neighbors;
};

class edge{
public:
    int node1, node2;
    int edgeRep;
    edge(int,int);
};

#endif /* face_h */
