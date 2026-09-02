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


	httplib::Client cli("http://localhost:8080");

	std::string url = fileToUrl(argv[1], "/announce");

	std::cout << url;

	if(auto res = cli.Get(url.c_str())) {
		std::cout << res->status;
		std::cout << res->body;
	}

	return 0;
}
