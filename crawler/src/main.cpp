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

	// args to crawler
	vector<string> seeds = readSeedFile(argv[1]);
	int nworkers = atoi(argv[2]);
	string outputPath = argv[3];
	int pages = atoi(argv[4]);
	int pagesPerFile = atoi(argv[5]);
	string logPath = argv[6];
	int seconds = 30; // politeness

	Crawler crawler (seeds, nworkers, seconds, outputPath, pages, pagesPerFile, logPath);
	crawler.start();
}