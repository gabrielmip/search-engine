#include "graph.hpp"

using namespace std;

InEdgeIterator Graph::getInEdgeIterator (uint vertex) {
    InEdgeIterator iter;
    iter.curr = inEdges[vertex].begin();
    iter.end = inEdges[vertex].end();
    return iter;
}

// quase bom :)
VertexIterator Graph::getVertexIterator () {
    VertexIterator iter;
    iter.curr = inEdges.begin();
    iter.end = inEdges.end();
    return iter;
}

OutEdgeIterator Graph::getOutEdgeIterator () {
    OutEdgeIterator it;
    it.curr = countOutEdges.begin();
    it.end = countOutEdges.end();
    return it;
}

void Graph::insertEdge (uint orig, uint dest) {
    countOutEdges[orig]++;
    inEdges[dest].push_back(orig);
}

uint Graph::getOutEdgesCount (uint vertex) {
    return countOutEdges[vertex];
}

bool Graph::isVertexAlone (uint vertex) {
    map<uint, vector<uint> >::iterator it = inEdges.find(vertex);
    if (it == inEdges.end()) return true;
    return false;
}