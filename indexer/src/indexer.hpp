#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <queue>

#include <html/ParserDom.h>
#include "utils.hpp"
#include "file_iterator.hpp"
#include "run_iterator.hpp"
#include "rank_run_iterator.hpp"

typedef unsigned int uint;

class Indexer {
public:
    Indexer (std::string raw, std::string runs, std::string merge, std::string out, int memory, std::string log);
    void run ();
    std::vector<std::string> tokenize (std::string page);

private:
    std::string rawfolder;
    std::string runfolder;
    std::string mergefolder;
    std::string outpath;
    std::vector<std::string> rawfiles;
    Utils u;
    void indexPage (std::string raw, std::string url);
    
    // tuples
    std::vector<Tuple> cachedTuples;
    std::vector<std::pair<uint, uint> > cachedAnchorTuples;
    std::vector<std::pair<uint, uint> > cachedLinks;
    
    // url codes
    std::map<std::string, uint> urlCodes;
    std::map<std::string, uint> pageRankUrlCodes;
    uint getUrlCode (std::string url, std::map<std::string, uint> &m);

    // vocab
    std::map<std::string, uint> vocabulary;
    std::map<std::string, uint> anchorVocabulary;
    uint getTermCode (std::string term, std::map<std::string, uint> &m);
    
    // manage cache
    void addTuple (uint term, uint doc, std::vector<uint> pos);
    void cacheLink (uint origin, uint dest);
    void cacheAnchorTerm (uint dest, uint term);
    void dumpTuples ();

    void mergeRuns (std::string folder,std::string otherFolder);
    void mergePageRankRuns (std::string folder,std::string otherFolder);
    void outputIndex (std::string folder);
    void outputPageRank (std::string folder);
    void outputAnchorText (std::string folder);
    uint MAX_MEM_USAGE;
    uint memoryUsed;
    int runCount;
    FILE *logFile;
    void log (uint indexed, int type);
};