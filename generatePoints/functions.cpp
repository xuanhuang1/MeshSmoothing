//
//  functions.hpp
//  
//
//  Created by Xuan Huang on 6/28/16.
//
//

#include "functions.h"

#define TOTALVERTICES 1000
#define PERCISION 5   //digit after .

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

void fourVerticesOnEdge(char* afilename){

    int precPara1 = pow(10,PERCISION);
    float precDivider = precPara1 + 0.0;

    float generatedList[TOTALVERTICES*2];


    for (int i = 0; i<20; i++){
        generatedList[i*2] = 0;
        generatedList[i*2+1] = (i)*(1.0/20);
    }
    for (int i = 20; i<40; i++){
        generatedList[i*2] = 1;
        generatedList[i*2+1] = 1-(i-20)*(1.0/20);
    }
    for (int i = 40; i<60; i++){
        generatedList[i*2] = 1-(i-40)*(1.0/20);
        generatedList[i*2+1] = 0;
    }
    for (int i = 60; i<80; i++){
        generatedList[i*2] = (i-60)*(1.0/20);
        generatedList[i*2+1] = 1;
    }



    srand(time(NULL));

    for (int i = 80; i<TOTALVERTICES; i++){
        generatedList[i*2] = 0.05 + 0.90*(rand() % precPara1 +1)/precDivider;
        generatedList[i*2+1] = 0.05 + 0.90*(rand() % precPara1 +1)/precDivider;
    }
        
    ofstream outputfile;
    outputfile.open(afilename, ios::out | ios::trunc);
    
    outputfile << TOTALVERTICES<<" "<< "2 0 0"<< endl;


    for (int i =0; i<TOTALVERTICES; i++){
        outputfile << i+1  << " "<< generatedList[2*i] << " " << generatedList[2*i+1] <<endl;
    }




    outputfile <<"0"<< endl;

    outputfile.close();
}
