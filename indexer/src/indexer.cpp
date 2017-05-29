#include "indexer.hpp"

using namespace std;

typedef unsigned int uint;

// for tuple sorting when writing a run to file
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

// priority queue to merge runs
struct pqTupleSorter {
    bool operator () (pair<Tuple, int> const &aa, pair<Tuple, int> const &bb) const {
        Tuple a = aa.first;
        Tuple b = bb.first;
        if (a.term > b.term) return true;
        else if (a.term == b.term) {
            if (a.doc > b.doc) return true;
            else if (a.doc == b.doc) {
                if (a.pos.size() > b.pos.size()) return true;
                else return false;
            } else return false;
        } else return false;
    }
};

// memory in megabytes
Indexer::Indexer (string raw, string runs, string merge, string out, int memory, string logPath) {
    rawfolder = raw;
    runfolder = runs;
    mergefolder = merge;
    outpath = out;
    rawfiles = u.listdir(raw);
    MAX_NUM_TUPLES = (1000000 * memory) / (8 + 4*500);
    runCount = 0;
    logFile = fopen(logPath.c_str(), "a");
}

vector<string> Indexer::tokenize (string page) {
    vector<string> tokens;
    string token;
    uint current, previous;
    vector<char> separators = {'\t',' ','\n','\r','.',',',';',':','!','?','^','\'','"','@','#','$','%','&','*','(',')','{','}','[',']','-','+','=','_','/','\\','|','<','>'};
    current = previous = 0;
    while (current < page.size()) {
        // iterates over separators to see if end of word was found
        for (int i = 0; i < separators.size(); i++) {
            if (page[current] == separators[i]) {
                // word is considered if size is greater than 0, ofc
                if (current-previous > 0) {
                    token = page.substr(previous, current-previous);
                    tokens.push_back(token);
                }
                previous = current + 1;
                break;
            }
        }
        current++;
    }
    return tokens;
}

string Indexer::cleanHtml (string raw) {
    htmlcxx::HTML::ParserDom parser;
    tree<htmlcxx::HTML::Node> dom = parser.parseTree(raw);
    tree<htmlcxx::HTML::Node>::iterator it = dom.begin();

    string text = "";
    string formatted;

    for (; it != dom.end(); ++it) {
        if (it.node != 0 && dom.parent(it) != NULL){
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
            formatted = u.cleanTerm(it->text());
            text.append(formatted+" ");
        }
    }
    return text;
}

uint Indexer::getUrlCode (string url) {
    map<string, uint>::iterator it = urlCodes.find(url);    
    if (it == urlCodes.end()) { // url wasnt found
        urlCodes[url] = urlCodes.size();
    }
    return urlCodes[url];
}

uint Indexer::getTermCode (string term) {
    map<string, uint>::iterator it = vocabulary.find(term);    
    if (it == vocabulary.end()) { // term wasnt found
        // printf("%s wasnt found. code: %d\n", term.c_str(), vocabulary.size());
        vocabulary[term] = vocabulary.size();
    }
    return vocabulary[term];
}

void Indexer::addTuple (uint term, uint doc, vector<uint> pos) {
    Tuple a;
    a.term = term;
    a.doc = doc;
    a.pos = pos;
    cachedTuples.push_back(a);

    // sort and store in files
    if (cachedTuples.size() > MAX_NUM_TUPLES) {
        dumpTuples();
    }
}

void Indexer::dumpTuples () {
    // sorted run
    sort(cachedTuples.begin(), cachedTuples.end(), tupleSorter());
    string filename = runfolder + "/" + to_string(runCount) + ".txt";
    FILE *file = fopen(filename.c_str(), "w");

    // writes to file
    Tuple t;
    for (int i = 0; i < cachedTuples.size(); i++) {
        t = cachedTuples[i];
        fprintf(file, "%d,%d,%lu,", t.term, t.doc, t.pos.size());
        for (uint p = 0; p < t.pos.size()-1; p++) {
            fprintf(file, "%u,", t.pos[p]);
        }
        fprintf(file, "%u\n", t.pos[t.pos.size()-1]);
    }

    fclose(file);
    runCount++;
    cachedTuples.clear();
}

// recursive function that calls itself until there is only
// one file on the folder passed as parameter.
string Indexer::mergeRuns (string folder, string otherFolder) {
    vector<string> runPaths = u.listdir(folder);
    if (runPaths.size() == 1) { // merge is done
        return folder;
    }
    
    Tuple tup;
    pair<Tuple, int> tuppair;
    vector<RunIterator> runs (runPaths.size());
    priority_queue<pair<Tuple, int>, vector<pair<Tuple, int> >, pqTupleSorter> heap;

    // init run iterators
    for (int i = 0; i < runPaths.size(); i++) {
        runs[i].loadFile(folder + '/' + runPaths[i]);
    }

    // number of individual segments to be analysed
    for (int i = 0; i <= runPaths.size()/MAX_NUM_TUPLES; i++) {
        // segment interval
        int lowLim = i * runPaths.size()/MAX_NUM_TUPLES;
        int highLim = lowLim + 1 + runPaths.size()/MAX_NUM_TUPLES;
        if (highLim >= runPaths.size()) {
            highLim = runPaths.size() - 1;
        }
        
        // filling heap
        int index = lowLim;
        while (heap.size() < MAX_NUM_TUPLES) {
            if (!runs[index].isFileOver()) {
                tup = runs[index].nextTuple();
                heap.push(make_pair(tup, index));
            }
            index = (index+1 > highLim) ? lowLim : index+1;
        }

        // file with merged runs
        string mergedName = otherFolder + '/' + to_string(i) + ".txt";
        FILE *mergedFile = fopen(mergedName.c_str(), "w");
        
        // pops heap, writes to merged run's file and pushs
        // a tuple from the run where the popped one came from
        while (!heap.empty()) {
            tuppair = heap.top();
            tup = tuppair.first;
            index = tuppair.second;
            heap.pop();

            // writes to file (ugh)
            // printf("i: %d,\t<%d,%d,%lu>\n", index, tup.term, tup.doc, tup.pos.size());
            fprintf(mergedFile, "%d,%d,%lu,", tup.term, tup.doc, tup.pos.size());
            for (uint p = 0; p < tup.pos.size()-1; p++) {
                fprintf(mergedFile, "%u,", tup.pos[p]);
            }
            fprintf(mergedFile, "%u\n", tup.pos[tup.pos.size()-1]);

            // inserts a new one if possible
            if (!runs[index].isFileOver()) {
                tup = runs[index].nextTuple();
                heap.push(make_pair(tup, index));
            }
        }
        fclose(mergedFile);
    }
    
    // deleting original run files
    for (int i = 0; i < runPaths.size(); i++) {
        string name = folder + '/' + runPaths[i];
        remove(name.c_str());
        runs[i].close();
    }

    runPaths.clear();
    runs.clear();

    // call function again, now for the merged runs
    return mergeRuns(otherFolder, folder);
}

void Indexer::indexPage(string raw, string url) {
    string page = cleanHtml(raw);
    vector<string> terms = tokenize(page);
    uint docIndex = getUrlCode(url);
    map<uint, vector<uint> > appearsAt;
    
    // frequency of terms
    for (int i = 0; i < terms.size(); i++) {
        // if (isStopWord(terms[i])) continue;
        uint termIndex = getTermCode(terms[i]);
        appearsAt[termIndex].push_back(i);
    }

    // store tuples
    map<uint, vector<uint> >::iterator it;
    for (it = appearsAt.begin(); it != appearsAt.end(); it++) {
        uint termIndex = it->first;
        vector<uint> positions = it->second;
        addTuple(termIndex, docIndex, positions);
    }
}

void Indexer::outputIndex (string folder) {
    vector<string> files = u.listdir(folder);
    if (files.size() > 1) {
        cerr << "Final merge sort has more than one file." << endl;
        exit (1);
    }

    string oldPath = folder + '/' + files[0];
    string newPath = outpath + "/index.txt";
    string vocabPath = outpath + "/vocab.txt";
    string urlsPath = outpath + "/urls.txt";

    // moving index to output folder
    rename(oldPath.c_str(), newPath.c_str());

    // creating inverse vocabulary hash map
    map<uint, string> invVocab;
    map<string, uint>::iterator it;
    for (it = vocabulary.begin(); it != vocabulary.end(); it++) {
        invVocab[it->second] = it->first;
    }

    // storing vocabulary together with position on index file
    // FILE *indexFile = fopen(newPath.c_str(), "r");
    FILE *vocabFile = fopen(vocabPath.c_str(), "w");
    ifstream indexFile (newPath);
    string line;
    stringstream ss;
    uint term, current;
    term = current = 0;
    long long unsigned int pos = 0;

    fprintf(vocabFile, "%d,%llu,%s\n", current, pos, invVocab[current].c_str());
    while (!indexFile.eof()) {
        getline(indexFile, line);
        
        ss.str(line); // overkill...
        ss >> term;
        if (term != current) {
            current = term;
            fprintf(vocabFile, "%d,%llu,%s\n", current, pos, invVocab[current].c_str());
        }
        pos += line.size()+1; // +1 for newline
    }

    // storing urls
    FILE *urlsFile = fopen(urlsPath.c_str(), "w");
    map<string, uint>::iterator urlit;
    for (urlit = urlCodes.begin(); urlit != urlCodes.end(); urlit++) {
        fprintf(urlsFile, "%u,%s\n", urlit->second, urlit->first.c_str());
    }

    fclose(urlsFile);
    indexFile.close();
    fclose(vocabFile);
}

void Indexer::run () {
    string rawpage, page, file, url;
    FileIterator it;
    uint pageIndexed = 0;

    // iterates over all raw html files
    log(pageIndexed, 0);
    for (string file : rawfiles) {
        it.loadFile(rawfolder + '/' + file);
        while (!it.isFileOver()) {
            rawpage = it.nextPage();
            url = it.getUrl();
            if (url.size() > 0 and rawpage.size() > 0){
                indexPage(rawpage, url);
                if ((++pageIndexed % 10000) == 0) {
                    log(pageIndexed, 0);
                }
            }
        }
    }
    
    if (cachedTuples.size() > 0) {
        dumpTuples();
    }
    log(pageIndexed, 0);

    // end of iteration over raw html files
    // log(pageIndexed);

    // merges them
    log(pageIndexed, 1);
    string finalFolder = mergeRuns(runfolder, mergefolder);
    log(pageIndexed, 1);

    outputIndex(finalFolder);
    fclose(logFile);
}

void Indexer::log (uint indexed, int type) {
    time_t timer;
    time(&timer);
    fprintf(logFile, "%ld,%d,%d,%u\n", timer, type, MAX_NUM_TUPLES, indexed);
}

int main (int argc, char **argv) {
    if (argc != 7) {
        cerr << "Few arguments." << endl;
        exit(1);
    }

    string docsFolder = argv[1];
    string runsFolder = argv[2];
    string mergeFolder = argv[3];
    string outputPath = argv[4];
    int memory = atoi(argv[5]);
    string logPath = argv[6];

    Utils u;
    Indexer indexer (docsFolder, runsFolder, mergeFolder, outputPath, memory, logPath);
    indexer.run();
}