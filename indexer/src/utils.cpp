#include "utils.hpp"

using namespace std;

vector<string> Utils::listdir (string folder) {
    vector<string> files;

    // open dir
    DIR *dp = opendir(folder.c_str());
    if (dp == NULL) {
        cerr << "\nCannot open directory " << folder << '\n';
        exit(1);
    }

    string name;
    struct dirent *dptr = readdir(dp);
    while (dptr != NULL) {
        name = dptr->d_name;
        // hidden files, current folder and parent folder
        if (name[0] != '.' && name != "..") {
            files.push_back(name);
        }
        dptr = readdir(dp);
    }

    closedir(dp);
    return files;
}

