#include "./bencode/bencode.hpp"
#include "./bdecode/bdecode.hpp"
#include "./lib/httplib.h"
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

void announceHandler(const httplib::Request &req, httplib::Response &res) {
	if(req.method == "GET") {
		std::string info_hash = req.get_param_value("info_hash");
		std::cout << "info_hash: " << info_hash << std::endl;
		std::string peer_id = req.get_param_value("peer_id");
		std::cout << "peer_id: " << peer_id << std::endl;
		std::string port = req.get_param_value("port");
		std::cout << "port: " << port << std::endl;
		std::string uploaded = req.get_param_value("uploaded");
		std::cout << "uploaded: " << uploaded << std::endl;
		std::string downloaded = req.get_param_value("downloaded");
		std::cout << "downloaded: " << downloaded << std::endl;
		std::string left = req.get_param_value("left");
		std::cout << "left: " << left << std::endl;
		std::string compact = req.get_param_value("compact");
		std::cout << "compact: " << compact << std::endl;
		res.set_content(req.method, "text");
	}
}

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "Wrong usage.\n Correct usage : [command] [port number]\n";
		throw std::exception();
	}
	httplib::Server serv;

	std::unordered_map<std::string, std::string> map;

	const char ip[] = "0.0.0.0";
	const int port = std::stoi(argv[1]);

	serv.Get("/announce", announceHandler);
	serv.listen(ip, port);


}
