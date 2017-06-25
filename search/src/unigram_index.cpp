#include "unigram_index.hpp"

using namespace std;

UnigramIndex::UnigramIndex (string indexPath, string vocabPath, string urlPath) {
    index = fopen(indexPath.c_str(), "r");
    initVocabulary(vocabPath);
    initUrl(urlPath);
}

// returns the 50 best scored documents
vector<pair<string, float> > UnigramIndex::query (vector<string> terms) {
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

void UnigramIndex::populateVectors (map<uint, vector<float> > &vecs, uint termIndex, uint querySize) {
    vector<uint> docs;
    uint term, freq, doc, current;
    bool first = true;
    lastDoc = lastTerm = 0;
    char c = 'a';
    
    fscanf(index, "%ul,%ul,%ul,", &term, &doc, &freq);
    while (c != '\n') fscanf(index, "%c", c);

    do {
        docs.push_back(doc); // df
        if (vecs[doc].size() < querySize)
            vecs[doc].resize(querySize);
        vecs[doc][i]++; // tf
        
        fscanf(index, "%ul,%ul,%ul,", &current, &doc, &freq);
        while (c != '\n') fscanf(index, "%c", c);
    } while (current == term);

    // calculating final TF-IDF for doc terms
    for (int d = 0; d < docs.size(); d++) {
        vecs[docs[d]][i] *= log(urls.size()/(1+docs.size()));
    }
}

void UnigramIndex::initVocabulary (string path) {
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

void UnigramIndex::initUrl (string urlPath) {
    ifstream finf (urlPath);
    string line, url;
    uint id;
    
    while (getline(finf, line)) {
        pos = line.find(",");
        id = strtoul(line.substr(0,pos));
        url = line.substr(pos+1, line.size()-pos);
        urls[id] = url;
    }
    
    finf.close();
}

bool UnigramIndex::termNotFound (string term) {
    map<string, uul>::iterator it = positions.find(term);
    if (it == positions.end()) {
        return true;
    } else return false;
}
