#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "chilkat/include/CkSpider.h"
#include "chilkat/include/CkString.h"

class Utils {
    public:
        Utils ();
        std::string getDomain (std::string url);
        std::string formatUrl (std::string url);
        int countDepth (std::string url);

    private:
        CkSpider spider;
        std::vector<std::string> indexEndings;

};

#endif