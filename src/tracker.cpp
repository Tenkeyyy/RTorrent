#include "./bencode/bencode.hpp"
#include "./bdecode/bdecode.hpp"
#include "./tracker/tracker.hpp"
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

#define PATH "sample.torrent"

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "Wrong usage.\n Correct usage : [command] [port number]\n";
		throw std::exception();
	}

	std::string hex_hash = getinfo_hash(PATH);

	httplib::Server serv;

	const char ip[] = "0.0.0.0";
	const int port = std::stoi(argv[1]);

	serv.Get("/announce",[hex_hash](const httplib::Request &req, httplib::Response &res){
		if(req.method == "GET") {
			std::string info_hash = req.get_param_value("info_hash");
			std::cout << "info_hash: " << info_hash << std::endl;
			if(info_hash == hex_hash)
				std::cout << "LOL\n";
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
		else {
			res.set_content("<h1> Method" + req.method + " not implemented yet </h1>","text");
		}
	});
	serv.listen(ip, port);


}
