#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include "graph.hpp"

#define MIN_DIFF_NEEDED 0.0001
#define MAX_ITERATIONS 30
#define INITIAL_RANK 1

using namespace std;

typedef struct {
    float prev;
    float curr;
} RankNode;

float myabs (float a) {
    if (a < 0) return -1*a;
    else return a;
}

// read each line in index inserting edges on graph
void populateGraph (Graph &g, string filename) {
    ifstream finf (filename);
    string line;
    uint vertex, neighbor;
    // each index line
    while (getline(finf, line)) {
        stringstream ss (line);
        ss >> vertex;
        // each vertex to which current vertex is connected to
        while (ss >> neighbor) {
            g.insertEdge(vertex, neighbor);
        }
    }
    finf.close();
}

uint largestFromUrlList (string filename) {
    ifstream finf (filename);
    string line, url;
    uint pos, id, largest = 0;

    while (getline(finf, line)) {
        pos = line.find(" ");
        id = atof(line.substr(pos+1, line.size()-pos).c_str());
        if (id > largest) largest = id;
    }
    
    finf.close();
    return largest; // largest id found
}

void initializeRankList (vector<RankNode> &ranks) {
    for (uint i = 0; i < ranks.size(); i++) {
        ranks[i].prev = 1;
    }
}

// return new page rank value for the given vertex
float calculateNewRank (Graph g, vector<RankNode> &pageRanks, uint vertex, float dfactor) {
    float rankByInEdges = 0; // portion of rank gotten from inEdges
    float neighborRank, neighborOutEdges;
    EdgeIterator it = g.getEdgeIterator(vertex);
    
    for (; it.curr != it.end; it.curr++) {
        neighborOutEdges = g.outEdges(*it.curr);
        neighborRank = pageRanks[*it.curr].prev;
        rankByInEdges += neighborRank/neighborOutEdges;
    }

    return (1-dfactor + dfactor*rankByInEdges);
}

void calculatePageRank (Graph g, vector<RankNode> &pageRanks, float dfactor) {
    float diff, newRank;
    
    for (uint i = 0; i < MAX_ITERATIONS; i++) {
        cout << "#" << i+1 << "... ";
        cout.flush();
        
        diff = 0;
        // calculates vertex new rank
        for (uint vertex = 0; vertex < g.size(); vertex++) {
            cout << vertex << ' ';
            cout.flush();
            newRank = calculateNewRank(g, pageRanks, vertex, dfactor);
            diff += abs(pageRanks[vertex].prev - newRank);
            pageRanks[vertex].curr = newRank;
        }
        
        // update nodes with their new values
        for (uint vertex = 0; vertex < g.size(); vertex++) {
            // cout << vertex << ": " << pageRanks[vertex].prev << " -> " << pageRanks[vertex].curr << endl;
            pageRanks[vertex].prev = pageRanks[vertex].curr;
        }

        // average change
        diff /= g.size();
        printf("%.5f\n", diff);

        // if ranks have converged 
        if (diff < MIN_DIFF_NEEDED) break;
    }

}

void outputPageRanks (vector<RankNode> pageRanks, string outputPath) {
    ofstream fout (outputPath);
    for (uint i = 0; i < pageRanks.size(); i++) {
        fout << i << ' ' << pageRanks[i].prev << '\n';
    }
    fout.close();
}

string generateOutputPath (string filename) {
    string suffix = "ranks.txt";
    bool foundSlash = false;
    int i;
    // extract folders path
    for (i = filename.size()-1; i >= 0; i--) {
        if (filename[i] == '/') {
            foundSlash = true; break;
        }
    }
    if (foundSlash) {
        string prefix = filename.substr(0, i+1);
        return prefix + suffix;
    } else {
        return suffix;
    }
}

int main (int argc, char** argv) {
    if (argc < 3 or argc > 4) {
        cout << "Please provide path to the index as parameter. ";
        cout << "Optionally, provide the d factor for page rank calculation." << endl;
        exit(1);
    }

    string indexName = string(argv[1]);
    string outputPath = generateOutputPath(indexName);
    string urlName = string(argv[2]);
    float dfactor = (argc == 4) ? atof(argv[3]) : 0.85;
    
    // cout << indexName << endl;
    // cout << outputPath << endl;
    // cout << dfactor << endl;

    uint largestID = largestFromUrlList(urlName);
    cout << "Graph size: " << largestID << endl;
    Graph g (largestID + 1);
    populateGraph(g, indexName);
    vector<RankNode> pageRanks (largestID + 1);
    initializeRankList(pageRanks);
    calculatePageRank(g, pageRanks, dfactor);
    outputPageRanks(pageRanks, outputPath);
}