#include "crawler.hpp"

using namespace std;

Crawler::Crawler (vector<string> seeds, int numWorkers, int seconds, 
                  string outputPath, int pages, int pagesPerFile, string logPath) {
    
    // seeding
    schd = new Scheduler(1000000);
    schd->addUrls(seeds);
    schd->setPolitenessTime(seconds);
    
    // output path prefix
    filePrefix = outputPath;
    if (outputPath[outputPath.size() - 1] != '/')
        filePrefix += '/';
    filePrefix += "pages_";

    pageCounter = 0;
    fileCounter = 0;
    PAGES_PER_FILE = pagesPerFile;
    NUM_PAGES_TO_COLLECT = pages;

    // workers
    nWorkers = numWorkers;

    // log
    utils.setLogPath(logPath);
}

void Crawler::start () {
    for (int i = 0; i < nWorkers; i++) {
        workers.push_back(thread(&Crawler::worker, this));
    }

    for(vector<thread>::iterator it = workers.begin(); it != workers.end(); it++) {
        it->join();
    }

    cout << "Over." << endl;
}

bool Crawler::isStillCrawling () {
    return pageCounter < NUM_PAGES_TO_COLLECT && schd->hasUnvisited();
}

bool bothAreSpaces (char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
}

void Crawler::savePage (string url, string html) {
    // remove pipes
    replace(html.begin(), html.end(), '|', ' ');
    
    // remove duplicate spaces to save memory
    string::iterator newEnd = unique(html.begin(), html.end(), bothAreSpaces);
    html.erase(newEnd, html.end());

    bufferMtx.lock();
    htmlBuffer += "||| " + url + " | " + html + " ";
    utils.log(url);
    pageCounter++;

    // saves buffer to file
    if (pageCounter % PAGES_PER_FILE == PAGES_PER_FILE - 1 || pageCounter >= NUM_PAGES_TO_COLLECT) {
        fileCounter++;
        htmlBuffer += "|||";
        string filename = filePrefix + to_string(fileCounter) + ".txt";
        fstream fs;
        fs.open(filename, fstream::out);
        fs << htmlBuffer;
        fs.close();
        htmlBuffer.clear();
        utils.dumpLog();
    }
    bufferMtx.unlock();
}

// thread
void Crawler::worker () {
    CkSpider spider;
    spider.put_AvoidHttps(true);
    spider.put_ConnectTimeout(5);

    string url, domain, html;
    int size, i;

    // signal used by crawler object to stop crawling
    while (isStillCrawling()) {
        if (!schd->hasUnvisited()) {
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }


        url = schd->popUrl(); // gets uncrawled URL from scheduler
        if (url.size() == 0)
            continue;

        domain = utils.getDomain(url);
        spider.Initialize(domain.c_str());
        spider.AddUnspidered(url.c_str());
        
        // couldnt be crawled
        if (!spider.CrawlNext()) {
            schd->reAddUrl (url);
            cout << endl << "ERR: " << url << " - " << domain;
            continue;
        }

        html = spider.lastHtml(); // get page content
        savePage(url, html); // saves content

        cout << endl << "SUC " << pageCounter  << ": " << url;

        // Inbound links
        size = spider.get_NumUnspidered();
        for (i = 0; i < size; i++) {
            url = spider.getUnspideredUrl(0);
            schd->addUrl(url);
            spider.SkipUnspidered(0); // Removes inbound link from local queue
        }

        // Outbound links
        size = spider.get_NumOutboundLinks();
        for (i = 0; i < size; i++) {
            url = spider.getOutboundLink(i);
            schd->addUrl(url);
        }

        spider.ClearOutboundLinks(); // Clears all outbound links
    }
}