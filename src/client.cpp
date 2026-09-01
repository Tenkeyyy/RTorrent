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

	std::string url = "/announce?info_hash=a8aa9aa2eda98fbc4a9685bb6b4610e865d38e80&peer_id=-CC0001-123456789012&port=6881&uploaded=0&downloaded=0&left=92063&compact=1";

	if(auto res = cli.Get(url.c_str())) {
		std::cout << res->status;
		std::cout << res->body;
	}

	return 0;
}
