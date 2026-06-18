#include <algorithm>
#include <cctype>
#include <string>
#include <variant>
#include <vector>
#include <string>
#include <iostream>
#include <map>

struct l_item {
	std::variant<int,std::string,std::vector<l_item>,std::map<l_item, l_item>> data;
	char type;
	bool operator<(const l_item& other) const {
	if(!std::holds_alternative<std::string>(this->data) || !std::holds_alternative<std::string>(other.data)) {
		throw std::runtime_error("Dictionary keys must be strings!");
	}
	std::string s1 = std::get<std::string>(this->data);
	std::string s2 = std::get<std::string>(other.data);
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	return s1 < s2;
	}
};

typedef std::variant<int, std::string, std::vector<l_item>> item_t;
typedef std::map<l_item, l_item> dict;

void insert_int(std::vector<l_item> *dest, const std::string& s, size_t *pos);
void insert_string(std::vector<l_item> *dest, const std::string& s, size_t *pos);
int bdeci(const std::string& s, size_t *pos);
std::string bdecs(const std::string& s, size_t *pos);
void printlist(std::vector<l_item> l);
std::vector<l_item> bdecl(const std::string& s, size_t *pos);
dict bdecd(const std::string& s, size_t *pos);
void printdict(dict d);
