#include "utils.hpp"

using namespace std;

Utils::Utils () {
    FILE *file = fopen("src/stopwords.txt", "r");
    char word [80];
    while (fscanf(file, "%s\n", word) == 1){
        stopWords.insert(word);
    }
    fclose(file);
    UErrorCode status = U_ZERO_ERROR; 
    accentsConverter = Transliterator::createInstance("NFD; [:M:] Remove; NFC", UTRANS_FORWARD, status);
}

vector<string> Utils::listdir (string folder) {
    vector<string> files;

    // open dir
    DIR *dp = opendir(folder.c_str());
    if (dp == NULL) {
        cerr << "\nCannot open directory " << folder << '\n';
        exit(1);
    }

    string name;
    struct dirent *dptr = readdir(dp);
    while (dptr != NULL) {
        name = dptr->d_name;
        // hidden files, current folder and parent folder
        if (name[0] != '.' && name != "..") {
            files.push_back(name);
        }
        dptr = readdir(dp);
    }

    closedir(dp);
    return files;
}

string Utils::toUTF8 (string raw) {
    unsigned char c;
    string result;
    for (int i = 0; i < raw.size(); i++) {
        c = raw[i];
        if (c < 128) result += c;
        else result+=0xc2+(c>0xbf), result+=(raw[i]&0x3f)+0x80;
    }
    return result;
}

// removes accents, transforms to lower case...
string Utils::cleanTerm (string raw) {
    raw = toUTF8(raw);

    // accents
    UnicodeString source = UnicodeString::fromUTF8(StringPiece(raw));
    accentsConverter->transliterate(source);
    string term;
    source.toUTF8String(term);

    // lower case
    transform(term.begin(), term.end(), term.begin(), ::tolower);

    return term;
}

bool Utils::isStopWord (string word) {
    unordered_set<string>::iterator it = stopWords.find(word);
    if (it == stopWords.end()) return false;
    else return true;
}

vector<string> Utils::tokenize (string page) {
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