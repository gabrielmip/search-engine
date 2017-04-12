#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <ctime>
#include <mutex>
#include <tuple>
#include "utils.hpp"
#include "min_max_heap.h"

class Compare {
    public:
        bool operator() (std::pair<int, std::string> p1, std::pair<int, std::string> p2) {
            return p1 > p2;
        }
};

class Scheduler {
    private:
        std::unordered_map<std::string, char> registeredUrls;
        std::unordered_map<std::string, std::pair<int, std::time_t> > domainLastVisit;
        // std::vector<std::pair<std::string, std::string> > waitingUrls;
        std::mutex mtx;
        std::vector<std::string> allowedUrls;
        std::vector<std::string> notAllowedUrls;
        MinMaxHeap<std::tuple<std::string, int, std::time_t> > urlsToCrawl;
        
        bool isUrlAllowed (std::string url);
        void updateDomainAccessTime (std::string domain);
        bool domainCanBeAccessed (std::string domain);
        bool hasBeenSeen (std::string url);
        int POLITENESS_TIME; // seconds
        int MAX_HEAP_SIZE;
        Utils utils;
        
    
    public:
        Scheduler (int size);
        bool hasUnvisited ();
        std::string popUrl ();
        void setPolitenessTime(int seconds);
        void addUrl (std::string url);
        void addUrls (std::vector<std::string> urls);
        void reAddUrl (std::string url);
        std::pair<int, std::time_t> getDomainInfo (std::string domain);

};

#endif