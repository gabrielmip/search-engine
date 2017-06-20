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

// comparator for link sorting
struct linkSorter {
    bool operator () (pair<uint, uint> const &a, pair<uint, uint> const &b) const {
        if (a.first < b.first) return true;
        else if (a.first == b.first) {
            if (a.second < b.second) return true;
            else return false;
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

// priority queue to merge page rank runs
struct pqLinkSorter {
    bool operator () (pair<pair<uint, uint>, int> const &a, pair<pair<uint, uint>, int> const &b) const {
        if (a.first.first > b.first.first) return true;
        else if (a.first.first == b.first.first) {
            return (a.first.second > b.first.second);
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
    MAX_MEM_USAGE = memory; // bytes
    memoryUsed = 0;
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
        for (unsigned int i = 0; i < separators.size(); i++) {
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
    if (previous < current) {
        token = page.substr(previous, current-previous);
        tokens.push_back(token);        
    }
    return tokens;
}

uint Indexer::getUrlCode (string url, unordered_map<string, uint> &m) {
    unordered_map<string, uint>::iterator it = m.find(url);    
    if (it == m.end()) { // url wasnt found
        m[url] = m.size();
    }
    return m[url];
}

uint Indexer::getTermCode (string term, unordered_map<string, uint> &m) {
    unordered_map<string, uint>::iterator it = m.find(term);
    if (it == m.end()) { // term wasnt found
        m[term] = m.size();
    }
    return m[term];
}

void Indexer::cacheLink (uint origin, uint dest) {
    cachedLinks.push_back(make_pair(origin, dest));
    memoryUsed += 2 * sizeof(uint);
    if (memoryUsed > MAX_MEM_USAGE) {
        dumpTuples();
    }
}

void Indexer::cacheAnchorTerm (uint term, uint dest) {
    cachedAnchorTuples.push_back(make_pair(term, dest));
    memoryUsed += 2 * sizeof(uint);
    if (memoryUsed > MAX_MEM_USAGE) {
        dumpTuples();
    }
}

void Indexer::addTuple (uint term, uint doc, vector<uint> pos) {
    Tuple a;
    a.term = term;
    a.doc = doc;
    a.pos = pos;
    cachedTuples.push_back(a);
    memoryUsed += (2 + pos.size()) * sizeof(uint);
    if (memoryUsed > MAX_MEM_USAGE) {
        dumpTuples();
    }
}

void Indexer::dumpTuples () {
    cout << "Enter Dump Function" << endl;
    memoryUsed = 0;
    pair<uint, uint> p;

    // sorted run
    sort(cachedTuples.begin(), cachedTuples.end(), tupleSorter());
    string filename = runfolder + "/" + to_string(runCount) + ".txt";
    FILE *file = fopen(filename.c_str(), "w");
    Tuple t;
    for (unsigned int i = 0; i < cachedTuples.size(); i++) {
        t = cachedTuples[i];
        fprintf(file, "%d,%d,%lu,", t.term, t.doc, t.pos.size());
        for (uint p = 0; p < t.pos.size()-1; p++) {
            fprintf(file, "%u,", t.pos[p]);
        }
        fprintf(file, "%u\n", t.pos[t.pos.size()-1]);
        cachedTuples[i].pos.clear();
    }
    fclose(file);

    // page rank
    sort(cachedLinks.begin(), cachedLinks.end(), linkSorter());
    filename = runfolder + "_pagerank/" + to_string(runCount) + ".txt";
    file = fopen(filename.c_str(), "w");
    for (unsigned int i = 0; i < cachedLinks.size(); i++) {
        fprintf(file, "%u,%u\n", cachedLinks[i].first, cachedLinks[i].second);
    }
    fclose(file);

    // anchor text
    sort(cachedAnchorTuples.begin(), cachedAnchorTuples.end(), linkSorter());
    filename = runfolder + "_anchortext/" + to_string(runCount) + ".txt";
    file = fopen(filename.c_str(), "w");

    for (unsigned int i = 0; i < cachedAnchorTuples.size(); i++) {
        fprintf(file, "%u,%u\n", cachedAnchorTuples[i].first, cachedAnchorTuples[i].second);
    }
    fclose(file);
    
    runCount++;
    cachedTuples.clear(); cachedTuples.shrink_to_fit();
    cachedLinks.clear(); cachedLinks.shrink_to_fit();
    cachedAnchorTuples.clear(); cachedAnchorTuples.shrink_to_fit();
    cout << "Leave Dump Function" << endl;
}

// recursive function that calls itself until there is only
// one file on the folder passed as parameter.
void Indexer::mergeRuns (string folder, string otherFolder) {
    string primaryFolder, secondaryFolder, auxFolder;

    ////////////////////////////////////
        //standard inverted index//
    ////////////////////////////////////
    Tuple tup;
    pair<Tuple, int> tuppair;
    vector<string> runPaths = u.listdir(folder);
    vector<RunIterator> runs (runPaths.size());
    priority_queue<pair<Tuple, int>, vector<pair<Tuple, int> >, pqTupleSorter> heap;
    uint numWays = MAX_MEM_USAGE / (100*sizeof(uint)); // 200 bytes for each tuple;
    primaryFolder = folder;
    secondaryFolder = otherFolder;

    while (runPaths.size() > 1) {
        // init run iterators
        for (unsigned int i = 0; i < runPaths.size(); i++) {
            runs[i].loadFile(primaryFolder + '/' + runPaths[i]);
        }
        
        // segments to be analysed considering numWays and runPaths.size()
        unsigned int numSegments = runPaths.size()/numWays;
        for (unsigned int i = 0; i <= numSegments; i++) {
            // interval from segment being analysed
            unsigned int lower = i * numSegments;
            unsigned int higher = lower + 1 + numSegments;
            if (higher >= runPaths.size()) {
                higher = runPaths.size() - 1;
            }

            // filling heap
            unsigned int index = lower;
            bool pushedSomething = false;
            while (heap.size() < numWays) {
                if (!runs[index].isFileOver()) {
                    tup = runs[index].nextTuple();
                    heap.push(make_pair(tup, index));
                    pushedSomething = true;
                }
                if (index+1 > higher) {
                    if (!pushedSomething) break;
                    index = lower;
                    pushedSomething = false;
                } else {
                    index++;
                }
            }

            // file with merged runs
            string mergedName = secondaryFolder + '/' + to_string(i) + ".txt";
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
        for (unsigned int i = 0; i < runPaths.size(); i++) {
            string name = primaryFolder + '/' + runPaths[i];
            remove(name.c_str());
            runs[i].close();
        }

        runPaths.clear();
        runs.clear();
        runPaths = u.listdir(secondaryFolder); // otherfolder
        
        auxFolder = primaryFolder;
        primaryFolder = secondaryFolder;
        secondaryFolder = auxFolder;
    }

    if (primaryFolder != folder) {
        runPaths = u.listdir(secondaryFolder);
        for (unsigned int i = 0; i < runPaths.size(); i++) {
            rename((secondaryFolder +'/'+ runPaths[i]).c_str(), (primaryFolder +'/'+ runPaths[i]).c_str());
        }
    }
}


////////////////////////////////////
       // page rank index //
////////////////////////////////////
void Indexer::mergePageRankRuns (string folder, string otherFolder) {
    string primaryFolder, secondaryFolder, auxFolder;

    pair<uint, uint> tup;
    pair<pair<uint, uint>, int> tuppair;
    vector<string> runPaths = u.listdir(folder);
    vector<RankRunIterator> runs (runPaths.size());
    priority_queue<pair<pair<uint, uint>, int>, vector<pair<pair<uint, uint>, int> >, pqLinkSorter> heap;
    uint numWays = MAX_MEM_USAGE / (2*sizeof(uint));
    primaryFolder = folder;
    secondaryFolder = otherFolder;

    while (runPaths.size() > 1) {
        // init run iterators
        for (unsigned int i = 0; i < runPaths.size(); i++) {
            runs[i].loadFile(primaryFolder + '/' + runPaths[i]);
        }
        
        // segments to be analysed considering numWays and runPaths.size()
        unsigned int numSegments = runPaths.size()/numWays;
        for (unsigned int i = 0; i <= numSegments; i++) {
            // interval from segment being analysed
            unsigned int lower = i * numSegments;
            unsigned int higher = lower + 1 + numSegments;
            if (higher >= runPaths.size()) {
                higher = runPaths.size() - 1;
            }

            // filling heap
            unsigned int index = lower;
            bool pushedSomething = false;
            while (heap.size() < numWays) {
                if (!runs[index].isFileOver()) {
                    tup = runs[index].nextTuple();
                    heap.push(make_pair(tup, index));
                    pushedSomething = true;
                }
                if (index+1 > higher) {
                    if (!pushedSomething) break;
                    index = lower;
                    pushedSomething = false;
                } else {
                    index++;
                }
            }

            // file with merged runs
            string mergedName = secondaryFolder + '/' + to_string(i) + ".txt";
            FILE *mergedFile = fopen(mergedName.c_str(), "w");            
            
            // pops heap, writes to merged run's file and pushs
            // a tuple from the run where the popped one came from
            while (!heap.empty()) {
                tuppair = heap.top();
                tup = tuppair.first;
                index = tuppair.second;
                heap.pop();

                // writes to file
                fprintf(mergedFile, "%u,%u\n", tup.first, tup.second);

                // inserts a new one if possible
                if (!runs[index].isFileOver()) {
                    tup = runs[index].nextTuple();
                    heap.push(make_pair(tup, index));
                }
            }
            fclose(mergedFile);
        }

        // deleting original run files
        for (unsigned int i = 0; i < runPaths.size(); i++) {
            string name = primaryFolder + '/' + runPaths[i];
            remove(name.c_str());
            runs[i].close();
        }

        runPaths.clear();
        runs.clear();
        runPaths = u.listdir(secondaryFolder); // otherfolder
        
        auxFolder = primaryFolder;
        primaryFolder = secondaryFolder;
        secondaryFolder = auxFolder;
    }

    if (primaryFolder != folder) {
        runPaths = u.listdir(secondaryFolder);
        for (unsigned int i = 0; i < runPaths.size(); i++) {
            rename((secondaryFolder +'/'+ runPaths[i]).c_str(), (primaryFolder +'/'+ runPaths[i]).c_str());
        }
    }
}

// parses page html, getting indexable tokens and hrefs 
// for pagerank calculation and anchor text indexing
void Indexer::indexPage(string raw, string url) {
    uint docIndex = getUrlCode(url, urlCodes);
    uint dest;
    pair<bool, string> attr;
    map<string, string> attrs;
    
    unordered_map<uint, vector<uint> > appearsAt;
    string phrase;
    Tuple a;
    
    htmlcxx::HTML::ParserDom parser;
    tree<htmlcxx::HTML::Node> dom = parser.parseTree(raw);
    tree<htmlcxx::HTML::Node>::iterator it = dom.begin();
    vector<string> terms;
    string tagName, anchorText;
    uint docIndexPageRank;

    // navigates through page's parsing tree
    for (; it != dom.end(); ++it) {
        if (it.node != 0 && dom.parent(it) != NULL){
            tagName = dom.parent(it)->tagName();
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
        
        tagName = it->tagName();
        if (tagName == "a" or tagName == "A") {
            it->parseAttributes();
            attr = it->attribute("href");

            // if there isnt href attribute on <a>
            if (!attr.first or attr.second.size() == 0) {
                continue;
            }
            
            anchorText = "";
            int children = it.number_of_children();
            for (int i = 0; i < children; i++) {
                it++;
                if (it == dom.end()) break;
                if (!it->isTag()) {
                    anchorText += it->text();
                }
            }

            // page rank
            docIndexPageRank = getUrlCode(url, pageRankUrlCodes);
            dest = getUrlCode(attr.second, pageRankUrlCodes);
            cacheLink(docIndexPageRank, dest);

            // index anchor terms
            terms = tokenize(anchorText);
            for (unsigned int i = 0; i < terms.size(); i++) {
                if (u.isStopWord(terms[i])) continue;
                uint termIndex = getTermCode(terms[i], anchorVocabulary);
                cacheAnchorTerm(termIndex, dest);
            }
            
        }  else if ((!it->isTag()) && (!it->isComment())) {
            // do the standard indexing with textual terms from doc
            phrase = u.cleanTerm(it->text());
            terms = tokenize(phrase);
            for (unsigned int i = 0; i < terms.size(); i++) {
                if (u.isStopWord(terms[i])) continue;
                uint termIndex = getTermCode(terms[i], vocabulary);
                appearsAt[termIndex].push_back(i);
            }
        }
    }

    // store tuples
    unordered_map<uint, vector<uint> >::iterator mt;
    for (mt = appearsAt.begin(); mt != appearsAt.end(); mt++) {
        uint termIndex = mt->first;
        vector<uint> positions = mt->second;
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

    // creating inverse vocabulary hash unordered_map
    unordered_map<uint, string> invVocab;
    unordered_map<string, uint>::iterator it;
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
    unordered_map<string, uint>::iterator urlit;
    for (urlit = urlCodes.begin(); urlit != urlCodes.end(); urlit++) {
        fprintf(urlsFile, "%u,%s\n", urlit->second, urlit->first.c_str());
    }

    fclose(urlsFile);
    indexFile.close();
    fclose(vocabFile);
}

void Indexer::outputPageRank (string folder) {
    // std::unordered_map<std::string, uint> pageRankUrlCodes;

    vector<string> paths = u.listdir(folder);
    FILE *indexFile = fopen((folder + '/' + paths[0]).c_str(), "r");
    FILE *newFile = fopen((folder + "/compressed.txt").c_str(), "w");
    uint ori, dest, prev;
    prev = ori = 0;
    bool first = true;
    while (fscanf(indexFile, "%u,%u\n", &ori, &dest) == 2) {
        if (prev != ori) {
            if (first) {
                fprintf(newFile, "%u ", ori);
                first = false;
            }
            else fprintf(newFile, "\n%u ", ori);
        }
        fprintf(newFile, "%u ", dest);
        prev = ori;
    }
    fclose(indexFile);
    fclose(newFile);


    FILE *urlFile = fopen((folder + "/urls.txt").c_str(), "w");
    unordered_map<string, uint>::iterator it;
    for (it = pageRankUrlCodes.begin(); it != pageRankUrlCodes.end(); it++) {
        fprintf(urlFile, "%s %u\n", it->first.c_str(), it->second);
    }
    fclose(urlFile);
}

void Indexer::outputAnchorText (string folder) {
    // std::unordered_map<std::string, uint> anchorVocabulary;

    // inverted vocabulary index
    unordered_map<uint, string> inverted;
    unordered_map<string, uint>::iterator it;
    for (it = anchorVocabulary.begin(); it != anchorVocabulary.end(); it++) {
        inverted[it->second] = it->first;
    }

    // write index and vocabulary
    vector<string> paths = u.listdir(folder);
    FILE *indexFile = fopen((folder + '/' + paths[0]).c_str(), "r");
    FILE *newFile = fopen((folder + "/compressed.txt").c_str(), "w");
    FILE *vocFile = fopen((folder + "/vocabulary.txt").c_str(), "w");
    
    uint ori, dest, prev;
    prev = ori = 0;
    bool first = true;
    string term;
    long long unsigned int pos = 0;
    while (fscanf(indexFile, "%u,%u\n", &ori, &dest) == 2) {
        if (prev != ori) {
            if (!first) {
                fprintf(vocFile, "%s %u %llu\n", inverted[ori].c_str(), ori, pos+1);
                pos += fprintf(newFile, "\n%u ", ori);
            }
            else {
                first = false;
                fprintf(vocFile, "%s %u %llu\n", inverted[ori].c_str(), ori, pos);
                pos += fprintf(newFile, "%u ", ori);
            }
        }
        pos += fprintf(newFile, "%u ", dest);
        prev = ori;
    }

    fclose(indexFile);
    fclose(newFile);
    fclose(vocFile);
}

void Indexer::run () {
    string rawpage, page, file, url;
    FileIterator it;
    uint pageIndexed = 0;

    // iterates over all raw html files
    for (string file : rawfiles) {
        it.loadFile(rawfolder + '/' + file);
        cout << "Indexing file " << ++pageIndexed << "..." << endl;
        while (!it.isFileOver()) {
            rawpage = it.nextPage();
            url = it.getUrl();
            if (url.size() > 0 and rawpage.size() > 0){
                indexPage(rawpage, url);
            }
        }
    }
    
    if (cachedTuples.size() > 0) {
        dumpTuples();
    }

    // merges them
    // cout << "Merge standard index..." << endl;
    // mergeRuns(runfolder, mergefolder);
    // cout << "Merge page rank info..." << endl;
    // mergePageRankRuns(runfolder+"_pagerank", mergefolder);
    // cout << "Merge anchor text info..." << endl;
    // mergePageRankRuns(runfolder+"_anchortext", mergefolder);

    // outputIndex(runfolder);
    // outputPageRank(runfolder+"_pagerank");
    // outputAnchorText(runfolder+"_anchortext");
}

void Indexer::log (uint indexed, int type) {
    time_t timer;
    time(&timer);
    // fprintf(logFile, "%ld,%d,%d,%u\n", timer, type, MAX_NUM_TUPLES, indexed);
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
    cout << "Initializing..." << endl;
    Indexer indexer (docsFolder, runsFolder, mergeFolder, outputPath, memory, logPath);
    cout << "Run..." << endl;
    indexer.run();
}
