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
	
	/*
	Scheduler s;
	s.addUrls(seeds);
	while(s.hasUnvisited()) {
		cout << s.popUrl() << endl;
	}
	*/

	Crawler crawler (seeds, nworkers, seconds, outputPath);
	crawler.start();

	/*
	CkSpider spider;
	string html;
	// string url;
	vector<string> queue;

	spider.Initialize("www.chilkatsoft.com");
	spider.AddUnspidered("http://www.chilkatsoft.com/");
	spider.CrawlNext(); // bool return

	int size = spider.get_NumUnspidered();

	html = spider.lastHtml(); // Saves HTML

	//cout << "Crawled HTML: " << html << '\n';

	// Inbound links
	for (int i = 0; i < size; i++) {
		url = spider.getUnspideredUrl(0);
		spider.SkipUnspidered(0); // Removes inbound link from local queue
		cout << "Crawled URL: " << url << '\n';
	}

	// Outbound links
	size = spider.get_NumOutboundLinks();
	for (int i = 0; i < size; i++) {
		url = spider.getOutboundLink(i);
		cout << "Crawled outbound URL: " << url << '\n';
	}

	spider.ClearOutboundLinks(); // Clears all outbound links
	*/
}