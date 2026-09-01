#ifndef BENCODE_HPP
#define BENCODE_HPP
#include <cctype>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include "../lib/types.hpp"
#include "../lib/sha1.hpp"
#include "../bdecode/bdecode.hpp"
std::string bencd(dict d);
std::string benc(l_item item);
std::string bencl(l_item item);
std::string benci(l_item item);
std::string bencs(l_item item);
std::string dtoh(dict d);
std::string stoh(std::string s);
std::vector<std::string> splitBySize(std::string s, size_t size);
l_item getItem(dict d, l_item key);
l_item getItem(dict d, std::string k);

std::string bencs(l_item item) {
	if(item.type != 's') {
		std::cout << "Wrong type\n";
		abort();
	}
	std::string s = std::get<std::string>(item.data);
	int x = s.size();
	return (std::to_string(x) + ':' + s);
}

std::string benci(l_item item) {
	if(item.type != 'i') {
		std::cout << "Wrong type!\n";
		abort();
	}
	int x = std::get<int>(item.data);
	return 'i' + std::to_string(x) + 'e';
}

std::string bencl(l_item item) {
	if(item.type != 'l') {
		std::cout << "Wrong type!\n";
		abort();
	}
	std::vector<l_item> v = std::get<std::vector<l_item>>(item.data);
	std::string res = "l" ;
	for(size_t i = 0 ; i < v.size(); ++i) {
		if(v[i].type == 'i') {
			res += benci(v[i]);
		}
		else if(v[i].type == 's') {
			res += bencs(v[i]);
		}
		else if(v[i].type == 'l') {
			res += bencl(v[i]);
		}
	}
	return res + 'e';
}

std::string benc(l_item item) {
	if(item.type == 'i')
		return benci(item);
	else if(item.type == 's')
		return bencs(item);
	else
		return bencl(item);
}

std::string bencd(dict d) {
	std::string res = "d";
	std::map<l_item,l_item>::iterator item;
	for(item = d.begin(); item != d.end() ; ++item) {
		if(item->second.type == 's' || item->second.type == 'i' || item->second.type == 'l' )
			res += benc(item->first) + benc(item->second);
		else
			res += bencs(item->first) + bencd(std::get<dict>(item->second.data));
	}
	return res + 'e';
}

std::string dtoh(dict d) {
	SHA1 sha;
	sha.update(bencd(d));
	return sha.final();
}

std::string stoh(std::string s) {
	SHA1 sha;
	sha.update(s);
	return sha.final();
}

std::vector<std::string> splitBySize(std::string s, size_t size) {
	std::vector<std::string> res;
	for(size_t i = 0; i < s.length(); i += size) {
		res.push_back(s.substr(i, size));
	}
	return res;
}

std::string dictToUrl(dict d, std::string endpoint) {
	std::string res = endpoint + '?';

	for(dict::iterator x = d.begin(); x != d.end(); ++x) {
		res += std::get<std::string>(x->first.data) + '=';
		if (x->second.type == 'd')
			res += dtoh(std::get<dict>(x->second.data));
		else if(x->second.type == 's')
			res += std::get<std::string>(x->second.data);
		else if(x->second.type == 'i')
			res += std::get<int>(x->second.data);
	}

	return res;
}

std::string fileToUrl(const std::string path, const std::string endpoint) {
	std::ifstream torrent(path, std::ios::binary);
	if(!torrent.is_open()) {
		throw std::runtime_error("Could not open file");
	}

	std::ostringstream content;
	content << torrent.rdbuf();

	std::string s = content.str();

	size_t pos = 0;

	dict d = bdecd(s,&pos);

	return dictToUrl(d, endpoint);

}

#endif
