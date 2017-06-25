#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include "utils.hpp"

typedef unsigned long long ull;

class AnchorIndex {
public:
    AnchorIndex (std::string indexPath, std::string vocabPath);
    std::vector<std::pair<std::string, float> > query (std::vector<std::string> terms);
    void populateVectors (std::map<uint, std::vector<float> > &vecs, uint termIndex, uint querySize);
    void initVocabulary (std::string path);
    bool termNotFound (std::string term);
private:
    FILE *index;
    std::map<std::string, ull> positions; // maps terms to positions at index file
    map<uint, std::string> urls;
}