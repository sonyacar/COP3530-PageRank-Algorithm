#include <iostream>
#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#include <set>
using namespace std;

class PageRank{
    public:
    float totalVertex;
    vector<string>vertex;
    vector<pair<string,string> > edges;
    

    set<string>uniqueVertex;

    map<string,pair<vector<string>,vector<float> > > adjList;
    map<string,float> rankOfPage;
    map<string,float> finalResult;
    map<string, float> outdegrees;
    map<string, float> indegrees;

    PageRank();
    void addVertex(string URL);
    void addEdges(string from,string to);
    void printAllVertex();
    void inDegrees();
    void outDegrees();
    void addAdjList();
    void calculatePageRank(int powerIterations);
    float getOutDegree(string vertexName);

};