#include "scheduler.hpp"

using namespace std;

// to use on max_min_heap
inline bool operator<( const PageEntity& a, const PageEntity& b) {
    if (a.depth-4 < b.depth+4 && a.penalty < b.penalty) { 
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
    notAllowedUrls.push_back("facebook.com/sharer.php");
    notAllowedUrls.push_back("twitter.com/share");
    notAllowedUrls.push_back("reddit.com/submit");
    notAllowedUrls.push_back("validator.w3.org/check");
}

bool Scheduler::hasUnvisited () {
    return (urlsToCrawl.size() > 0);
}

string Scheduler::popUrl () {
    
    if (urlsToCrawl.size() == 0) {
        return ""; // to be treated on thread function
    }
    
    PageEntity page;
    pair<int, time_t> domainInfo;
    vector<PageEntity> toAddLater;
    time_t now;
    
    mtx.lock();

    time(&now);
    
    while (urlsToCrawl.size() > 0) {
        page = urlsToCrawl.min();
        urlsToCrawl.pop_min();
        domainInfo = getDomainInfo(page.domain);

        if (domainInfo.second == -1 || now - domainInfo.second >= POLITENESS_TIME) {
            updateDomainAccessTime(page.domain);
            for (int i = 0; i < toAddLater.size(); i++) {
                urlsToCrawl.push(toAddLater[i]);
            }
            toAddLater.clear();
            mtx.unlock();
            // cout << '\n' << "Tries: " << toAddLater.size();
            return page.url;
        } else {
            page.penalty += 1;
            toAddLater.push_back(page);
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

bool Scheduler::hasSeen (string url) {
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
    if (!hasSeen(formattedUrl)) {
        PageEntity p;
        
        try {
            p.url = formattedUrl;
            p.domain = utils.getDomain(formattedUrl);
            pair<int, time_t> domainInfo = getDomainInfo(p.domain);
            domainInfo.first += 1; // updated penalty for domain
            p.penalty = domainInfo.first; 
            p.depth = depth;
            
            if (urlsToCrawl.size() >= MAX_HEAP_SIZE)
                urlsToCrawl.pop_max();
            urlsToCrawl.push(p);
            
            // says it has now seen the url
            registeredUrls[formattedUrl] = ' ';

            // updates domain penalty
            domainLastVisit[p.domain] = domainInfo;
        } catch (int e) {
            // nothing
            cerr << '\n' << 'ERR when adding URL ' << url;
        }
    }
    mtx.unlock();
}

void Scheduler::addUrls (vector<string> urls) {
    mtx.lock();
    for (int i = 0; i < urls.size(); i++) {
        string formattedUrl = utils.formatUrl(urls[i]);
        if (!isUrlAllowed(formattedUrl)) continue;
        int depth = utils.countDepth(formattedUrl);

        if (!hasSeen(formattedUrl)) {
            PageEntity p;

            try {
                p.url = formattedUrl;
                p.domain = utils.getDomain(formattedUrl);
                pair<int, time_t> domainInfo = getDomainInfo(p.domain);
                domainInfo.first += 1; // updated penalty for domain
                p.penalty = domainInfo.first; 
                p.depth = depth;
                
                if (urlsToCrawl.size() >= MAX_HEAP_SIZE)
                    urlsToCrawl.pop_max();
                urlsToCrawl.push(p);
                
                // says it has now seen the url
                registeredUrls[formattedUrl] = ' ';

                // updates domain penalty
                domainLastVisit[p.domain] = domainInfo;
            } catch (int e) {
                // nothing
                cerr << '\n' << 'ERR when adding URL ' << url;
            }
        }        
    }
    mtx.unlock();
}

// assumes it is a well formed url taken from the scheduler
// therefore no try catch when trying to extract domain
void Scheduler::reAddUrl (string url) {
    PageEntity p;
    p.domain = utils.getDomain(url);
    p.depth = utils.countDepth(url);

    mtx.lock();
    pair<int, time_t> domainInfo = getDomainInfo(p.domain);
    domainInfo.first += 1;
    domainLastVisit[p.domain] = domainInfo;

    p.penalty = domainInfo.first;
    urlsToCrawl.push(p);
    mtx.unlock();
}

void Scheduler::setPolitenessTime(int seconds) {
    POLITENESS_TIME = seconds;
}