#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "chilkat/include/CkSpider.h"
#include "chilkat/include/CkString.h"

class Utils {
    public:
        std::string extractUrlDomain (std::string url);

    private:
        CkSpider spider;

};

#endif