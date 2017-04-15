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

	Crawler crawler (seeds, nworkers, seconds, outputPath, pages, pagesPerFile, logPath);
	crawler.start();


	/*
	Scheduler s (10);
	Utils u;
	string url, formatted;
	CkSpider spider;
	string form = spider.canonicalizeUrl("http:////www.chilkatsoft.com///purchase2.asp#buyZip");
	cout << spider.getUrlDomain(u.formatUrl("http:////www.chilkatsoft.com///purchase2.asp#buyZip").c_str());
	return 0;
	cout << spider.canonicalizeUrl("http:////www.chilkatsoft.com///purchase2.asp#buyZip") << "\r\n";
	vector<string> seeds = readSeedFile(argv[1]);
	for (int i = 0; i < seeds.size(); i++) {
		cout << seeds[i] << '\n';
		cout << u.formatUrl(seeds[i]) <<'\n';
		formatted = u.formatUrl(seeds[i]);
		cout << u.getDomain(formatted) << '\n';
		continue;
	}
	return 0;
	s.addUrls(seeds);
	while(s.hasUnvisited()) {
		url = s.popUrl();
		formatted = u.formatUrl(url);
		cout << url << ' ' << formatted << ' ';
		cout << u.getDomain(formatted) << '\n';
		spider.Initialize(u.getDomain(formatted).c_str());
		spider.AddUnspidered(formatted.c_str());
		if (spider.CrawlNext()) {
			cout << "worked "<< '\n';
		} else {
			cout << " didnt work"<< '\n';
		}
		cout << u.getDomain(formatted) << '\n';
		cout << u.formatUrl(formatted) << '\n';
	}
	*/
}