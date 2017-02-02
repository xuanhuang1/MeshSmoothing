//
//  functions.cpp
//
//
//  Created by Xuan Huang on 6/28/16.
//
//

#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>






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


