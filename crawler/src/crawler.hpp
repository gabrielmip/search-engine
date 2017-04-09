#ifndef CRAWLER_HPP
#define CRAWLER_HPP

#include <iostream>
#include <string>
#include <thread>
#include <vector>
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

    private:
        std::thread *workers;

};

#endif