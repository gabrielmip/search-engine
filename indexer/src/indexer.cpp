#include "indexer.hpp"

using namespace std;

struct tupleSorter {
    bool operator () (Tuple const &a, Tuple const &b) const {
        if (a.term < b.term) return true;
        else if (a.term == b.term) {
            if (a.doc < b.doc) return true;
            else if (a.doc == b.doc) {
                if (a.pos.size() < b.pos.size()) return true;
                else return false;
            } else return false;
        } else return false;
    }
};

Indexer::Indexer (string raw, string merge, string out) {
    rawfolder = raw;
    mergefolder = merge;
    outpath = out;
    rawfiles = u.listdir(raw);
    MAX_NUM_TUPLES = 5;
    runCount = 0;
}

vector<string> Indexer::tokenize (string page) {
    vector<string> tokens;
    string token;
    regex rgx("[\\t\\s\\n\\r\\.,;:!?^'\"@#$\\%&*(){}[\\]\\-+=_/\\|<>]");
    sregex_token_iterator it (page.begin(), page.end(), rgx, -1);
    sregex_token_iterator end;
    
    while (it != end) {
        token = it->str();
        if (token.size() > 0) {
            tokens.push_back(token);
        }
        it++;
    }
    return tokens;
}

string Indexer::cleanHtml (string raw) {
    htmlcxx::HTML::ParserDom parser;
    tree<htmlcxx::HTML::Node> dom = parser.parseTree(raw);
    tree<htmlcxx::HTML::Node>::iterator it = dom.begin();

    string text = "";

    for (; it != dom.end(); ++it) {
        if(it.node != 0 && dom.parent(it) != NULL){
            string tagName = dom.parent(it)->tagName();
            transform(tagName.begin(), tagName.end(), tagName.begin(), ::tolower);

            // Skipping code embedded in html
            if ((tagName == "script") ||
                (tagName == "noscript") ||
                (tagName == "style")
                ){
                it.skip_children();
                continue;
            }
        }

        if ((!it->isTag()) && (!it->isComment())) {
            text.append(it->text()+" ");
        }
    }
    return text;
}

int Indexer::getUrlCode (string url) {
    map<string, int>::iterator it = urlCodes.find(url);    
    if (it == urlCodes.end()) { // url wasnt found
        urlCodes[url] = urlCodes.size();
    }
    return urlCodes[url];
}

int Indexer::getTermCode (string term) {
    map<string, int>::iterator it = vocabulary.find(term);    
    if (it == vocabulary.end()) { // term wasnt found
        // printf("%s wasnt found. code: %d\n", term.c_str(), vocabulary.size());
        vocabulary[term] = vocabulary.size();
    }
    return vocabulary[term];
}

void Indexer::addTuple (int term, int doc, vector<int> pos) {
    Tuple a;
    a.term = term;
    a.doc = doc;
    a.pos = pos;
    cachedTuples.push_back(a);

    // sort and store in files
    if (cachedTuples.size() > MAX_NUM_TUPLES) {
        sort(cachedTuples.begin(), cachedTuples.end(), tupleSorter());
        string filename = mergefolder + "/" + to_string(runCount) + ".txt";
        FILE *file = fopen(filename.c_str(), "w");
        int doc, term;
        Tuple t;
        for (int i = 0; i < cachedTuples.size(); i++) {
            t = cachedTuples[i];
            fprintf(file, "%d,%d,%d,", t.term, t.doc, t.pos.size());
            for (int p = 0; p < t.pos.size()-1; p++) {
                fprintf(file, "%d,", t.pos[p]);
            }
            fprintf(file, "%d\n", t.pos[t.pos.size()-1]);
        }
        fclose(file);
        runCount++;
        cachedTuples.clear();
    }
}

void Indexer::dumpTuples () {
    int doc, term;
    Tuple t;

    // sorted run
    sort(cachedTuples.begin(), cachedTuples.end(), tupleSorter());
    string filename = mergefolder + "/" + to_string(runCount) + ".txt";
    FILE *file = fopen(filename.c_str(), "w");

    // writes to file
    for (int i = 0; i < cachedTuples.size(); i++) {
        t = cachedTuples[i];
        fprintf(file, "%d,%d,%d,", t.term, t.doc, t.pos.size());
        for (int p = 0; p < t.pos.size()-1; p++) {
            fprintf(file, "%d,", t.pos[p]);
        }
        fprintf(file, "%d\n", t.pos[t.pos.size()-1]);
    }

    fclose(file);
    runCount++;
    cachedTuples.clear();
}

// void Indexer::mergeDump () {
    
// }

void Indexer::indexPage(string raw, string url) {
    string page = cleanHtml(raw);
    vector<string> terms = tokenize(page);
    int docIndex = getUrlCode(url);
    map<int, vector<int> > appearsAt;
    
    // frequency of terms
    for (int i = 0; i < terms.size(); i++) {
        // if (isStopWord(terms[i])) continue;
        int termIndex = getTermCode(terms[i]);
        appearsAt[termIndex].push_back(i);
    }

    // store tuples
    map<int, vector<int> >::iterator it;
    for (it = appearsAt.begin(); it != appearsAt.end(); it++) {
        int termIndex = it->first;
        vector<int> positions = it->second;
        addTuple(termIndex, docIndex, positions);
    }
}

void Indexer::run () {
    string rawpage, page, file, url;
    FileIterator it;

    for (string file : rawfiles) {
        it.loadFile(rawfolder + '/' + file);
        while (!it.isFileOver()) {
            rawpage = it.nextPage();
            url = it.getUrl();
            indexPage(rawpage, url);
        }
    }

    if (cachedTuples.size() > 0) {
        dumpTuples();
    }

    // mergeDumps();
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
    Indexer indexer (rawFolder, mergeFolder, outputPath);
    indexer.run();


}