#include "crawler.hpp"

using namespace std;

Crawler::Crawler (vector<string> seeds, int numWorkers, int seconds, string outputPath, int pages, int pagesPerFile) {
    // seeding
    schd.addUrls(seeds);
    schd.setPolitenessTime(seconds);
    
    // output path prefix
    filePrefix = outputPath;
    if (outputPath[outputPath.size() - 1] != '/')
        filePrefix += '/';
    filePrefix += "pages_";

    pageCounter = 0;
    fileCounter = 0;
    PAGES_PER_FILE = 5;
    NUM_PAGES_TO_COLLECT = 50;

    // workers
    nWorkers = numWorkers;
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
    return pageCounter < NUM_PAGES_TO_COLLECT && schd.hasUnvisited();
}

void Crawler::savePage (string url, string html) {
    // html prep
    replace(html.begin(), html.end(), '|', ' ');

    bufferMtx.lock();
    htmlBuffer += "||| " + url + " | " + html + " ";
    pageCounter++;

    // saves buffer to file
    if (pageCounter == PAGES_PER_FILE || pageCounter >= NUM_PAGES_TO_COLLECT) {
        htmlBuffer += "|||";
        fileCounter++;
        string filename = filePrefix + to_string(fileCounter) + ".txt";
        fstream fs;
        fs.open(filename, fstream::out);
        fs << htmlBuffer;
        fs.close();
        htmlBuffer = "";
    }
    bufferMtx.unlock();
}

// thread
void Crawler::worker () {
    CkSpider spider;
    string url, domain, html;
    int size, i;

    // signal used by crawler object to stop crawling
    while (isStillCrawling()) {
        if (!schd.hasUnvisited()) {
            this_thread::sleep_for(chrono::milliseconds(100));
        } else {
            url = schd.popUrl(); // gets uncrawled URL from scheduler
            if (url.size() == 0)
                continue;

            domain = utils.getDomain(url);
            string formattedDomain = "www." + domain;
            spider.Initialize(formattedDomain.c_str());
            spider.AddUnspidered(url.c_str());
            
            // couldnt be crawled
            if (!spider.CrawlNext()) {
                schd.reAddUrl (url);
                continue;
            }

            html = spider.lastHtml(); // get page content
            savePage(url, html); // saves content

            cout << "Crawled URL " << url << ": " << html.size() << " bytes; waitingUrls size: " << schd.waitingUrls.size() << endl;

            // Inbound links
            size = spider.get_NumUnspidered();
            for (i = 0; i < size; i++) {
                url = spider.getUnspideredUrl(0);
                schd.addUrl(url);
                spider.SkipUnspidered(0); // Removes inbound link from local queue
            }

            // Outbound links
            size = spider.get_NumOutboundLinks();
            for (i = 0; i < size; i++) {
                url = spider.getOutboundLink(i);
                schd.addUrl(url);
            }

            spider.ClearOutboundLinks(); // Clears all outbound links
        }
    }
}