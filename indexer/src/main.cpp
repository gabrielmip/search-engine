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
    string path = "data/teste.txt";
    fi.loadFile(path);
    string page = fi.nextPage();
    cout << fi.getUrl() << endl;
    cout << page << endl;
    page = fi.nextPage();
    cout << fi.getUrl() << endl;
    cout << page << endl;

    // wchar_t c = L'Á';
    // string s = "examplé strÍng";
    // cout << s << endl;
    // replace( s.begin(), s.end(), c, 'e');

    // c = 0xc1; 
    // printf("char: %lc encoding: %d\n", c, c);   
}