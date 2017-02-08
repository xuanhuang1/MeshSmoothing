//
//  main.cpp
//
//
//  Created by Xuan Huang on 6/23/16.
//
//

#include "functions.h"
#include <string.h>

using namespace std;

int main(int argc, char* argv[]){
    ifstream inputFile(argv[1]);
    
    if(!inputFile){
        cout << "Cannot open file" << endl;
        return 1;
    }
    string fileN = argv[1];

    vector<vertex> v;
    vector<edge> e;
    vector<face> f;
    
    readIn(v, e, f, fileN);

    









    /*
    for (int i=0; i<v.size(); i++) {
        cout << v[i].x << " "<< v[i].y << " "<< v[i].z << " "<< endl;
    }
    for (int i=0; i<e.size(); i++) {
        cout << e[i].node1 << " "<< e[i].node2<< endl;
    }
    cout << f.size() <<endl;*/
    ofstream outputfile;
    outputfile.open(argv[2], ios::out | ios::trunc);
    
    outputfile << "OFF" << endl;
    outputfile << v.size()<<" "<< f.size()<<" "<<e.size()<<" "<< endl;
    
    for (int i =0; i<v.size(); i++){
        outputfile << v[i].x << " " << v[i].y << " " << v[i].z <<endl;
    }
    
    for (int i =0; i<f.size(); i++){
        outputfile << f[i].listOfV.size() << " "<< f[i].listToS();
        outputfile <<"\n";
    }
    outputfile.close();
    
    return 0;
    
}
//test for class vertex
/*
 vertex v(1.3, 2);
 v.setNum(0);
 vertex v2(3,5.2);
 v2.setNum(1);
 cout << "v1 getX: " << v.getX() << " num: " << v.getNum() << endl;
 cout << "v1 getY: " << v.getY() << endl;
 cout << "v2 getX: " << v2.getX() << " num: " << v2.getNum()<< endl;
 cout << "v2 getY: " << v2.getY() << endl;
 */

//test for class face
/*
 vector<int> list;
 list.push_back(1);
 list.push_back(8);
 list.push_back(10);
 list.push_back(12);
 list.push_back(7);
 face f(list);
 
 cout << "face v number: " << f.getList().size() <<endl;
 for (int i =0; i<f.getList().size(); i++) {
 cout << "face v :" << f.getList()[i] << endl;
 }
 
 //test for read v, e, f
 for (int i =0; i<v.size(); i++)
 cout << v[i].getX() << " " << v[i].getY() << " " << v[i].getZ() <<endl;
 
 for (int i =0; i<f.size(); i++){
 for (int j =0; j<f[i].getList().size(); j++)
 cout << f[i].getList()[j] << " ";
 cout <<"\n";
 }
 
 for (int i =0; i<e.size(); i++)
 cout << e[i].get1() << " " << e[i].get2() <<endl;
 */

//test for read v, e, f
/*for (int i =0; i<v.size(); i++){
 if (v[i].ifBound() == 1) {
 cout << " vertice on bound" <<endl;
 }
 cout << v[i].getX() << " " << v[i].getY() << " " << v[i].getZ() <<endl;
 }
 
 for (int i =0; i<f.size(); i++){
 for (int j =0; j<f[i].getList().size(); j++)
 cout << f[i].getList()[j] << " ";
 cout <<"\n";
 }
 
 for (int i =0; i<e.size(); i++)
 cout << e[i].get1() << " " << e[i].get2() <<endl;
 */
