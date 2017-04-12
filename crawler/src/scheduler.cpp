#include "scheduler.hpp"

using namespace std;

// to use on max_min_heap
inline bool operator<( const tuple<string, int, time_t>& a, const tuple<string, int, time_t>& b) {
    if (get<1>(a) < get<1>(b)) {
        return true;    
    } else if (get<1>(a)-2 < get<1>(b)+2 && get<2>(a) < get<2>(b)) { // a little range to avoid starving
        return true;
    }
    return false;
}



Scheduler::Scheduler (int size) {
    MAX_HEAP_SIZE = size;

    allowedUrls.push_back(".br");
    allowedUrls.push_back("//br.");
    allowedUrls.push_back("globo.com");
    allowedUrls.push_back("ingresso.com");
    allowedUrls.push_back("r7.com");
    allowedUrls.push_back("amocinema.com");
    
    notAllowedUrls.push_back("<%"); // JS TEMPLATES
    notAllowedUrls.push_back("{{");
    notAllowedUrls.push_back("addtoany.com/add_to");
    notAllowedUrls.push_back("migre.me");
    notAllowedUrls.push_back("bit.ly");
    notAllowedUrls.push_back("share=");
    notAllowedUrls.push_back("www.facebook.com/sharer.php");
}

bool Scheduler::hasUnvisited () {
    return (urlsToCrawl.size() > 0);
}

string Scheduler::popUrl () {
    
    if (urlsToCrawl.size() == 0) {
        return ""; // to be treated on thread function
    }
    
    string url, domain;
    int penalty;
    time_t lastVisit;
    time_t now;
    time(&now);
    tuple<string, int, time_t> item;
    vector<tuple<string, int, time_t> > toAddLater;
    
    mtx.lock();
    
    // cout << "while"<<endl;
    
    while (urlsToCrawl.size() > 0) {
        tie (url, penalty, lastVisit) = urlsToCrawl.min();
        urlsToCrawl.pop_min();

        //cout << url << ' ' << penalty << ' ' << now - lastVisit << endl;

        if (lastVisit == -1 || now - lastVisit >= POLITENESS_TIME) {
            domain = utils.getDomain(url);
            updateDomainAccessTime(domain);
            for (int i = 0; i < toAddLater.size(); i++) {
                urlsToCrawl.push(toAddLater[i]);
            }
            mtx.unlock();
            toAddLater.clear();
            return url;
        } else {
            penalty += 1;
            toAddLater.push_back(make_tuple(url, penalty, lastVisit));
        }
    }

    for (int i = 0; i < toAddLater.size(); i++) {
        urlsToCrawl.push(toAddLater[i]);
    }

    // if has gotten to here, wasn't able to successfully
    // return a page url
    mtx.unlock();
    return "";
}

void Scheduler::updateDomainAccessTime (string domain) {
    unordered_map<string, pair<int, time_t> >::iterator it = domainLastVisit.find(domain);
    time_t now;
    time(&now);
    if (it != domainLastVisit.end()) {
        domainLastVisit[domain].first += 1;
        domainLastVisit[domain].second = now;
    } else {
        domainLastVisit[domain] = make_pair(1, now);
    }
}

pair<int, time_t> Scheduler::getDomainInfo (string domain) {
    unordered_map<string, pair<int, time_t> >::iterator it = domainLastVisit.find(domain);
    if (it != domainLastVisit.end()) {
        return it->second;
    } else {
        return make_pair(1, -1);
    }
}

bool Scheduler::domainCanBeAccessed (string domain) {
    unordered_map<string, pair<int, time_t> >::iterator it = domainLastVisit.find(domain);
    if (it == domainLastVisit.end()) {
        return true;
    } else {
        pair<int, time_t> domainLog = it->second;
        time_t lastVisit = domainLog.second;
        time_t now;
        time(&now);
        if (now - lastVisit < POLITENESS_TIME) {
            return false;
        } else return true;
    }
}

bool Scheduler::hasBeenSeen (string url) {
    if (registeredUrls.find(url) == registeredUrls.end()) {
        return false;
    } else {
        return true;
    }
}

bool Scheduler::isUrlAllowed (string url) {
    bool allow = false;
    bool disallow = false;
    
    int pos;
    for (int i = 0; i < allowedUrls.size(); i++) {
        pos = url.find(allowedUrls[i]);
        if (pos != string::npos) { // found expression
            allow = true;
            break;
        }
    }

    for (int i = 0; i < notAllowedUrls.size(); i++) {
        pos = url.find(notAllowedUrls[i]);
        if (pos != string::npos) { // found expression
            disallow = true;
            break;
        }
    }

    return allow && !disallow;
}

void Scheduler::addUrl (string url) {
    string formattedUrl = utils.formatUrl(url);
    if (!isUrlAllowed(formattedUrl)) return;
    int depth = utils.countDepth(formattedUrl);

    mtx.lock();
    if (!hasBeenSeen(formattedUrl)) {
        if (urlsToCrawl.size() > MAX_HEAP_SIZE)
            urlsToCrawl.pop_max();
        
        pair<int, time_t> domainInfo = getDomainInfo(utils.getDomain(formattedUrl));
        urlsToCrawl.push(make_tuple(url, domainInfo.first, domainInfo.second));
        registeredUrls[formattedUrl] = ' ';
    }
    mtx.unlock();
}

void Scheduler::addUrls (vector<string> urls) {
    for (int i = 0; i < urls.size(); i++) {
        addUrl(urls[i]);
    }
}

// assumes it is a well formed url taken from the scheduler
void Scheduler::reAddUrl (string url) {
    mtx.lock();
    pair<int, time_t> domainInfo = getDomainInfo(utils.getDomain(url));
    urlsToCrawl.push(make_tuple(url, domainInfo.first, domainInfo.second));
    mtx.unlock();
}

void Scheduler::setPolitenessTime(int seconds) {
    POLITENESS_TIME = seconds;
}