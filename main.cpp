//
//  main.cpp
//
//
//  Created by Xuan Huang on 6/23/16.
//
//

#include "functions.h"
#include <string.h>
#include <math.h>

#define PI 3.1415926

using namespace std;

int main(int argc, char* argv[]){
    if(argc != 4){
        cout << "Usage: ./test [flag: -Lap -s -q] inputOff outputOff" <<endl;
        return 1; 
    }

    string runFlag = argv[1];
    string infi = argv[2];
    string outfi = argv[3];

    ifstream inputFile(infi);
    
    if(!inputFile){
        cout << "Cannot open file" << endl;
        return 1;
    }

    vector<vertex> v;
    vector<edge> e;
    vector<face> f;
    
    readIn(v, e, f, infi);

    double maxAngle, minAngle, med, aspectratio;
    maxminAng(v, f, maxAngle, minAngle);
    aspectratio = aspectR(v, f, med);

    cout << "\noriginal :" <<endl;
    cout << "max: " << maxAngle*180/PI << " min: " << minAngle*180/PI<<endl;
    cout << "aspectR: " << aspectratio<<endl;
    
    int a =20;
    float thresh = 2;
    while(a >0 ){
        if(!runFlag.compare("-Lap")){
            smoothLapAng(v, f);
        }else if(!runFlag.compare("-s")){
            for (int i = 0; i < 8; ++i){
                if(aspectratio < 4){
                    thresh = 1.2;
                }else if(aspectratio < 8 ){
                    thresh = aspectratio /4;
                }
                smooth2Star(v, f, thresh);
            }
        }else if(!runFlag.compare("-q")){
            for (int i = 0; i < 8; ++i){
                if(aspectratio < 4){
                    thresh = 1.2;
                }else if(aspectratio < 8 ){
                    thresh = aspectratio /4;
                }
                smooth2StarQ(v, f, thresh);
            }


        }else{
            cout << "Wrong flag!" <<endl;
            return 1;
        }
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
    outputfile.open(outfi, ios::out | ios::trunc);
    
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


    //double s = lineDistPoint(1, 1, 2, 2, 3, 4);
    //cout << s <<endl;
    
    return 0;
    
}