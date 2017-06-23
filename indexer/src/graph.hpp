#include <iostream>
#include <vector>
#include <map>

typedef unsigned int uint;

typedef struct {
    std::vector<uint>::iterator curr;
    std::vector<uint>::iterator end;
} InEdgeIterator;

typedef struct {
    std::map<uint, std::vector<uint> >::iterator curr;
    std::map<uint, std::vector<uint> >::iterator end;
} VertexIterator;

typedef struct {
    std::map<uint, uint>::iterator curr;
    std::map<uint, uint>::iterator end;
} OutEdgeIterator;

class Graph {
public:
    void insertEdge (uint orig, uint dest);
    InEdgeIterator getInEdgeIterator (uint vertex);
    VertexIterator getVertexIterator ();
    OutEdgeIterator getOutEdgeIterator ();
    uint getOutEdgesCount (uint vertex);
    bool isVertexAlone (uint vertex);
private:
    std::map<uint, std::vector<uint> > inEdges;
    std::map<uint, uint> countOutEdges;
};