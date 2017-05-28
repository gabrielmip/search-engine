#include "run_iterator.hpp"

using namespace std;

Tuple RunIterator::nextTuple () {
    Tuple t;
    char c = 42; // whatever
    int i, tf;
    fscanf(file, "%d,%d,%d,", &t.term, &t.doc, &tf);
    while (c != '\n') {
        fscanf(file, "%d", &i);
        t.pos.push_back(i);
        c = fgetc(file);
    }
    return t;
}

void RunIterator::loadFile (string path) {
    if (file != NULL)
        fclose(file);

    file = fopen(path.c_str(), "r");
    if (file == NULL) {
        cerr << "Error loading file for run iterator: " << path << '.' << endl;
        exit (1);
    }
}

bool RunIterator::isFileOver () {
    int c = fgetc(file);
    ungetc(c, file);
    if (c == EOF) return 1;
    else return 0;
}