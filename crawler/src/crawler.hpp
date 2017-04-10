#ifndef CRAWLER_HPP
#define CRAWLER_HPP

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <fstream>
#include "scheduler.hpp"

class Crawler {
    public:
        Crawler (std::vector<std::string> seeds, int numWorkers, int politeness, std::string outputPath, int pages, int pagesPerFile);
        void start ();
        bool isStillCrawling ();
        void savePage (std::string url, std::string html);

    private:
        std::vector<std::thread> workers;
        Scheduler schd;
        std::string htmlBuffer;
        std::string filePrefix;
        int pageCounter;
        int fileCounter;
        std::mutex bufferMtx;
        int PAGES_PER_FILE;
        int NUM_PAGES_TO_COLLECT;
        int nWorkers;
        void worker (); // thread
        Utils utils;

};

#endif