#ifndef BENCODE_HPP
#define BENCODE_HPP
#include <algorithm>
#include <cctype>
#include <string>
#include <variant>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include "../lib/types.hpp"
#include "../lib/sha1.hpp"

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

#endif
