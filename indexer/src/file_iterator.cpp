#include "file_iterator.hpp"

using namespace std;

string FileIterator::getUrl () {
    return url;
}

string FileIterator::nextPage () {
    string newUrl;
    string newPage;
    char c;
    // reads from file until end of url
    while (!feof(file)) {
        c = fgetc(file);
        if (c == '|') break;
        if (c != ' ') {
            newUrl += c;
        }
    }
    url = newUrl;
    // reads page
    while (!feof(file)) {
        c = fgetc(file);
        if (c == '|') { // end of page, skips the other two pipes
            fscanf(file, "%c%c", &c, &c);
            break;
        } else {
            newPage += c;
        }
    }
    return newPage;
}

void FileIterator::loadFile (string path) {
    char c;
    
    if (file != NULL)
        fclose(file);

    file = fopen(path.c_str(), "r");
    if (file == NULL) {
        cerr << "Error trying to open file " << path << '.' << endl;
        exit (1);
    } else {
        // skipping the first pipes
        while (fscanf(file, "%c", &c) == 1) {
            if (c == '|') {
                // skipping the other 2 pipes
                fscanf(file, "%c%c", &c, &c);
                break;
            }
        }
    }
}