#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>

#include <html/ParserDom.h>
#include "utils.hpp"
#include "file_iterator.hpp"

typedef struct {
    int term;
    int doc;
    int freq;
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
    void indexPage (std::string raw);
    std::map<std::string, int> vocabulary;
    std::map<std::string, int> urlCodes;
    std::vector<Tuple> cachedTuples;
};