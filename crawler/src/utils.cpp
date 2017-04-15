#include "utils.hpp"

using namespace std;

Utils::Utils () {
    indexEndings.push_back("/index.html");
    indexEndings.push_back("/index.htm");
    indexEndings.push_back("/index.php");
    indexEndings.push_back("/index.asp");
    indexEndings.push_back("/default.asp");
    indexEndings.push_back("/default.html");
    indexEndings.push_back("/default.htm");
    indexEndings.push_back("/default.php");
    indexEndings.push_back("/");
}

string Utils::getDomain(string url) {
    if (url.size() == 0) return "";

    string domain = spider.getUrlDomain(url.c_str());

    // looks for www in domain string
    const string www = "www.";
    int i = 0; 
    for (; i < domain.size() && i < www.size(); i++) {
        if (www[i] != domain[i]) break;
    }

    // removes www
    if (i == www.size())
        domain = domain.substr(i, domain.size() - i);

    //removes subdomain if it has any
    return spider.getBaseDomain(domain.c_str());
}

// count slashs in url, ignoring the first 2
// related to protocol info
int Utils::countDepth (string url) {
    const string https = "https";
    int depth = 0;
    int i;

    // skip protocol
    for (i = 0; i < https.size() && i < url.size(); i++) {
        if (url[i] != https[i]) break;
    }

    // skip slashs
    if (i > 2) i += 3;
    else i = 0; // deu ruim

    // count slashs
    for (; i < url.size(); i++) {
        if (url[i] == '/') depth++;
    }

    if (url[i-1] != '/') depth++;

    return depth;
}

string Utils::formatUrl (string url) {
    // lower case
    transform(url.begin(), url.end(), url.begin(), ::tolower);

    // removes duplicated slashs from the begining (https://////, for instance)
    const string https = "https";
    int i;
    for (i = 0; i < https.size() && i < url.size(); i++) {
        if (url[i] != https[i]) break;
    }
    if (i > 2) i += 3; // now i stores position of char after second slash in http://
    int extras = 0;
    for (; i + extras < url.size() && url[i + extras] == '/'; extras++) {} // counts extra slashs
    url.erase(i, extras);

    // index endings (index.html, index.php, etc)
    int pos, exStartPos;
    for (int i = 0; i < indexEndings.size(); i++) {
        exStartPos = url.size() - indexEndings[i].size();
        pos = url.find(indexEndings[i], exStartPos);
        if (pos != string::npos) { // found expression
            url = url.substr(0, exStartPos);
            break;
        }
    }

    return url;
}

void Utils::log (string url) {
    time_t timer;
    time(&timer);
    crawlingLog.push_back(make_pair(url, timer));
}

void Utils::setLogPath (string logPath) {
    path = logPath;
}

void Utils::dumpLog () {
    fstream fs;
    fs.open(path, fstream::in | fstream::out | fstream::app);

    vector<pair<string, time_t> >::iterator it;
    for (it = crawlingLog.begin(); it != crawlingLog.end(); it++) {
        fs << it->second << " " << it->first << endl;
    }
    
    fs.close();

    crawlingLog.clear();
}