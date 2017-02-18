//
//  main.cpp
//
//
//  Created by Xuan Huang on 6/23/16.
//
//

#include "functions.h"
#include <string.h>

#define PI 3.1415926

using namespace std;

int main(int argc, char* argv[]){
    ifstream inputFile(argv[1]);
    
    if(!inputFile){
        cout << "Cannot open file" << endl;
        return 1;
    }
    string fileN = argv[1];

    vector<vertex> v;
    vector<edge> e;
    vector<face> f;
    
    readIn(v, e, f, fileN);

    double maxAngle, minAngle, med, aspectratio;
    maxminAng(v, f, maxAngle, minAngle);
    aspectratio = aspectR(v, f, med);

    cout << "\noriginal :" <<endl;
    cout << "max: " << maxAngle*180/PI << " min: " << minAngle*180/PI<<endl;
    cout << "aspectR: " << aspectratio<<endl;
    
    int a =50;
    while(a >0){
        smooth1Star(v, f, aspectratio/5);
        a--;
    }

    cout << "\nafter smooth : "<<endl;
    aspectratio = aspectR(v, f, med);
    maxminAng(v, f, maxAngle, minAngle);
    cout << "max: " << maxAngle*180/PI << " min: " << minAngle*180/PI<<endl;
    cout << "aspectR: " << aspectratio<<endl;
    /*
    for (int i=0; i<v.size(); i++) {
        cout << v[i].x << " "<< v[i].y << " "<< v[i].z << " "<< endl;
    }
    for (int i=0; i<e.size(); i++) {
        cout << e[i].node1 << " "<< e[i].node2<< endl;
    }
    cout << f.size() <<endl;*/
    ofstream outputfile;
    outputfile.open(argv[2], ios::out | ios::trunc);
    
    outputfile << "OFF" << endl;
    outputfile << v.size()<<" "<< f.size()<<" "<<e.size()<<" "<< endl;
    
    for (int i =0; i<v.size(); i++){
        outputfile << v[i].x << " " << v[i].y << " " << v[i].z <<endl;
    }
    
    for (int i =0; i<f.size(); i++){
        outputfile << f[i].listOfV.size() << " "<< f[i].listToS();
        outputfile <<"\n";
    }
    outputfile.close();
    
    return 0;
    
}