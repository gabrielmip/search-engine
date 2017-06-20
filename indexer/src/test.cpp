#include <iostream>
#include <string>
#include <vector>
#include "utils.hpp"
#include "run_iterator.hpp"
#include "file_iterator.hpp"

using namespace std;

void tutils () {
    Utils u;
    vector<string> dirs = u.listdir("../src/");
    for (int i = 0; i < dirs.size(); i++) {
        cout << dirs[i] << endl;
    }
    vector<string> terms;
    terms.push_back("blaáBlaASDç");
    terms.push_back("a");
    terms.push_back("paá");
    terms.push_back("como");
    terms.push_back("assim");
    terms.push_back("vem");

    for (int i = 0; i<terms.size(); i++) {
        cout << u.isStopWord(terms[i]) << endl;
    }
    cout << endl << endl;
    for (int i = 0; i<terms.size(); i++) {
        cout << u.cleanTerm(terms[i]) << endl;
    }
}

void tfileiter () {
    FileIterator r;
    r.loadFile("../data/docs/0.txt");
    string page, url;
    while (!r.isFileOver()) {
        page = r.nextPage();
        if (page.size() == 0) continue;
        url = r.getUrl();

        cout << page <<endl<<url<<endl;
    }
}

int main () {
    tfileiter();
}