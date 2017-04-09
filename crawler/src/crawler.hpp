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

// thread
void worker (Scheduler schd);

class Crawler {
    public:
        Crawler ();
        Crawler (std::vector<std::string> seeds, int numWorkers, int politeness, std::string outputPath);
        void seed (std::vector<std::string> seeds);
        void start ();
        void setNumWorkers (int amount);
        void setPolitenessTime (int seconds);
        void setOutputFolder (std::string path);
        bool isStillCrawling ();
        void savePage (std::string url, std::string html);


    private:
        std::thread *workers;
        Scheduler schd;
        bool stillCrawling;
        std::string htmlBuffer;
        std::string filePrefix;
        int fileCounter;
        std::mutex bufferMtx;
        int PAGES_PER_FILE;
        int NUM_PAGES_TO_COLLECT;

};

#endif