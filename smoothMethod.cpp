#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int smoothLapAng(vector<vertex> &v, vector<face> &f){
    for (int i=0; i<v.size(); i++) {// for each vertex in mesh
    	double xnew = 0;
        double ynew = 0;
        vertex lastV(0,0,0), nextV(0,0,0), thisV(0,0,0);

    	if(v[i].onBound == 0){	
    		for(int j= 0; j<v[i].neighborSize; j++){ // for each vertex in neihgbor face
    			lastV = v[v[i].neighbors[(v[i].neighborSize+j-1)%v[i].neighborSize]];
    			thisV = v[v[i].neighbors[j]];
    			nextV = v[v[i].neighbors[(j+1)%v[i].neighborSize]];

    			//cout << "lastV thisV nextV " << v[i].neighbors[(v[i].neighborSize+j-1)%v[i].neighborSize]
    			// <<" " <<v[i].neighbors[j] <<" " <<v[i].neighbors[(j+1)%v[i].neighborSize] <<endl;
                double vecLastX, vecLastY, vecSelfX, vecSelfY, vecNextX, vecNextY;
    			double angle1, angle2, beta;

    			vecLastX = lastV.x - thisV.x;
    			vecLastY = lastV.y - thisV.y;
    			vecSelfX = v[i].x - thisV.x;
    			vecSelfY = v[i].y - thisV.y;
    			vecNextX = nextV.x - thisV.x;
    			vecNextY = nextV.y - thisV.y;

    			angle1 = acos((vecNextX*vecSelfX + vecNextY*vecSelfY)
                              /(sqrt(pow(vecNextX,2)+pow(vecNextY,2))
                                *sqrt(pow(vecSelfX,2)+pow(vecSelfY,2)) )  );
                //cout << "angle1: " << angle1*180/3.1415926 << endl;  // for test angle
                angle2 = acos((vecLastX*vecSelfX + vecLastY*vecSelfY)
                              /(sqrt(pow(vecLastX,2)+pow(vecLastY,2))
                                *sqrt(pow(vecSelfX,2)+pow(vecSelfY,2)) )  );
                //cout << " angle2: " << angle2*180/3.1415926 << endl;  //for test angle
                
                
                beta = (angle2 - angle1)/2;


                xnew += thisV.x + vecSelfX*cos(beta) - vecSelfY*sin(beta);
                ynew += thisV.y + vecSelfX*sin(beta) + vecSelfY*cos(beta);

    		}
    		v[i].x = xnew/v[i].neighborSize;
    		v[i].y = ynew/v[i].neighborSize;


    	}
    }


	return 1;
}