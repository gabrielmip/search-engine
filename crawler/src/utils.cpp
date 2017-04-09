#include "utils.hpp"

using namespace std;

string Utils::getDomain(string url) {
    if (url.size() == 0) return "";

    string domain = spider.getUrlDomain(url.c_str());

    // looks for www in domain string
    const string www = "www.";
    int i; 
    for (i = 0; i < domain.size() && i < www.size(); i++) {
        if (www[i] != domain[i]) break;
    }

    // removes www
    return domain.substr(i, domain.size() - i);
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

    return depth;
}