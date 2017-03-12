#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926

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


void smooth1(std::vector<vertex> &v, std::vector<face> &f, double ar){
	//for each face
	for(int k=0; k<f.size(); k++){
	
		double min,max,vecx,vecy;
		double thisEdge, tempAR, minAng, thisAng;
		int self, next, ver1, ver2;
        double centerX, centerY;


        //for triangle only!!!
        centerX = GetCircumCenterX(v[f[k].listOfV[0]].x, v[f[k].listOfV[0]].y,
        						   v[f[k].listOfV[1]].x, v[f[k].listOfV[1]].y,
        						   v[f[k].listOfV[2]].x, v[f[k].listOfV[2]].y);
        centerY = GetCircumCenterY(v[f[k].listOfV[0]].x, v[f[k].listOfV[0]].y,
        						   v[f[k].listOfV[1]].x, v[f[k].listOfV[1]].y,
        						   v[f[k].listOfV[2]].x, v[f[k].listOfV[2]].y);
        //
        // 
		for(int i=0; i<f[k].listOfV.size(); i++){ 
			self = f[k].listOfV[i];
			next = f[k].listOfV[(i+1)%f[k].listOfV.size()];
			int last = f[k].listOfV[(f[k].listOfV.size()+i-1)%f[k].listOfV.size()];

			//cout << selfIndex <<" "<< nextIndex <<" "<<lastIndex<<endl;

			vecx = v[next].x - v[self].x;	
			vecy = v[next].y - v[self].y;	
            double vec1x = v[last].x - v[self].x;
            double vec1y = v[last].y - v[self].y;

			thisEdge = sqrt(pow(vecx,2)+ pow(vecy,2));
            thisAng = acos((vec1x*vecx + vec1y*vecy)
                             /(sqrt(pow(vec1x,2)+pow(vec1y,2))
                               *sqrt(pow(vecx,2)+pow(vecy,2)) )  );

			if(i==0){
				max = thisEdge;
				min = thisEdge;
                minAng = thisAng;
				ver1 = self;
				ver2 = next;
			}else{
				if(thisEdge>max){
					max = thisEdge;
				}
				if(thisEdge<min){
					min = thisEdge;
					ver1 = self;
					ver2 = next;
				}
                if(thisAng < minAng)
                    minAng = thisAng;
			}
			
		}
	

		tempAR = max/min;

		if(minAng < 20*PI/180){
                    //cout << "min " <<minAng*PI/180 <<endl;

			if(v[ver1].onBound == 0){
                //cout << ver1 << " "<<endl;
				double angle = -0.01;
				double currentDist = min;

				while(currentDist < min+0.01*max){
						v[ver1].x = movePX(v[ver1].x, v[ver1].y, centerX, centerY, angle);
						v[ver1].y = movePY(v[ver1].x, v[ver1].y, centerX, centerY, angle);
						currentDist = sqrt(pow(v[ver1].x-v[ver2].x, 2) + pow(v[ver1].y-v[ver2].y, 2));
				}

				min = currentDist;
			}

			if(v[ver2].onBound == 0){
				double angle = 0.01;
				double currentDist = min;

				while(currentDist < min+0.01*max){
						v[ver2].x = movePX(v[ver2].x, v[ver2].y, centerX, centerY, angle);
						v[ver2].y = movePY(v[ver2].x, v[ver2].y, centerX, centerY, angle);
						currentDist = sqrt(pow(v[ver1].x-v[ver2].x, 2) + pow(v[ver1].y-v[ver2].y, 2));

				}

                //cout << ver2 << " "<<endl;
			}



		//}else{
        //    cout << "tar " << tempAR <<endl;
        }
	}

}


//  for each star region
//  for each neighborhood face
//  check if the center point is on the shortest edge, if true move accordingly (on circumcircle)
//  take average

void smooth1Star(std::vector<vertex> &v, std::vector<face> &f, double ar){
    for (int i=0; i<v.size(); i++) {// for each vertex in mesh
        double xnew = 0;
        double ynew = 0;
        vertex nextV(0,0,0), thisV(0,0,0);

        if(v[i].onBound == 0){  
            for(int j= 0; j<v[i].neighborSize; j++){ // for each vertex in neihgbor face
                // get the next vertex and forms a triangle with v[i]
                thisV = v[v[i].neighbors[j]];
                nextV = v[v[i].neighbors[(j+1)%v[i].neighborSize]];


                double min,max,vecx,vecy;
                double thisEdge, tempAR, minAng, thisAng;
                int self, next, lastIndex, ver1, ver2;
                double centerX, centerY;


                //for triangle only!!!
                centerX = GetCircumCenterX(thisV.x, thisV.y,nextV.x, nextV.y,v[i].x, v[i].y);
                centerY = GetCircumCenterY(thisV.x, thisV.y,nextV.x, nextV.y,v[i].x, v[i].y);

                std::vector<int> tempInts;
                tempInts.push_back(i);
                tempInts.push_back(v[i].neighbors[j]);
                tempInts.push_back(v[i].neighbors[(j+1)%v[i].neighborSize]);

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

                    thisEdge = sqrt(pow(vecx,2)+ pow(vecy,2));
                    thisAng = acos((vec1x*vecx + vec1y*vecy)
                             /(sqrt(pow(vec1x,2)+pow(vec1y,2))
                               *sqrt(pow(vecx,2)+pow(vecy,2)) )  );

                    // find max and min edge
                    if(k==0){
                        minAng = thisAng;
                        ver1 = self;
                        ver2 = next;
                    }else{
                        if(thisEdge>max){
                            max = thisEdge;
                        }
                        if(thisEdge<min){
                            min = thisEdge;
                            ver1 = self;
                            ver2 = next;
                        }
                        if(thisAng < minAng)
                            minAng = thisAng;
                    }
                }

                double xTobeMove = v[i].x, yTobeMove = v[i].y;
                tempAR = max/min;


                if(minAng < 20*PI/180){

                    //cout << "min " <<minAng*PI/180 <<endl;
                   if(ver1 == i){
                        //cout << ver1 << " "<<endl;
                        double angle = -0.01;
                        double currentDist = min;
                        xTobeMove = v[ver1].x;
                        yTobeMove = v[ver1].y;

                        while(currentDist < min+0.01*max){
                            xTobeMove = movePX(xTobeMove, yTobeMove, centerX, centerY, angle);
                            yTobeMove = movePY(xTobeMove, yTobeMove, centerX, centerY, angle);
                            currentDist = sqrt(pow(xTobeMove-v[ver2].x, 2) + pow(yTobeMove-v[ver2].y, 2));
                        }

                        min = currentDist;
                    }

                    else if(ver2 == i){
                        double angle = 0.01;
                        double currentDist = min;
                        xTobeMove = v[ver2].x;
                        yTobeMove = v[ver2].y;

                        while(currentDist < min+0.01*max){
                            xTobeMove = movePX(xTobeMove, yTobeMove, centerX, centerY, angle);
                            yTobeMove = movePY(xTobeMove, yTobeMove, centerX, centerY, angle);
                            currentDist = sqrt(pow(v[ver1].x-xTobeMove, 2) + pow(v[ver1].y-yTobeMove, 2));

                        }
                    //cout << ver2 << " "<<endl;
                    }

                    double ordis = findShortestDistInStar(v, f, v[i].x, v[i].y, v[i].neighbors);
                    //cout << "v[" << i<<"] neighbors shortest dis orig: " << ordis <<endl;
                    double dis = findShortestDistInStar(v, f, xTobeMove, yTobeMove, v[i].neighbors);
                    //cout << "v[" << i<<"] neighbors shortest dis now: " << dis <<endl;
                    if(dis < ordis){
                        xTobeMove = v[i].x;
                        yTobeMove = v[i].y;
                        //cout << "Closer! Not Moving!" <<endl;
                    }


                }

                xnew += xTobeMove;
                ynew += yTobeMove;


            }

            v[i].x = xnew/v[i].neighborSize;
            v[i].y = ynew/v[i].neighborSize;

        }
    }


}


//  for each star region
//  for each neighborhood face
//  compare the two edges it connects, move to decrease the difference (on circumcircle)
//  take average

void smooth2Star(std::vector<vertex> &v, std::vector<face> &f, double ar){
    for (int i=0; i<v.size(); i++) {// for each vertex in mesh
        double xnew = 0;
        double ynew = 0;
        vertex nextV(0,0,0), thisV(0,0,0);

        if(v[i].onBound == 0){  
            for(int j= 0; j<v[i].neighborSize; j++){ // for each vertex in neihgbor face
                // get the next vertex and forms a triangle with v[i]
                thisV = v[v[i].neighbors[j]];
                nextV = v[v[i].neighbors[(j+1)%v[i].neighborSize]];


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
                tempInts.push_back(v[i].neighbors[(j+1)%v[i].neighborSize]);

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

                    thisEdge = sqrt(pow(vecx,2)+ pow(vecy,2));
                    thisAng = acos((vec1x*vecx + vec1y*vecy)
                             /(sqrt(pow(vec1x,2)+pow(vec1y,2))
                               *sqrt(pow(vecx,2)+pow(vecy,2)) )  );

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
                //cout << max << " "<< min <<endl;

                if(minAng < 20*PI/180){

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

                xnew += xTobeMove;
                ynew += yTobeMove;


            }

            v[i].x = xnew/v[i].neighborSize;
            v[i].y = ynew/v[i].neighborSize;

        }
    }


}



double GetCircumCenterX(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
    double BCx, BCy, ABx, ABy, k1, k2;
     
    BCx = ((Bx + Cx)/2.0);
    BCy = ((By + Cy)/2.0);
    ABx = ((Bx + Ax)/2.0);
    ABy = ((By + Ay)/2.0);
    k1 = (- Bx + Ax)/(By - Ay);
    k2 = (- Cx + Bx)/(Cy - By);
     
    if(By == Ay)
        return ABx;
    if(Cy == By)
        return BCx;
     
    return (((ABy - k1*ABx) - (BCy - k2 * BCx)) / (k2 - k1));
     
}
 
double GetCircumCenterY(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
    double BCx, BCy, ABx, ABy, k1, k2, CircumCenterX;
     
    BCx = ((Bx + Cx)/2.0);
    BCy = ((By + Cy)/2.0);
    ABx = ((Bx + Ax)/2.0);
    ABy = ((By + Ay)/2.0);
    k1 = (- Bx + Ax)/(By - Ay);
    k2 = (- Cx + Bx)/(Cy - By);
    CircumCenterX = GetCircumCenterX(Ax, Ay, Bx, By, Cx, Cy);
     
    if(By == Ay)
        return k2*ABx + BCy - k2*BCx;
    if(By == Cy)
        return k1*BCx + ABy - k1*ABx;

    return (k1 * (CircumCenterX - ABx) + ABy);
     
}
 
double movePX(double Ax, double Ay, double cenX, double cenY, double ang){
    return cenX + (Ax - cenX)*cos(ang) - (Ay - cenY)*sin(ang);
}
 
double movePY(double Ax, double Ay, double cenX, double cenY, double ang){
    return cenY + (Ax - cenX)*sin(ang) + (Ay - cenY)*cos(ang);
}






