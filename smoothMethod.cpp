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
            float weightsTotal = 0;
            for(int j= 0; j<v[i].neighborSize; j++){ // for each vertex in neihgbor face
                // get the next vertex and forms a triangle with v[i]
                thisV = v[v[i].neighbors[j]];
                nextV = v[v[i].neighbors[(j+1)%v[i].neighborSize]];

                double vecx,vecy, angle = 0.01;
                double lastEdge, nextEdge,thisEdge, tempAR, minAng, thisAng;
                int self, next;
                double centerX, centerY;
                float a;


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
                    double vec1x = -v[last].x + v[self].x;
                    double vec1y = -v[last].y + v[self].y;

                    thisEdge = sqrt(pow(vecx,2)+ pow(vecy,2));
                    thisAng = acos((vec1x*vecx + vec1y*vecy)
                             /(sqrt(pow(vec1x,2)+pow(vec1y,2))
                               *sqrt(pow(vecx,2)+pow(vecy,2)) )  );

                    // find max and min edge
                    if(k==0){
                        //minAng = thisAng;
                        lastEdge = sqrt(pow(vecx,2)+ pow(vecy,2));
                        nextEdge = sqrt(pow(vec1x,2)+ pow(vec1y,2));

                        if(lastEdge < nextEdge){
                            angle = -0.02;
                        }else{
                            angle = 0.02; 
                        }

                    }else{
                        //if(thisAng < minAng)
                            //minAng = thisAng;
                    }
                }

                double xTobeMove = v[i].x, yTobeMove = v[i].y;

                // 2 for fine 1.5 for good mesh
                a = max(lastEdge, nextEdge)/min(lastEdge, nextEdge);
                weightsTotal+=a;
                //if (  max(lastEdge, nextEdge)/min(lastEdge, nextEdge)< ar )
                //{
                    //cout <<"ratoi" <<endl;
                    //cout << max(lastEdge, nextEdge)/min(lastEdge, nextEdge) <<endl;
                //}else{

                       //double rcoeff = 1;
                        //cout << "  " << i << " " <<thisAng*180/PI  <<" pi " <<PI<<endl;
                        if(thisAng > PI/3){
                            //cout << "larger "<< v[i].x <<" " <<v[i].y<<" "<<endl;
                            //rcoeff = 0.00003*thisAng/(PI/3) + 1;
                            //cout << "larger "<< v[i].x <<" " <<v[i].y<<" "<<endl;
                            //rcoeff = thisAng/(PI/2);
                            xTobeMove = centerX + 1.00000002*(xTobeMove - centerX);
                            yTobeMove = centerY + 1.00000002*(yTobeMove - centerY);
                        }else if(thisAng < PI/3){
                            //printf("a");
                            //rcoeff = 0.99998;
                            xTobeMove = centerX + 0.99999998*(xTobeMove - centerX);
                            yTobeMove = centerY + 0.99999998*(yTobeMove - centerY);
                        }
                        xTobeMove = movePX(xTobeMove, yTobeMove, centerX, centerY, angle, 1);
                        yTobeMove = movePY(xTobeMove, yTobeMove, centerX, centerY, angle, 1);
                        
                    
                //}


                //}
                double total, t2;
                double  disToOppoEdge = lineDistPoint(thisV.x, thisV.y,nextV.x, nextV.y,v[i].x, v[i].y);
                double ordis = findShortestDistInStar(v, f, v[i].x, v[i].y, v[i].neighbors, total);
                double dis = findShortestDistInStar(v, f, xTobeMove, yTobeMove, v[i].neighbors, t2);
                if(dis < ordis){
                    xTobeMove = v[i].x;
                    yTobeMove = v[i].y;
                }
                //cout <<"    disFrac"<< disToOppoEdge/total <<endl;

                xnew += a*xTobeMove;
                ynew += a*yTobeMove;


            }

            v[i].x = xnew/weightsTotal;
            v[i].y = ynew/weightsTotal;

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
 
double movePX(double Ax, double Ay, double cenX, double cenY, double ang, double rScalar){
    return cenX + rScalar*(Ax - cenX)*cos(ang) - rScalar*(Ay - cenY)*sin(ang);
}
 
double movePY(double Ax, double Ay, double cenX, double cenY, double ang, double rScalar){
    return cenY + rScalar*(Ax - cenX)*sin(ang) + rScalar*(Ay - cenY)*cos(ang);
}






