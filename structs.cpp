//
//  face.cpp
//  
//
//  Created by Xuan Huang on 6/23/16.
//
//

#include "structs.h"

vertex::vertex(double a, double b, double c){
    x = a;
    y = b;
    z = c;
    onBound = 0;// 0 not onbound, 1 onbound
}



edge::edge(int a, int b){
    node1 = a;
    node2 = b;
    edgeRep = 0;
}

face::face(std::vector<int> list){
    for(int i=0; i<list.size();i++){
        listOfV.push_back(list[i]);
    }
}


int face::hasV(int v){
    for (int i=0; i<listOfV.size();i++) {
        if(listOfV[i]== v){
            return i;
        }
    }
    return -1;
}

std::string face::listToS(){
    std::string str;
    for (int i=0; i<listOfV.size();i++) {
        str += std::to_string(listOfV[i]) + " ";
    }
    return str;
}
