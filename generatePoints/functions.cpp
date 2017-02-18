//
//  functions.hpp
//  
//
//  Created by Xuan Huang on 6/28/16.
//
//

#include "functions.h"

#define TOTALVERTICES 40
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

    int precPara1 = 10*PERCISION;
    float precDivider = precPara1 + 0.0;

    float generatedList[TOTALVERTICES*2];

    //4 boudary vertices
    generatedList[0] = 0;
    generatedList[1] = 0;

    generatedList[2] = 0;
    generatedList[3] = 0.2;
    generatedList[4] = 0;
    generatedList[5] = 0.7;

    generatedList[6] = 0;
    generatedList[7] = 1;

    generatedList[8] = 0.4;
    generatedList[9] = 1;
    generatedList[10] = 0.6;
    generatedList[11] = 1;

    generatedList[12] = 1;
    generatedList[13] = 1;

    generatedList[14] = 1;
    generatedList[15] = 0.9;
    generatedList[16] = 1;
    generatedList[17] = 0.5;
    generatedList[18] = 1;
    generatedList[19] = 0.2;

    generatedList[20] = 1;
    generatedList[21] = 0;

    generatedList[22] = 0.8;
    generatedList[23] = 0;
    generatedList[24] = 0.7;
    generatedList[25] = 0;
    generatedList[26] = 0.3;
    generatedList[27] = 0;



    srand(time(NULL));

    for (int i = 14; i<TOTALVERTICES; i++){
        generatedList[i*2] = (rand() % precPara1 +1)/precDivider;
        generatedList[i*2+1] = (rand() % precPara1 +1)/precDivider;
    }
        
    ofstream outputfile;
    outputfile.open(afilename, ios::out | ios::trunc);
    
    outputfile << TOTALVERTICES<<" "<< "2 0 0"<< endl;
    
    for (int i =0; i<TOTALVERTICES; i++){
        outputfile << i+1  << " "<< 10*generatedList[2*i] << " " << 10*generatedList[2*i+1] <<endl;
    }

    outputfile <<"14 0"<< endl;
    for (int i = 1; i<14+1; i++){
        if(i == 14){
            outputfile << i <<" " << i << " "<< 1<< endl;
        }else{
            outputfile << i <<" " << i << " "<< i+1<< endl;
        }
    }


    outputfile <<"0"<< endl;

    outputfile.close();
}
