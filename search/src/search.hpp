#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
// #include "anchor_index.hpp"
#include "unigram_index.hpp"

class SearchEngine {
public:
    // void initAnchorIndex (std::string indexPath, std::string vocabPath);
    void initUnigramIndex (std::string indexPath, std::string vocabPath, std::string urlPath);
    std::vector<std::string> search (std::string query);
private:
    // AnchorIndex *anchor;
    UnigramIndex *unigram;
    Utils u;
};
