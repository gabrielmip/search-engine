#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>
#include "chilkat/include/CkSpider.h"
#include "chilkat/include/CkString.h"

class Utils {
    public:
        Utils ();
        std::string getDomain (std::string url);
        std::string formatUrl (std::string url);
        int countDepth (std::string url);
        void log (std::string url);
        void setLogPath (std::string logPath);
        void dumpLog ();

    private:
        CkSpider spider;
        std::vector<std::string> indexEndings;
        std::vector<std::pair<std::string, std::time_t> > crawlingLog;
        std::string path;

};

#endif