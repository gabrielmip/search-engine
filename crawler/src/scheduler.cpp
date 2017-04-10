#include "scheduler.hpp"

using namespace std;

Scheduler::Scheduler () {}

bool Scheduler::hasUnvisited () {
    return urlsToCrawl.size() > 0 || waitingUrls.size() > 0;
}

string Scheduler::popUrl () {
    vector<pair<string, string> >::iterator it;

    mtx.lock();

    // checks if any page waiting to be crawled
    // because of politeness is now ready
    for (it = waitingUrls.begin(); it != waitingUrls.end(); it++) {
        string url = it->first;
        string domain = it->second;

        if (domainCanBeAccessed(domain)) {
            updateDomainAccessTime(domain);
            waitingUrls.erase(it);
            mtx.unlock();
            return url;
        }
        
    }

    // if no page waiting the politeness time,
    // looks for a page to collect in the main
    // url list
    if (urlsToCrawl.size() == 0) {
        mtx.unlock();
        return ""; // to be treated on thread function
    } else {
        pair<int, string> item;
        while (urlsToCrawl.size() > 0) {
            item = urlsToCrawl.top();
            urlsToCrawl.pop();

            string url = item.second;
            string domain = utils.getDomain(url);

            if (domainCanBeAccessed(domain)) {
                updateDomainAccessTime(domain);
                mtx.unlock();
                return url;
            } else {
                // url cant be accessed bc of politeness
                waitingUrls.push_back(make_pair(url, domain));
            }
        }
    }

    // if has gotten to here, wasn't able to successfully
    // return a page url
    mtx.unlock();
    return "";
}

void Scheduler::updateDomainAccessTime (string domain) {
    // get current time
    time_t now;
    time(&now);
    domainLastVisit[domain] = now;
}

bool Scheduler::domainCanBeAccessed (string domain) {
    unordered_map<string, time_t>::iterator it = domainLastVisit.find(domain);
    if (it == domainLastVisit.end()) {
        return true;
    } else {
        time_t lastVisit = it->second;
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

void Scheduler::addUrl (string url) {
    string formattedUrl = utils.formatUrl(url);

    mtx.lock();
    if (!hasBeenSeen(formattedUrl)) {
        int depth = utils.countDepth(formattedUrl);
        registeredUrls[formattedUrl] = ' ';
        urlsToCrawl.push(make_pair(depth, formattedUrl));
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
    string domain = utils.getDomain(url);
    waitingUrls.push_back(make_pair(url, domain));
    mtx.unlock();
}

void Scheduler::setPolitenessTime(int seconds) {
    POLITENESS_TIME = seconds;
}