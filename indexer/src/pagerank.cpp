#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include "graph.hpp"

#define MIN_DIFF_NEEDED 0.0001
#define MAX_ITERATIONS 30
#define INITIAL_RANK 1

using namespace std;

float abs (float a) {
    if (a < 0) return -1*a;
    else return a;
}

// read each line in index inserting edges on graph
void populateGraph (Graph &g, string filename) {
    ifstream finf (filename);
    string line;
    // stringstream ss;
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

// return new page rank value for the given vertex
float calculateNewRank (Graph g, map<uint, float> &pageRanks, uint vertex, float dfactor) {
    float rankByInEdges = 0; // portion of rank gotten from inEdges
    float neighborRank, neighborOutEdges;
    InEdgeIterator it = g.getInEdgeIterator(vertex); 
    
    for (; it.curr != it.end; it.curr++) {
        neighborOutEdges = g.getOutEdgesCount(*it.curr);
        neighborRank = pageRanks[*it.curr];
        if (neighborRank == 0) { // var unset
            neighborRank = INITIAL_RANK;
            pageRanks[*it.curr] = INITIAL_RANK;
        }
        rankByInEdges += neighborRank/neighborOutEdges;
    }

    return (1-dfactor + dfactor*rankByInEdges);
}

// initialize vertexes that no other vertex is linked to it
uint setAloneVertexes (Graph g, map<uint, float> &prevRanks, OutEdgeIterator it, float dfactor) {
    uint count = 0;
    for (; it.curr != it.end; it.curr++) {
        if (g.isVertexAlone((*it.curr).first)) {
            // as no vertex is connected to this one,
            // rank will never change, being always
            // equals to 1-dfactor
            prevRanks[(*it.curr).first] = 1-dfactor;
            count++;
        }
    }
    return count;
}

void calculatePageRank (Graph g, map<uint, float> &pageRanks, float dfactor) {
    float diff, newRank, oldRank;
    VertexIterator it = g.getVertexIterator();
    VertexIterator backup; 
    backup.curr = it.curr;
    uint nvertexes = 0;
    uint neighbor;
    map<uint, float> prevRanks; // stores previous ranks while pageRanks stores the current ones
    
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        // reset iterator and diff accumulator
        it.curr = backup.curr;
        diff = 0;
        
        cout << "Starting iteration number " << i+1 << "..." << endl;

        // updates each vertex's page rank
        for (; it.curr != it.end; it.curr++) {
            neighbor = it.curr->first;
            newRank = calculateNewRank(g, prevRanks, neighbor, dfactor);
            oldRank = prevRanks[neighbor];
            if (oldRank == 0) {
                oldRank = INITIAL_RANK;
            }
            pageRanks[neighbor] = newRank;
            diff += abs(oldRank-newRank);
            if (i==0) nvertexes++;
        }
        
        // first iteration:
        // sets all lonely wolves to 1-dfactor, as their
        // ranks are never going to change
        if (i == 0) {
            OutEdgeIterator outIter = g.getOutEdgeIterator();
            uint n = setAloneVertexes(g, prevRanks, outIter, dfactor);
            diff += n*(1-dfactor);
            nvertexes++;
        }

        // updates prevRank to be the new ranks
        it.curr = backup.curr;
        for (; it.curr != it.end; it.curr++) {
            prevRanks[(*it.curr).first] = pageRanks[(*it.curr).first];
        }

        // average change
        diff /= nvertexes;

        cout << "Done! Average change found: " << diff << endl << endl;

        // if ranks have converged 
        if (diff < MIN_DIFF_NEEDED) break;
    }

}

void outputPageRanks (map<uint, float> pageRanks, string outputPath) {
    ofstream fout (outputPath);
    map<uint, float>::iterator it;
    for (it = pageRanks.begin(); it != pageRanks.end(); it++) {
        fout << it->first << ' ' << it->second << '\n';
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
    if (argc < 2 or argc > 3) {
        cout << "Please provide path to the index as parameter. ";
        cout << "Optionally, provide the d factor for page rank calculation." << endl;
        exit(1);
    }

    string filename = string(argv[1]);
    string outputPath = generateOutputPath(filename);
    float dfactor = (argc == 3) ? atof(argv[2]) : 0.85;
    
    cout << filename << endl;
    cout << outputPath << endl;
    cout << dfactor << endl;

    Graph g;
    map<uint, float> pageRanks;
    populateGraph(g, filename);
    calculatePageRank(g, pageRanks, dfactor);
    outputPageRanks(pageRanks, outputPath);
}