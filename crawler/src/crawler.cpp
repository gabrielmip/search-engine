#include "crawler.hpp"

using namespace std;

// thread
void worker (Crawler crw, Scheduler schd) {
    CkSpider spider;
    Utils utils;
    string url, domain, html;
    int size, i;

    // signal used by crawler object to stop crawling
    while (crw.isStillCrawling()) {
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
            spider.CrawlNext();
            html = spider.lastHtml(); // get page content
            crw.savePage(url, html); // saves content

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

Crawler::Crawler () {}

Crawler::Crawler (vector<string> seeds, int numWorkers, int politeness, string outputPath) {

}

void Crawler::seed (vector<string> seeds) {

}

void Crawler::start () {

}

void Crawler::setNumWorkers (int amount) {

}

void Crawler::setPolitenessTime (int seconds) {

}

void Crawler::setOutputFolder (string path) {

}

bool Crawler::isStillCrawling () {
    return stillCrawling;
}

void Crawler::savePage (string url, string html) {
    // html prep
    replace(html.begin(), html.end(), '|', ' ');

    bufferMtx.lock();
    htmlBuffer += "||| " + url + " | " + html + " ";
    fileCounter += 1;

    // saves buffer to file
    if (fileCounter == PAGES_PER_FILE) {
        htmlBuffer += "|||";
        string filename = filePrefix + to_string(fileCounter) + ".txt";
        fstream fs;
        fs.open(filename, fstream::out);
        fs << htmlBuffer;
        fs.close();
        htmlBuffer = "";
    }
    bufferMtx.unlock();
}