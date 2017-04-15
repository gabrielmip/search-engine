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

typedef struct {
    std::string url;
    long bytes;
    std::time_t timestamp;
} LogEntity;

class Utils {
    public:
        Utils ();
        std::string getDomain (std::string url);
        std::string formatUrl (std::string url);
        int countDepth (std::string url);
        void log (std::string url, long bytes);
        void setLogPath (std::string logPath);
        void dumpLog ();

    private:
        CkSpider spider;
        std::vector<std::string> indexEndings;
        std::vector<LogEntity> crawlingLog;
        std::string path;

};

#endif