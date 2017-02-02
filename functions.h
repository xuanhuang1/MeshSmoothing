//
//  functions.hpp
//  
//
//  Created by Xuan Huang on 6/28/16.
//
//

#ifndef functions_h
#define functions_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "structs.h"


using namespace std;



struct Vertex{
    double x;
    double y;
    double z;
};

struct CREAnalysis{
    double AR;
    double skew;
    double taperX;
    double taperY;
    double jacobianDet;
    double modifiedDet;
};

CREAnalysis analyze(Vertex vertices[4]);



#endif /* functions_h */
