#include <cstdio>
#include <iostream>
#include <string>

class FileIterator {
public: 
    std::string getUrl ();
    std::string nextPage ();
    void loadFile (std::string path);
    bool isFileOver ();

private:
    std::string url;
    FILE *file = NULL;
};
