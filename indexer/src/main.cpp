#include "utils.hpp"
#include "file_iterator.hpp"

using namespace std;

int main (int argc, char **argv) {
    Utils u;
    vector<string> files = u.listdir(argv[1]);
    for (string file : files) {
        cout << file << endl;
    }

    cout << endl << endl;
    cout << "Teste com FileIterator" << endl;
    FileIterator fi;
    string path = "teste.txt";
    fi.loadFile(path);
    string page = fi.nextPage();
    cout << fi.getUrl() << endl;
    cout << page << endl;
    page = fi.nextPage();
    cout << fi.getUrl() << endl;
    cout << page << endl;

    
}