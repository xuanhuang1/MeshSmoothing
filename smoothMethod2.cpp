#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926

void smooth2StarQ(std::vector<vertex> &v, std::vector<face> &f, double ar){
    for (int i=0; i<v.size(); i++) {// for each vertex in mesh
        double xnew = 0;
        double ynew = 0;
        vertex nextV(0,0,0), thisV(0,0,0);

        if(v[i].onBound == 0){  
            for(int j= 0; j<v[i].neighborSize; j+=2){ // for each vertex in neihgbor face
                // get the next vertex and forms a triangle with v[i]
                thisV = v[v[i].neighbors[j]];
                nextV = v[v[i].neighbors[(j+2)%v[i].neighborSize]];


                double vecx,vecy, angle = 0.01;
                double lastEdge, nextEdge,thisEdge, tempAR, minAng, thisAng;
                int self, next, ver2;
                double centerX, centerY;


                //for triangle only!!!
                centerX = GetCircumCenterX(thisV.x, thisV.y,nextV.x, nextV.y,v[i].x, v[i].y);
                centerY = GetCircumCenterY(thisV.x, thisV.y,nextV.x, nextV.y,v[i].x, v[i].y);

                std::vector<int> tempInts;
                tempInts.push_back(i);
                tempInts.push_back(v[i].neighbors[j]);
                tempInts.push_back(v[i].neighbors[(j+2)%v[i].neighborSize]);

                // in that triangle
                face aFaceInStar = face(tempInts);
                for(int k=0; k<aFaceInStar.listOfV.size(); k++){ 
                    self = aFaceInStar.listOfV[k];
                    next = aFaceInStar.listOfV[(k+1)%aFaceInStar.listOfV.size()];
                    int last = aFaceInStar.listOfV[(aFaceInStar.listOfV.size()+k-1)%aFaceInStar.listOfV.size()];
                    //cout << self <<" "<< next <<" "<< endl;

                    vecx = v[next].x - v[self].x;   
                    vecy = v[next].y - v[self].y; 
                    double vec1x = v[last].x - v[self].x;
                    double vec1y = v[last].y - v[self].y;

                    // find max and min edge
                    if(k==0){
                        minAng = thisAng;
                        lastEdge = sqrt(pow(vecx,2)+ pow(vecy,2));
                        nextEdge = sqrt(pow(vec1x,2)+ pow(vec1y,2));

                        if(lastEdge < nextEdge){
                            angle = -0.01;
                            ver2 = last;
                        }else{
                            angle = 0.01;
                            ver2 = next;
                        }

                    }else{
                        if(thisAng < minAng)
                            minAng = thisAng;
                    }
                }

                double xTobeMove = v[i].x, yTobeMove = v[i].y;

                // 2 for fine 1.5 for good mesh

                if ( max(lastEdge, nextEdge)/min(lastEdge, nextEdge) < ar )
                {
                    //cout <<"ratoi" <<endl;
                    //cout << max(lastEdge, nextEdge)/min(lastEdge, nextEdge) <<endl;
                }else{


                //cout << max << " "<< min <<endl;

                //if(minAng < 30*PI/180){

                    //cout << "min " <<minAng*PI/180 <<endl;
                    //cout << minAng << " "<<endl;
                    double count = 3;

                    while(count > 0){
                        xTobeMove = movePX(xTobeMove, yTobeMove, centerX, centerY, angle);
                        yTobeMove = movePY(xTobeMove, yTobeMove, centerX, centerY, angle);
                        count --;
                        //cout << "thisEdge+0.01*max: " <<thisEdge+0.01*max << " currentDist: " << currentDist<<endl;
                    }
                    
                }


                //}
                double ordis = findShortestDistInStar(v, f, v[i].x, v[i].y, v[i].neighbors);
                double dis = findShortestDistInStar(v, f, xTobeMove, yTobeMove, v[i].neighbors);
                if(dis < ordis){
                    xTobeMove = v[i].x;
                    yTobeMove = v[i].y;
                }


                xnew += xTobeMove;
                ynew += yTobeMove;


            }

            v[i].x = 2*xnew/v[i].neighborSize;
            v[i].y = 2*ynew/v[i].neighborSize;

        }
    }


}
