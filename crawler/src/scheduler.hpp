#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <ctime>
#include <mutex>
#include "utils.hpp"

class Compare {
    public:
        bool operator() (std::pair<int, std::string> p1, std::pair<int, std::string> p2) {
            return p1 > p2;
        }
};

class Scheduler {
    private:
        std::vector<std::pair<std::string, std::string> > waitingUrls;
        std::unordered_map<std::string, char> registeredUrls;
        std::unordered_map<std::string, time_t> domainLastVisit;
        std::mutex mtx;
        std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string> >, Compare> urlsToCrawl;
        
        void updateDomainAccessTime (std::string domain);
        bool domainCanBeAccessed (std::string domain);
        bool hasBeenSeen (std::string url);
        int POLITENESS_TIME; // seconds
        Utils utils;
        
    
    public:
        Scheduler ();
        bool hasUnvisited ();
        std::string popUrl ();
        void setPolitenessTime(int seconds);
        void addUrl (std::string url);
        void addUrls (std::vector<std::string> urls);
        void reAddUrl (std::string url);

};

#endif