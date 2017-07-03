#include <iostream>
#include <vector>
#include <unordered_map>

typedef unsigned int uint;

typedef struct {
    std::vector<uint>::iterator curr;
    std::vector<uint>::iterator end;
} EdgeIterator;

class Graph {
public:
    Graph (uint size);
    void insertEdge (uint orig, uint dest);
    EdgeIterator getEdgeIterator (uint vertex);
    uint outEdges (uint vertex);
    uint size ();
private:
    std::vector<std::vector<uint> > inedges;
    std::vector<uint> outedges;
};