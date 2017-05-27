#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

typedef struct {
    int term;
    int doc;
    std::vector<int> pos;
} Tuple;

class RunIterator {
public: 
    Tuple nextTuple ();
    void loadFile (std::string path);
    bool isFileOver ();

private:
    FILE *file = NULL;
};
