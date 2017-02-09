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
    double aspectR, det, minAng;
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
    std::vector<int> neighbors;
    int neighborSize;
};

class edge{
public:
    int node1, node2;
    int edgeRep;
    edge(int,int);
};

#endif /* face_h */
