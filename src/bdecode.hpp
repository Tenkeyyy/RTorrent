#include <string>
#include <vector>
#include <string>
#include <iostream>

struct l_item {
	void *data;
	char type;
};

int bdeci(std::string s, size_t *pos);
std::string bdecs(std::string s, size_t *pos);
void printlist(std::vector<l_item> l);
std::vector<l_item> bdecl(std::string s, size_t *pos);
