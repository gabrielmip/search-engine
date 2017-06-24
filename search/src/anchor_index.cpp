#include "anchor_index.hpp"

using namespace std;

AnchorIndex::AnchorIndex (string indexPath, string vocabPath) {
    index = fopen(indexPath.c_str(), "r");
    initVocabulary(vocabPath);
}

// returns the 50 best scored documents
vector<pair<string, float> > AnchorIndex::query (vector<string> terms) {
    uul position;
    vector<pair<uint, float> > rankings;
    vector<pair<string, float> > results;
    map<uint, vector<float> > docvecs;

    // documents' tfidf vectors 
    for (int i = 0; i < terms.size(); i++) {
        if (termNotFound(terms[i])) continue;
        position = positions[terms];
        fseek(index, position, SEEK_SET);
        populateVectors(docvecs, i, terms.size());
    }

    // query's idf vector
    vector<float> queryVector (terms.size());
    for (int i = 0; i < terms.size(); i++) {
        queryVector[i] = log(terms.size());
    }

    // calculating rankings
    map<uint, vector<float> >::iterator it;
    for (it = docvecs.begin(); it != docvecs.end(); it++) {
        float ranking = 0;
        for (int i = 0; i < terms.size(); i++) {
            ranking += queryVector[i] * it->second[i];
        }
        // doc size normalization
        // ranking /= 
        rankings.push_back(make_pair(ranking, it->first));
    }

    // sort
    sort(rankings.begin(), rankings.end(), rankingSorter());
    for (int i = 0; i < 50 && i < rankings.size(); i++) {
        string url = urls[rankings[i].first];
        float score = rankings[i].second;
        results.push_back(make_pair(url, score));
    }

    return results;
}

void AnchorIndex::populateVectors (map<uint, vector<float> > &vecs, uint termIndex, uint querySize) {
    vector<uint> docs;
    uint doc, lastDoc = 0;
    char c = 'a';
    
    fscanf(index, "%ul", &doc); // term id
    fscanf(index, "%c", &c);
    while (c != '\n') {
        fscanf(index, "%ul", &doc); // term id
        fscanf(index, "%c", &c);
        
        if (doc != lastDoc) {
            docs.push_back(doc); // df
            lastDoc = doc;
        }
        if (vecs[doc].size() < querySize)
            vecs[doc].resize(querySize);
        vecs[doc][i]++; // tf
    }

    // calculating final TF-IDF for doc terms
    for (int d = 0; d < docs.size(); d++) {
        vecs[docs[d]][i] *= log(totalDocs/(1+docs.size()));
    }
}

void AnchorIndex::initVocabulary (string path) {
    ofstream file (path);
    string term, line;
    uint id;
    uul pos;
    while (getline(file, line)) {
        stringstream ss (line);
        ss >> term >> id >> pos;
        positions[term] = pos;
    }
    file.close();
}

bool AnchorIndex::termNotFound (string term) {
    map<string, uul>::iterator it = positions.find(term);
    if (it == positions.end()) {
        return true;
    } else return false;
}