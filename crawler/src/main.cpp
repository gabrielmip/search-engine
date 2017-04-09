#include <iostream>
#include <vector>
#include <string>
#include "chilkat/include/CkSpider.h"
#include "chilkat/include/CkString.h"
#include "scheduler.hpp"
//#include "crawler.hpp"

using namespace std;

int main(){

	Scheduler s;
	s.popUrl();
	return 0;

	CkSpider spider;
	string html, url;
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
}