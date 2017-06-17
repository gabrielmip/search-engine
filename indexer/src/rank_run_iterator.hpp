#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned int uint;

class RankRunIterator {
public: 
    std::pair<uint, uint> nextTuple ();
    void loadFile (std::string path);
    bool isFileOver ();
    void close ();

private:
    FILE *file = NULL;
};
