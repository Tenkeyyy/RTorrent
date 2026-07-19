#include <algorithm>
#include <cctype>
#include <string>
#include <variant>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <map>
#include "../types.hpp"

void insert_int(std::vector<l_item> *dest, const std::string& s, size_t *pos);
void insert_string(std::vector<l_item> *dest, const std::string& s, size_t *pos);
int bdeci(const std::string& s, size_t *pos);
std::string bdecs(const std::string& s, size_t *pos);
void printlist(std::vector<l_item> l);
std::vector<l_item> bdecl(const std::string& s, size_t *pos);
dict bdecd(const std::string& s, size_t *pos);
void printdict(dict d);
