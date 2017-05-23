#include "indexer.hpp"

using namespace std;

Indexer::Indexer (string raw, string merge, string out) {
    rawfolder = raw;
    mergefolder = merge;
    outpath = out;
    rawfiles = u.listdir(raw);
}

int main (int argc, char **argv) {
    if (argc != 4) {
        cerr << "Few arguments." << endl;
        exit(1);
    }

    string rawFolder = argv[1];
    string mergeFolder = argv[2];
    string outputPath = argv[3];
    Utils u;

    vector<string> rawfiles = u.listdir(rawFolder);
    cout << rawfiles.size() << endl;

}