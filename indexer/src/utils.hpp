#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <dirent.h>
#include <sys/types.h>

class Utils {
    public:
        Utils ();
        std::vector<std::string> listdir (std::string folder);
        std::string cleanTerm (std::string term);
        bool isStopWord (std::string);
    private:
        std::unordered_set<std::string> stopWords;
        std::map<char, char> accents;
        // std::map<char, char> accentReplacementes;
};