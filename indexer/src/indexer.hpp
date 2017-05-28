#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <queue>

#include <html/ParserDom.h>
#include "utils.hpp"
#include "file_iterator.hpp"
#include "run_iterator.hpp"

typedef unsigned int uint;

class Indexer {
public:
    Indexer (std::string raw, std::string runs, std::string merge, std::string out, int memory);
    void run ();
    std::vector<std::string> tokenize (std::string page);

private:
    std::string rawfolder;
    std::string runfolder;
    std::string mergefolder;
    std::string outpath;
    std::vector<std::string> rawfiles;
    Utils u;
    std::string cleanHtml (std::string raw);
    void indexPage (std::string raw, std::string url);
    std::map<std::string, uint> vocabulary;
    std::map<std::string, uint> urlCodes;
    std::vector<Tuple> cachedTuples;
    uint getUrlCode (std::string url);
    uint getTermCode (std::string term);
    void addTuple (uint term, uint doc, std::vector<uint> pos);
    void dumpTuples ();
    std::string mergeRuns (std::string folder,std::string otherFolder);
    void outputIndex (std::string folder);
    int MAX_NUM_TUPLES;
    int runCount;
};