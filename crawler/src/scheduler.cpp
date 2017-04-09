#include "scheduler.hpp"

using namespace std;

Scheduler::Scheduler () {}

bool Scheduler::hasUnvisited () {
    return urlsToCrawl.size() > 0 || waitingUrls.size() > 0;
}

string Scheduler::popUrl () {
    list<pair<string, string> >::iterator it;
    //priority_queue<pair<int, string> >::iterator it2;

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
            string domain = utils.extractUrlDomain(url);

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
    try {
        time_t lastVisit = domainLastVisit[domain];
        time_t now;
        time(&now);
        if (now - lastVisit < POLITENESS_TIME) {
            return false;
        } else return true;
    } catch (const out_of_range& oor) {
        return true;
    } catch (int e) {
        cerr << "Exception n. " << e << " occurred. Exiting now." << endl;
        exit (EXIT_FAILURE);
    }
}

bool Scheduler::hasBeenSeen (string url) {
    try {
        char c = registeredUrls[url];
        return true;
    } catch (const out_of_range& oor) {
        return false;
    }
}

void Scheduler::addUrl (string url) {
    if (!hasBeenSeen(url)) {
        int nComponents = utils.countComponents(url);

        mtx.lock();
        registeredUrls[url] = '';
        urlsToCrawl.push(make_pair(nComponents, url));
        mtx.unlock();
    }
}

void Scheduler::addUrls (list<string> urls) {
    mtx.lock();
    for (int i = 0; i < urls.size(); i++) {
        if (!hasBeenSeen(urls[i])) {
            int nComponents = utils.countComponents(urls[i]);
            registeredUrls[urls[i]] = '';
            urlsToCrawl.push(make_pair(nComponents, urls[i]));
        }
    }
    mtx.unlock();    
}

void Scheduler::setPolitenessTime(int seconds) {
    POLITENESS_TIME = seconds;
}