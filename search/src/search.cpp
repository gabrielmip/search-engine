#include "search.hpp"

using namespace std;

/*
void SearchEngine::initAnchorIndex (string indexPath, string vocabPath) {

}
*/

void SearchEngine::initUnigramIndex (string indexPath, string vocabPath, string urlPath) {
    unigram = new UnigramIndex(indexPath, vocabPath, urlPath);
}

vector<string> SearchEngine::search (string raw) {
    vector<string> query;
    
    string processed = u.cleanTerm(raw);
    vector<string> tokens = u.tokenize(processed);
    for (unsigned int i = 0; i < tokens.size(); i++) {
        if (u.isStopWord(tokens[i])) continue;
        query.push_back(tokens[i]);
    }
  
    vector<string> finalRes;
    vector<pair<string, float> > unigramResults = unigram->query(query);
    for (uint i = 0; i < 5 && i < unigramResults.size(); i++) {
        cout << unigramResults[i].first << ' ' << unigramResults[i].second << endl;
        finalRes.push_back(unigramResults[i].first);
    }
    return finalRes;
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

        for (uint i = 0; i < 5 && i < results.size(); i++) {
            cout << "> " << results[i] << endl;
        }
        
        cout << "\n---------------------------------\n";
    }
}

