#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "crawler.hpp"

using namespace std;

vector<string> readSeedFile (string path) {
	fstream fs;
	string line;
	vector<string> seeds;

	fs.open(path, fstream::in);
	while (!fs.eof()) {
		fs >> line;
		seeds.push_back(line);
	}
	return seeds;
}

int main(int argc, char **argv){

	
	vector<string> seeds = readSeedFile(argv[1]);
	int nworkers = atoi(argv[2]);
	int seconds = 30;
	string outputPath = argv[3];
	int pages = atoi(argv[4]);
	int pagesPerFile = atoi(argv[5]);
	string logPath = argv[6];
	
	/*
	string url;
	Utils u;
	CkSpider spider;
	Scheduler s;
	s.addUrls(seeds);
	while(s.hasUnvisited()) {
		url = s.popUrl();
		cout << url << endl;
		cout << u.getDomain(url) << endl;
		
		spider.Initialize(spider.getBaseDomain(url.c_str()));
		spider.AddUnspidered(url.c_str());
		if (spider.CrawlNext()) {
			cout << "worked" << endl;
		} else {
			cout << "didnt work" << endl;
		}
	}
	*/


	/*
	Scheduler s;
	Utils u;
	string url, formatted;
	CkSpider spider;
	s.addUrls(seeds);
	while(s.hasUnvisited()) {
		url = s.popUrl();
		formatted = u.formatUrl(url);
		spider.Initialize(u.getDomain(formatted).c_str());
		spider.AddUnspidered(formatted.c_str());
		if (spider.CrawlNext()) {
			cout << "worked "<< endl;
		} else {
			cout << " didnt work"<< endl;
		}
		cout << u.getDomain(formatted) << endl;
		cout << u.formatUrl(formatted) << endl;
	}
	*/
	

	Crawler crawler (seeds, nworkers, seconds, outputPath, pages, pagesPerFile, logPath);
	crawler.start();
}