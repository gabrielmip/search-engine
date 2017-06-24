#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <dirent.h>
#include <sys/types.h>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>

class Utils {
    public:
        Utils ();
        std::vector<std::string> listdir (std::string folder);
        std::string cleanTerm (std::string term);
        bool isStopWord (std::string);
        std::string toUTF8 (std::string raw);
        std::vector<std::string> tokenize (std::string page);

    private:
        std::unordered_set<std::string> stopWords;
        Transliterator *accentsConverter;
        
};
