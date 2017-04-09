#include "utils.h"

using namespace std;

Utils::Utils () {};

string Utils::getDomain(string url) {
    string domain = spider.getBaseDomain(url);
    cout << domain << '\n';
    return domain;
}