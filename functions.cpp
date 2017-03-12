//
//  functions.cpp
//
//
//  Created by Xuan Huang on 6/28/16.
//
//

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int readIn(vector<vertex> &v,vector<edge> &e,vector<face> &f, string filename){

    ifstream inputFile(filename);
    
    if(!inputFile){
        cout << "Cannot open file" << endl;
        return 1;
    }

    
    string str;
    int line = 0;

    while(getline(inputFile, str)){
        int nofV, nofE, nofF;

        // read the first line
        if(line == 0){  
            if(str != "OFF"){
                cout << "Not An OFF File!" <<endl;
                exit(0);
            }
        // read numbers of v f e
        }else if(line == 1){   
            stringstream ss(str);
            ss >> nofV >> nofF >> nofE;
        // read vertices
        }else if(line < 1+nofV +1){   
            double x,y,z;
            stringstream ss(str);
            ss >>x>>y >>z;
            vertex temp = vertex(x,y,z);
            v.push_back(vertex(x,y,z));
        // read faces
        }else if(line < 1+nofV+nofF +1){   
            int numOfVerOnFace, thisVertexIndex;
            std::vector<int> verticesIndexThisFace;
            stringstream ss(str);
            ss >> numOfVerOnFace;
            // read edges
            for(int i=0; i<numOfVerOnFace; i++){
                ss >> thisVertexIndex;
                verticesIndexThisFace.push_back(thisVertexIndex);
                if(i >0){   
                    edge eTemp(verticesIndexThisFace[i-1], verticesIndexThisFace[i]);
                    for (int j =0; j<e.size(); j++) {
                        if( (e[j].node1== verticesIndexThisFace[i-1]&&e[j].node2== verticesIndexThisFace[i])
                            || (e[j].node2== verticesIndexThisFace[i-1]&&e[j].node1== verticesIndexThisFace[i]) ){
                            e[j].edgeRep++;
                            eTemp.edgeRep++;
                        }
                    }
                    if(eTemp.edgeRep == 0)
                        e.push_back(eTemp);
                }
            }
            // add the tail with head - the last edge in list
            edge eTemp(verticesIndexThisFace[numOfVerOnFace-1],verticesIndexThisFace[0]);
            for (int j =0; j<e.size(); j++) {
                if( (e[j].node1== verticesIndexThisFace[numOfVerOnFace-1]&&e[j].node2== verticesIndexThisFace[0]) 
                    || (e[j].node2== verticesIndexThisFace[numOfVerOnFace-1]&&e[j].node1== verticesIndexThisFace[0])){
                    e[j].edgeRep++;
                    eTemp.edgeRep++;
                }
            }
            if(eTemp.edgeRep == 0)
                e.push_back(eTemp);

            //for each vertex in face
            for (int j =0; j<verticesIndexThisFace.size(); j++) {
                // add everything else after than vertex, in circular manner
                for(int p = 0; p<numOfVerOnFace-1; p++){
                    v[verticesIndexThisFace[j]].neighbors.push_back(verticesIndexThisFace[(j+p+1)%numOfVerOnFace]);
                }

                v[verticesIndexThisFace[j]].neighborSize += 1;
                //cout <<verticesIndexThisFace[j] << " size: " << v[verticesIndexThisFace[j]].neighborSize <<endl;
                //check neighbor
                /*cout << verticesIndexThisFace[j] << " :";
                for(int p = 0; p<v[verticesIndexThisFace[j]].neighbors.size(); p++){
                    cout << v[verticesIndexThisFace[j]].neighbors[p] << " ";
                }
                cout <<endl;*/
            }
            face tempF = face(verticesIndexThisFace);
            
            f.push_back(tempF);
        }

        line++;
        
    }

    cout << "endofwhileread" <<endl;

    // mark the boundary vertices
    for (int i=0; i<e.size(); i++) {
        if (e[i].edgeRep == 0) {
            v[e[i].node1].onBound = 1;
            v[e[i].node2].onBound = 1;
            //cout << e[i].node1 << " " <<e[i].node2<<endl;
        }
    }

    cout << "endofboundary check" <<endl;

    // clear out format of neighbor faces
    for (int i=0; i<v.size(); i++) {
        if(v[i].onBound == 0){
            vector<int> neighborTemp;
            //cout << "v[i].neighborSize" << v[i].neighborSize<<endl;
            if(v[i].neighborSize == 0)
                cout << i<<endl;
            int numofelements = v[i].neighbors.size()/v[i].neighborSize;
            int j = numofelements;

            for(int k = 0; k< numofelements; k++)
                neighborTemp.push_back(v[i].neighbors[k]);

            while (neighborTemp.size() < v[i].neighborSize*(numofelements -1)){
                if(v[i].neighbors[j] == neighborTemp.back()){
                    for(int k = 0; k< numofelements-1; k++){
                        if(v[i].neighbors[j+k+1] != neighborTemp[0])
                            neighborTemp.push_back(v[i].neighbors[j+k+1]);
                    }
                }
                j += numofelements;
                j = j%(v[i].neighbors.size());
            }
            v[i].neighbors = neighborTemp;

            //for(int p = 0; p<v[i].neighbors.size(); p++)   
                //cout << v[i].neighbors[p] <<" ";
            //cout <<"endiput"<< endl;
        }
    }

    cout <<"endiput"<< endl;



    return 1;
}


void maxminAng(vector<vertex> &v, vector<face> &f, double &max, double &min){
    double angleTemp = 20.123456;
    double vec1x, vec1y, vec2x, vec2y;
    for (int i=0; i<f.size(); ++i) { // for each face
        for (int j=0; j<f[i].listOfV.size(); ++j) { // for each vertex in this face, there is an angle
            int last, self, next;
            self = f[i].listOfV[j];
            if (j == 0) {
                last = f[i].listOfV[f[i].listOfV.size()-1];
                next = f[i].listOfV[j+1];
            }else if(j==f[i].listOfV.size()-1){
                last = f[i].listOfV[j-1];
                next = f[i].listOfV[0];
            }else{
                last = f[i].listOfV[j-1];
                next = f[i].listOfV[j+1];
            }
            vec1x = v[last].x - v[self].x;
            vec1y = v[last].y - v[self].y;
            vec2x = v[next].x - v[self].x;
            vec2y = v[next].y - v[self].y;
            
            angleTemp = acos((vec1x*vec2x + vec1y*vec2y)
                             /(sqrt(pow(vec1x,2)+pow(vec1y,2))
                               *sqrt(pow(vec2x,2)+pow(vec2y,2)) )  );
            
            //for test angle
            /*cout << "vec2x*vec1x + vec2y*vec1y: " << vec2x*vec1x + vec2y*vec1y << endl;
             cout << "sqrt(pow(vec1x,2)+pow(vec1y,2))*sqrt(pow(vec2x,2)+pow(vec2y,2)): " << sqrt(pow(vec1x,2)+pow(vec1y,2))*sqrt(pow(vec2x,2)+pow(vec2y,2)) << endl;
            */ 
            
            if (i==0 && j==0) {
                max = angleTemp;
                min = angleTemp;
            }else{
                if (angleTemp > max) {
                    max = angleTemp;
                }
                else if (angleTemp < min){
                    min = angleTemp;
                }
            }
        }// end of this angle
        f[i].minAng = min;
    }//end of this face
    
}
double sortByAR(face &f1, face &f2){
    return f1.aspectR > f2.aspectR;
}

double aspectR(vector<vertex> &v, vector<face> &f, double &med){
    double tempAR, finalAR;
    finalAR = 0;
    double resultVal;

    Vertex face[4];
    
    for (int i=0; i<f.size(); ++i) { // for each face
        double min, max, vecx, vecy;
        double thisEdge;
        
        for (int j = 0; j < f[i].listOfV.size(); j++) { //jacob and modified det calculate
            face[j].x = v[f[i].listOfV[j]].x;
            face[j].y = v[f[i].listOfV[j]].y;
            face[j].z = v[f[i].listOfV[j]].z;
            //cout << "j " << j<<endl;
        }
        //cout << analyze(face).jacobianDet <<endl;
        //f[i].setDet(analyze(face).jacobianDet);
        
        //worstModDet = analysis.modifiedDet;
        
        
        for (int j=0; j<f[i].listOfV.size(); ++j) { // for each vertex in this face, measure the edge it connects with the next vertex
            int self, next;
            self = f[i].listOfV[j];
            next = f[i].listOfV[(j+1)%f[i].listOfV.size()];
            
            vecx = v[next].x - v[self].x;
            vecy = v[next].y - v[self].y;
            
            thisEdge = sqrt(pow(vecx,2)+pow(vecy,2));
            
            if(j==0){
                max = thisEdge;
                min = thisEdge;
            }else{
                if (thisEdge>max) {
                    max = thisEdge;
                }
                if (thisEdge<min) {
                    min = thisEdge;
                }
            }
        }// end of all edges in the face
        tempAR = max/min;
        //cout << "tempAR "<<tempAR<<endl;
        
        //set aspect ratio in each face
        f[i].aspectR = tempAR;
        
        if(finalAR < tempAR){
            finalAR = tempAR;
        }
    }//end of all faces
    
    sort(f.begin(), f.end(), sortByAR);    // !!!!! change here for sorting type!!!!
    
    med = f[2*f.size()/3].aspectR;
    
    return finalAR;
}

double lineDistPoint(double x1, double y1, double x2, double y2,double px, double py){
    double vxLine = x2 - x1;
    double vyLine = y2 - y1;
    double vxPointToEnd = px - x1;
    double vyPointToEnd = py - y1;

    double dis = abs(vxLine * vyPointToEnd - vyLine * vxPointToEnd) / sqrt(vxLine * vxLine + vyLine * vyLine);
    return dis;

}

double findShortestDistInStar(vector<vertex> &v, vector<face> &f, double theX, double theY, std::vector<int> nbrs){
    double distFinal, distTemp = 0;
    for (int i = 0; i < nbrs.size(); ++i)
    {
        vertex a = v[nbrs[(i)%nbrs.size()]];
        vertex b = v[nbrs[(i+1)%nbrs.size()]];

        distTemp =  lineDistPoint(a.x, a.y, b.x, b.y, theX, theY);

        if(i == 0)
            distFinal = distTemp;
        if(distFinal > distTemp)
            distFinal = distTemp;
    }

    return distFinal;
}

CREAnalysis analyze(Vertex vertices[4]) {
    
    CREAnalysis result;
    Vertex centroid;
    Vertex midpoint[4];
    int j;
    Vertex v06, v07;
    double v06Length;
    Vertex localX, localY, localZ;
    Vertex v06xv07; //V06 cross with V07
    Vertex v0[4];
    Vertex localCoord[4];
    double e1, e2, e3, e4, f1, f2, f3, f4;
    
    double thisAR = 0.0;
    double worstAR = 1.0;
    
    
    centroid.x = 0.25 * (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x);
    centroid.y = 0.25 * (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y);
    
    //if (DEBUG) printf("centroid.x: %lf\t centroid.y: %lf\n", centroid.x, centroid.y);
    
    for (j=0; j<4; j++) {
        midpoint[j].x = 0.5 * (vertices[j].x + vertices[(j+1)%4].x);
        midpoint[j].y = 0.5 * (vertices[j].y + vertices[(j+1)%4].y);
        //if (DEBUG) printf("midpt[%d]: (%lf, %lf)\n", j, midpoint[j].x, midpoint[j].y);
    }
    
    v06.x = midpoint[1].x - centroid.x;
    v06.y = midpoint[1].y - centroid.y;
    v06Length = sqrt(pow(v06.x, 2) + pow(v06.y, 2));
    
    //if (DEBUG) printf("v06: (%lf, %lf)\n", v06.x, v06.y);
    
    localX.x = v06.x/v06Length;
    localX.y = v06.y/v06Length;
    
    //if (DEBUG) printf("localX: (%lf, %lf)\n", localX.x, localX.y);
    
    v07.x = midpoint[2].x - centroid.x;
    v07.y = midpoint[2].y - centroid.y;
    
    v06xv07.x = 0;
    v06xv07.y = 0;
    v06xv07.z = (v06.x * v07.y) + (v06.y * v07.x);
    
    localZ.z = 1;
    
    localY.x = -localX.y;
    localY.y = localX.x;
    
    //if (DEBUG) printf("localY: (%lf, %lf)\n", localY.x, localY.y);
    
    for (j=0; j<4; j++) {
        v0[j].x = vertices[j].x - centroid.x;
        v0[j].y = vertices[j].y - centroid.y;
        
        /*if (DEBUG) {
            printf("v0%dx: %lf, v0%dy: %lf\n", j+1, v0[j].x, j+1, v0[j].y);
            printf("v0%dx * localX.x: %lf\n", j+1, v0[j].x * localX.x);
            printf("v0%dy * localX.y: %lf\n", j+1, v0[j].y * localX.y);
        }*/
        
        localCoord[j].x = (v0[j].x * localX.x) + (v0[j].y * localX.y);
        localCoord[j].y = (v0[j].x * localY.x) + (v0[j].y * localY.y);
    }
    
    e1 = 0.25 * (localCoord[0].x + localCoord[1].x + localCoord[2].x + localCoord[3].x);
    e2 = 0.25 * (-localCoord[0].x + localCoord[1].x + localCoord[2].x - localCoord[3].x);
    e3 = 0.25 * (-localCoord[0].x - localCoord[1].x + localCoord[2].x + localCoord[3].x);
    e4 = 0.25 * (localCoord[0].x - localCoord[1].x + localCoord[2].x - localCoord[3].x);
    
    f1 = 0.25 * (localCoord[0].y + localCoord[1].y + localCoord[2].y + localCoord[3].y);
    f2 = 0.25 * (-localCoord[0].y + localCoord[1].y + localCoord[2].y - localCoord[3].y);
    f3 = 0.25 * (-localCoord[0].y - localCoord[1].y + localCoord[2].y + localCoord[3].y);
    f4 = 0.25 * (localCoord[0].y - localCoord[1].y + localCoord[2].y - localCoord[3].y);
    
    /*if (DEBUG) {
        for (j=0; j<4;j++) {
            printf("x%d:%lf y%d:%lf\n", j, localCoord[j].x, j, localCoord[j].y);
        }
    }*/
    
    //if (DEBUG) printf("e2:%lf\te3:%lf\tf2:%lf\tf3:%lf\n", e2, e3, f2, f3);
    //printf("e2/f3:%lf\tf3/e2:%lf\n", e2/f3, f3/e2);
    //printf("e3/f3:%lf\tf2/e2:%lf\n", e3/f3, f2/e2);
    
    if (e2/f3 > f3/e2) result.AR = e2/f3;
    else result.AR = f3/e2;
    
    result.skew = e3/f3;
    result.taperX = f4/f3;
    result.taperY = e4/e2;
    result.jacobianDet = pow(f3, 2) * result.AR * (1 + (result.taperX) + (result.taperY - (result.taperX *(result.skew/result.AR))));
    result.modifiedDet = result.AR * (1 + fabs(result.taperX) + (fabs(result.taperY) - (fabs(result.taperX) *(result.skew/result.AR))));
    
    return result;
    //printf("holy shit this worked %lf", v06.x);
}


