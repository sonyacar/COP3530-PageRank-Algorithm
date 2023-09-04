#include "PageRank.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <iterator>


using namespace std;

PageRank::PageRank(){ }

void PageRank::addVertex(string URL)
{
    //make sure the vertex are unique and no duplicates, if so add it
    if (uniqueVertex.insert(URL).second) 
    {
            vertex.push_back(URL);
            //creates an adjacency list formatted as vertex(from) -> [to,outdegree of to]
            adjList[URL]=make_pair(vector<string>(),vector<float>());
    
            //initialize the outdegree of the vertex as 0
            outdegrees[URL]=0;
    }
    
   
}

void PageRank::printAllVertex()
{
    float totalVertex=0.00;
    for (const auto& v : vertex) 
    {
        totalVertex++;
    }
    //used later for the r0 vector of 1/total vertex to muliply by the adjList
    this->totalVertex=totalVertex;
}

void PageRank::addEdges(string from,string to)
{
    //first checks if the vertex are in the list and exisits 
    bool fromExists = (find(vertex.begin(), vertex.end(), from) != vertex.end());
    bool toExists = (find(vertex.begin(), vertex.end(), to) != vertex.end());
    //if they exisits then create edges
     if (fromExists && toExists) 
     {
        //adds to edge vector of (from vertex, to vertex)
        edges.push_back(make_pair(from,to));
        //increase the outdegree at the vertex and store in vector
        outdegrees[from]++;

     }
}

void PageRank::addAdjList()
{
    //after all the edges and vertices are added create the adj list
    vector<pair<string,string> >::iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    //for (auto const& edge : edges) 
    {
        string from = it->first;
        string to = it->second;
        // Add the edge to the adjacency list
        adjList[to].first.push_back(from);
        adjList[to].second.push_back(1.0/getOutDegree(from));

    }
}

void PageRank::outDegrees()
{
    map<string,pair<vector<string>,vector<float> > >::iterator it;
    for(it = adjList.begin(); it != adjList.end(); it++)
    {
        int outdegree = it->second.first.size();
        float pageRank= 1.0/totalVertex;
        outdegrees[it->first] = outdegree;
        rankOfPage[it->first]=pageRank;
    }
}



float PageRank::getOutDegree(string vertexName)
{
    map<string, float> ::iterator it;
    for(it = outdegrees.begin(); it != outdegrees.end(); it++)
    {
        if (it->first == vertexName)
        {
            return it->second;
        }
    }
    return 0.0; 
}


void PageRank::inDegrees()
{
     vector<pair<string,string> > ::iterator it;
    for(it = edges.begin(); it != edges.end(); it++)
    {
        indegrees[it->second]++;
    }
}

void PageRank::calculatePageRank(int powerIterations){
    while(powerIterations>0)
    {
        //iterate through the whole adjacencey list row by row
        map<string,pair<vector<string>,vector<float> > >::iterator it;
        for(it = adjList.begin(); it != adjList.end(); it++)
        {
            float result=0.0;
            string adjFirstVertex=it->first;
            //iterate through the adjacency list by vector first pair column by column
            for(int i=0; i<it->second.first.size();i++)
            {
                //adjList: <adjFirstVertex,<adjSecondVertex,adjNumber> >
                string adjSecondVertex=it->second.first[i];
                float& adjNumber=it->second.second[i];

                map<string,float> ::iterator it3;
                //iterate through the rankOfPage to find the same vertices to multiply
                for(it3 = rankOfPage.begin(); it3 != rankOfPage.end(); it3++)
                {
                    string rankName=it3->first;
                    float& rankNumber=it3->second;
                    if(adjSecondVertex==rankName)
                    {
                        result+=(rankNumber*adjNumber);
                    }
                            
                }
            }
            finalResult[adjFirstVertex]=result;
        }
        powerIterations--;
        rankOfPage=finalResult;
        finalResult.clear();
    }

    map<string,float> ::iterator it;
    for (it = rankOfPage.begin(); it != rankOfPage.end(); ++it)
    {
        cout << it->first << " " <<fixed<<setprecision(2)<< it->second << endl;
    }
    
}