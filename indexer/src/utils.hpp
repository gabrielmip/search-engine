#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include <dirent.h>
#include <sys/types.h>

class Utils {
    public:
        Utils ();
        std::vector<std::string> listdir (std::string folder);
        std::string cleanTerm (std::string term);
        // std::map<char, char> accentReplacementes;
};