#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>
#include <algorithm>

#include <html/ParserDom.h>
#include "utils.hpp"
#include "file_iterator.hpp"

typedef struct {
    int term;
    int doc;
    std::vector<int> pos;
} Tuple;

class Indexer {
public:
    Indexer (std::string raw, std::string merge, std::string out);
    void run ();
    std::vector<std::string> tokenize (std::string page);

private:
    std::string rawfolder;
    std::string mergefolder;
    std::string outpath;
    std::vector<std::string> rawfiles;
    Utils u;
    std::string cleanHtml (std::string raw);
    void indexPage (std::string raw, std::string url);
    std::map<std::string, int> vocabulary;
    std::map<std::string, int> urlCodes;
    std::vector<Tuple> cachedTuples;
    int getUrlCode (std::string url);
    int getTermCode (std::string term);
    void addTuple (int term, int doc, std::vector<int> pos);
    void dumpTuples ();
    void mergeDump ();
    int MAX_NUM_TUPLES;
    int runCount;
};