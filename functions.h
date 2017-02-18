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

int readIn(vector<vertex> &v, vector<edge> &e, vector<face> &f, string filename);
int smoothLapAng(vector<vertex> &v,vector<face> &f);
void smooth1(std::vector<vertex> &v, std::vector<face> &f, double ar);
void smooth1Star(std::vector<vertex> &v, std::vector<face> &f, double ar);
void smooth2Star(std::vector<vertex> &v, std::vector<face> &f, double ar);



void maxminAng(vector<vertex> &v, vector<face> &f, double &max, double &min);
double aspectR(vector<vertex> &v, vector<face> &f, double &med);
double GetCircumCenterX(double Ax, double Ay, double Bx, double By, double Cx, double Cy);
double GetCircumCenterY(double Ax, double Ay, double Bx, double By, double Cx, double Cy);

double movePX(double Ax, double Ay, double cenX, double cenY, double ang);
double movePY(double Ax, double Ay, double cenX, double cenY, double ang);



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
