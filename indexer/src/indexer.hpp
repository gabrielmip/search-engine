#include <iostream>
#include <string>
#include <vector>
#include "utils.hpp"
#include "file_iterator.hpp"

class Indexer {
public:
    Indexer (std::string raw, std::string merge, std::string out);

private:
    std::string rawfolder;
    std::string mergefolder;
    std::string outpath;
    std::vector<std::string> rawfiles;
    Utils u;
    FileIterator it;
}