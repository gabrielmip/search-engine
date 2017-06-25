#include "search.hpp"

using namespace std;

void SearchEngine::initAnchorIndex (string indexPath, string vocabPath) {

}

void SearchEngine::initUnigramIndex (string indexPath, string vocabPath, string urlPath) {
    unigram = new UnigramIndex(indexPath, vocabPath, urlPath);
}

void SearchEngine::search (string raw) {
    vector<string> query;
    
    string processed = u.cleanTerm(raw);
    vector<string> tokens = u.tokenize(processed);
    for (int i = 0; i < tokens.size(); i++) {
        if (u.isStopWord(tokens[i])) continue;
        query.push_back(tokens[i]);
    }

    vector<string> unigramResults = unigram->query(query);
    for (int i = 0; i < 5 && i < unigramResults.size(); i++) {
        cout << unigramResults[i] << endl;
    }
    return unigramResults;
}

int main (int argc, char **argv) {
    string indexPath = argv[1];
    string vocabPath = argv[2];
    string urlPath = argv[3];
    string query;
    SearchEngine se;
    se.initUnigramIndex(indexPath, vocabPath, urlPath);
    vector<string> results;
    
    while (true) {
        cout << "\nEnter search query: ";
        getline(cin, query);
        results = se.search(query);

        if (results.size() > 0) {
            cout << "Results:\n\n";
        }

        for (int i = 0; i < 5 && i < results.size(); i++) {
            cout << "> " << results[i] << endl;
        }
        
        cout << "\n---------------------------------\n";
    }
}

