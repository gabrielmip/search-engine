#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long int llu;
typedef struct {
    FILE *index;
    map<string, uint> vocab;
    map<uint, string> invVocab;
    map<uint, llu> pos;
    map<uint, string> invUrls;
} Index;

// for list of list sorting in ascending order on the size of the lists
bool sortDocsPerToken (vector<uint> const &a, vector<uint> const &b) {
    return a.size() < b.size();
}

string getUrl (uint code, Index i) {
    map<uint, string>::iterator it = i.invUrls.find(code);
    if (it == i.invUrls.end()) {
        cerr << "URL not found for given code: " << code << endl;
        exit(1);
    } else {
        return i.invUrls[code];
    }
}

bool isTermKnown (string term, Index index) {
    map<string, uint>::iterator iter = index.vocab.find(term);
    return !(iter == index.vocab.end());
}

vector<string> tokenize (string text) {
    vector<string> tokens;
    int previous = 0;
    int current = text.find(" ");
    
    while (current != string::npos) {
        if (current-previous > 0) {
            tokens.push_back(text.substr(previous, current-previous));
        }
        previous = current + 1;
        current = text.find(" ", previous);
    }

    if (text.size() - previous > 0) {
        tokens.push_back(text.substr(previous, text.size()-previous));
    }
    return tokens;
}

void readDocuments (string path, Index &index) {
    ifstream file (path);
    string line, url;
    uint code;
    int pointer;

    while (getline(file, line)) {
        pointer = line.find(',');
        code = stoul(line.substr(0, pointer).c_str());
        url = line.substr(pointer+1, line.size()-pointer-1);
        index.invUrls[code] = url;
    }
}

void readVocab (string path, Index &index) {
    string word;
    uint code;
    llu pos;
    ifstream file (path);
    string line;
    int pointer, current;

    // reads lines to extract code, word and position on index file
    while (getline(file, line)) {
        // code
        current = 0;
        pointer = line.find(',');
        code = stoul(line.substr(current, pointer-current).c_str());
        
        // pos
        current = pointer + 1;
        pointer = line.find(',', current);
        pos = stoull(line.substr(current, pointer-current));

        // word
        current = pointer + 1;
        word = line.substr(current, line.size()-current);
        
        index.vocab[word] = code;
        index.invVocab[code] = word;
        index.pos[code] = pos;
    }
}

// Returns vector of uints that appear in every vector in docsPerToken.
// Uses as reference the smallest vector.
// Checks if each element in the smallest vector can be found in the other ones.
// Removes element from reference list if it isnt found in every other list.
vector<uint> intersect (vector<vector<uint> > docsPerToken) {    
    uint doc;
    bool shouldIncludeDoc, foundDoc;
    vector<uint> intersection;

    if (docsPerToken.size() == 0) 
        return intersection;

    // sort by vector size
    sort(docsPerToken.begin(), docsPerToken.end(), sortDocsPerToken);

    // iterates over elements in the smallest set
    for (int i = 0; i < docsPerToken[0].size(); i++) {
        doc = docsPerToken[0][i];
        shouldIncludeDoc = true;

        // iterates over document lists
        for (int j = 1; j < docsPerToken.size(); j++) {
            foundDoc = false;
            // iterates over elements of document list
            for (int k = 0; k < docsPerToken[j].size(); k++) { 
                if (doc == docsPerToken[j][k]) {
                    foundDoc = true;
                    break;
                }
            }
            if (!foundDoc) {
                shouldIncludeDoc = false;
                break;
            }
        }
        // includes in the intersection if it was found in every other list
        if (shouldIncludeDoc) {
            intersection.push_back(doc);
        }
    }
    return intersection;
}

vector<string> search (string query, Index index) {
    vector<string> tokens = tokenize(query);
    vector<vector<uint> > docsPerToken (tokens.size());
    vector<string> urls;
    llu pos;
    uint term, code, doc, tf;
    char c;
    for (int i = 0; i < tokens.size(); i++) {
        // as it's a AND search, if any of the tokens is not 
        // in the collection, the result set is empty
        if (!isTermKnown(tokens[i], index)) {
            return urls;
        }
        
        code = index.vocab[tokens[i]];
        pos = index.pos[code]; // position on index file
        fseek(index.index, pos, SEEK_SET);
        term = code;
        c = 42;

        // reads documents where term appears
        while (c != EOF) {
            int ret = fscanf(index.index, "%u,%u,%u,", &term, &doc, &tf);
            do {
                c = fgetc(index.index);
            } while (c != '\n' and c != EOF); // read until the end of the line
            
            if (term == code and ret == 3) {
                docsPerToken[i].push_back(doc);
            } else {
                break;
            }
        }
    }
    // 
    vector<uint> docids = intersect(docsPerToken);
    for (int i = 0; i < docids.size(); i++) {
        urls.push_back(index.invUrls[docids[i]]);
    }
    return urls;
}

int main (int argc, char **argv) {
    string indexPath = argv[1];
    string vocabPath = argv[2];
    string documentsPath = argv[3];
    string query;
    vector<string> documents;

    Index index;
    index.index = fopen(indexPath.c_str(), "r");
    readVocab(vocabPath, index);
    readDocuments(documentsPath, index);

    while (true) {
        cout << "\nEnter search query: ";
        getline(cin, query);
        documents = search(query, index);
        cout << "\nSearch query returned " << documents.size() << " document(s).\n";
        if (documents.size() > 0) {
            cout << "Results:\n\n";
        }

        for (int i = 0; i < documents.size(); i++) {
            cout << "> " << documents[i] << endl;
        }
        cout << "\n---------------------------------\n";
    }
}