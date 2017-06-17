#include "utils.hpp"

using namespace std;

Utils::Utils () {
    FILE *file = fopen("src/stopwords.txt", "r");
    char word [80];
    while (fscanf(file, "%s\n", word) == 1){
        stopWords.push_back(word);
    }
    fclose(file);
}

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

// removes accents, transforms to lower case...
string Utils::cleanTerm (string term) {
    // lower case
    transform(term.begin(), term.end(), term.begin(), ::tolower);
    return term;
}

bool Utils::isStopWord (string word) {
    for (unsigned int i = 0; i < stopWords.size(); i++){
        if (stopWords[i] == word) return true;
    }
    return false;
}

