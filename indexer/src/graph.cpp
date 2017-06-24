#include "graph.hpp"

using namespace std;

Graph::Graph (uint size) {
    inedges.resize(size);
    outedges.resize(size);
}

void Graph::insertEdge (uint orig, uint dest) {
    inedges[dest].push_back(orig);
    outedges[orig]++;
}

EdgeIterator Graph::getEdgeIterator (uint vertex) {
    EdgeIterator it;
    it.curr = inedges[vertex].begin();
    it.end = inedges[vertex].end();
    return it;
}

uint Graph::outEdges (uint vertex) {
    return outedges[vertex];
}

uint Graph::size () {
    return inedges.size();
}