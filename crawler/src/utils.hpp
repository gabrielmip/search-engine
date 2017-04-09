#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>
#include "chilkat/include/CkSpider.h"
#include "chilkat/include/CkString.h"

class Utils {
    public:
        std::string getDomain (std::string url);
        int countDepth (std::string url);

    private:
        CkSpider spider;

};

#endif