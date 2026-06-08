#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "bdecode.hpp"

bool isnum(char c) {
	if( c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
		return true;
	return false;
}

std::string bdecs(std::string s, size_t *pos) {
	std::string chars = "";
	size_t i = *pos;
	while(s[i] != ':') {
		chars += s[i];
		++i;
	}

	++i;

	size_t size = std::stoi(chars);

	std::string res = "";
	size_t j = 0;
	for(j = 0; j < size; ++j) {
		res += s[i+j];
	}

	int newpos = i+j;
	*pos = newpos;
	return res;
}

int bdeci(std::string s, size_t *pos) {
	std::string nums = "";
	size_t i = *pos + 1;
	while(s[i] != 'e') {
		nums += s[i];
		++i;
	}
	*pos = i + 1;
	return std::stoi(nums);
}

std::vector<l_item> bdecl(std::string s, size_t *pos) {
	size_t i = *pos + 1;
	std::vector<l_item> res;
	l_item item;

	while(s[i] != 'e') {
		if(s[i] == 'l') {
			std::vector<l_item> *list = (std::vector<l_item> *) malloc(sizeof(std::vector<l_item>));
			*list = bdecl(s,&i);
			item.data = (void *) list;
			item.type = 'l';
			res.push_back(item);
		}
		else if(s[i] == 'i') {
			item.type = 'i';
			int *ptr = (int *) malloc(sizeof(int));
			int temp = bdeci(s,&i);
			*ptr = temp;
			item.data = (void *) ptr;
			res.push_back(item);
		}
		else if(isnum(s[i])) {
			item.type = 's';
			std::string *data = (std::string *) malloc(sizeof(std::string));
			std::string temp = bdecs(s,&i);
			*data = temp;
			item.data = (void *) data;
			res.push_back(item);
		}

	}
	*pos = i+1;
	return res;
}

void printlist(std::vector<l_item> l) {
	for(size_t i = 0 ; i < l.size() ; ++i) {
		if(l[i].type == 'l') {
			printlist(*( (std::vector<l_item> *) l[i].data ));
		}
		else if (l[i].type == 'i') {
			std::cout << *((int *) l[i].data) << std::endl ;
		}
		else if (l[i].type == 's') {
			std::cout << *((std::string *) l[i].data) << std::endl ;
		}
	}
}
