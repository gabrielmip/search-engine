#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned int uint;

typedef struct {
    uint term;
    uint doc;
    std::vector<uint> pos;
} Tuple;

class RunIterator {
public: 
    Tuple nextTuple ();
    void loadFile (std::string path);
    bool isFileOver ();
    void close ();

private:
    FILE *file = NULL;
};
