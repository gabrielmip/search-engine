#include <iostream>
#include <string>
#include <vector>

#include <dirent.h>
#include <sys/types.h>

class Utils {
    public:
        std::vector<std::string> listdir (std::string folder);
};