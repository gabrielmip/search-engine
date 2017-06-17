#include "rank_run_iterator.hpp"

using namespace std;

pair<uint, uint> RankRunIterator::nextTuple () {
    pair<uint, uint> t;
    fscanf(file, "%u,%u\n", &t.first, &t.second);
    return t;
}

void RankRunIterator::loadFile (string path) {
    if (file != NULL)
        fclose(file);

    file = fopen(path.c_str(), "r");
    if (file == NULL) {
        cerr << "Error loading file for run iterator: " << path << endl;
        exit (1);
    }
}

void RankRunIterator::close () {
    if (file != NULL)
        fclose(file);
}

bool RankRunIterator::isFileOver () {
    int c = fgetc(file);
    ungetc(c, file);
    if (c == EOF) return 1;
    else return 0;
}