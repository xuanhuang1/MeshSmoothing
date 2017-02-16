//
//  functions.hpp
//  
//
//  Created by Xuan Huang on 6/28/16.
//
//

#include "functions.h"


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
    generatedList[3] = 1;
    generatedList[4] = 1;
    generatedList[5] = 1;
    generatedList[6] = 1;
    generatedList[7] = 0;

    srand(time(NULL));

    for (int i = 4; i<TOTALVERTICES; i++){
        generatedList[i*2] = (rand() % precPara1 +1)/precDivider;
        generatedList[i*2+1] = (rand() % precPara1 +1)/precDivider;
    }
        
    ofstream outputfile;
    outputfile.open(afilename, ios::out | ios::trunc);
    
    outputfile << TOTALVERTICES<<" "<< "2 0 0"<< endl;
    
    for (int i =0; i<TOTALVERTICES; i++){
        outputfile << i+1  << " "<< 100*generatedList[2*i] << " " << 100*generatedList[2*i+1] <<endl;
    }
    
    outputfile <<"4 0"<< endl;

    outputfile <<"1 1 2"<< endl;
    outputfile <<"2 2 3"<< endl;
    outputfile <<"3 3 4"<< endl;
    outputfile <<"4 4 1"<< endl;

    outputfile <<"0"<< endl;

    outputfile.close();
}
