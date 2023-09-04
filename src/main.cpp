#include <iostream>
#include <vector>
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <set>
#include "PageRank.h"
using namespace std;


int main(){
    PageRank URL;

    int numLines;
    int powerIterations;
    int from;
    int to;
    cin>>numLines>>powerIterations;
    
 
// loop through each input line and add vertices to the map
for(int i = 0; i <= numLines; i++) {
    string line;
    getline(cin, line);
    istringstream in(line);
    if(i!=0){
    string from, to;
    in >> from >> to;

    URL.addVertex(from);
    URL.addVertex(to);
    URL.addEdges(from,to);
    }
}
    URL.printAllVertex();
    URL.addAdjList();
    URL.outDegrees();
    URL.inDegrees();
    URL.calculatePageRank(powerIterations-1);
}


