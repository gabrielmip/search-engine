#include "utils.hpp"

using namespace std;

int main (int argc, char **argv) {
    Utils u;
    vector<string> files = u.listdir(argv[1]);
    for (string file : files) {
        cout << file << endl;
    }
}