#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include "utils.hpp"

typedef unsigned long long ull;

class UnigramIndex {
public:
    UnigramIndex (std::string indexPath, std::string vocabPath, std::string urlPath);
    std::vector<std::pair<std::string, float> > query (std::vector<std::string> terms);
    void populateVectors (std::map<uint, std::vector<float> > &vecs, uint termIndex, uint querySize);
    void initVocabulary (std::string path);
    void initUrl (std::string urlPath);
    bool termNotFound (std::string term);
private:
    FILE *index;
    std::map<std::string, ull> positions; // maps terms to positions at index file
    map<uint, std::string> urls;
};