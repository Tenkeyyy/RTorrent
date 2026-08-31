#include "./bencode/bencode.hpp"
#include "./bdecode/bdecode.hpp"
#include "./lib/httplib.h"
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cout << "Wrong usage\n";
		throw std::exception();
	}
	std::ifstream torrent(argv[1], std::ios::binary);

	if(!torrent.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::ostringstream content;
	content << torrent.rdbuf();

	std::string s = content.str();

	size_t pos = 0;
	dict d = bdecd(s, &pos);
	printItem(d);

	dict info = std::get<dict>(getItem(d, "info").data);

	printItem(getItem(info, "pieces"));

	httplib::Client cli("http://yhirose.github.io");

	if(auto res = cli.Get("/hi")) {
		std::cout << res->status;
		std::cout << res->body;
	}

	return 0;
}
