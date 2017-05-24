#include "indexer.hpp"

using namespace std;

Indexer::Indexer (string raw, string merge, string out) {
    rawfolder = raw;
    mergefolder = merge;
    outpath = out;
    rawfiles = u.listdir(raw);
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
            cout << token << '\n';
        }
        it++;
    }
    return tokens;
}

void Indexer::indexPage (string raw) {
    string page = cleanHtml(raw);
    cout << page << endl;
    vector<string> tokens = tokenize(page);
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

void Indexer::run () {
    string rawpage, page, file;
    FileIterator it;

    for (string file : rawfiles) {
        it.loadFile(rawfolder + '/' + file);
        while (!it.isFileOver()) {
            rawpage = it.nextPage();
            indexPage(rawpage);
        }
    }
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
    // FileIterator it;
    // it.loadFile(rawfiles[0]);
    // string page = it.nextPage();
    // indexer.tokenize(page);

}