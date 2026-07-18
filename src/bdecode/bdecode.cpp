#include <cstdlib>
#include <ostream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <variant>
#include "bdecode.hpp"


bool isnum(char c) {
	if( c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
		return true;
	return false;
}

#define BENCODE_ERR -1

std::string bdecs(const std::string& s, size_t *pos) {
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

	*pos = i+j;
	return res;
}

int bdeci(const std::string& s, size_t *pos) {
	std::string nums = "";
	size_t i = *pos + 1;
	while(s[i] != 'e') {
		nums += s[i];
		if(!isnum(s[i])) {
			std::cout << "Not a valid bencoding\n";
			errno = BENCODE_ERR;
			return 0;
		}
		++i;
		if(i == s.length()) {
			std::cout << "Not a valid bencoding\n";
			errno = BENCODE_ERR;
			return 0;
		}
	}
	*pos = i + 1;
	return std::stoi(nums);
}

void insert_int(std::vector<l_item> *dest, const std::string& s, size_t *pos) {
	l_item item;
	item.type = 'i';
	int temp = bdeci(s,pos);
	item.data =  temp;
	(*dest).push_back(item);
}

l_item insert_int(dict *d, l_item *i, const std::string& s, size_t *pos) {
	l_item item;
	item.type = 'i';
	int temp = bdeci(s,pos);
	item.data = temp;
	if(i == nullptr)
		(*d)[item] = item;
	else {
		(*d)[*i] = item;
		*i = item;
	}
	return item;
}

void insert_string(std::vector<l_item> *dest, const std::string& s, size_t *pos) {
	l_item item;
	item.type = 's';
	std::string temp = bdecs(s,pos);
	item.data = temp;
	(*dest).push_back(item);
}

l_item insert_string(dict *d, l_item *i, const std::string& s, size_t *pos) {
	l_item item;
	item.type = 's';
	std::string temp = bdecs(s,pos);
	item.data = temp;
	if(i == nullptr)
		(*d)[item] = item;
	else {
		(*d)[*i] = item;
		*i = item;
		std::cout << "Inserted a value\n";
	}
	return item;
}

l_item insert_list(dict*d, l_item *i, const std::string& s, size_t *pos) {
	l_item item;
	item.type = 'l';
	item.data = bdecl(s,pos);
	if(i == nullptr)
		(*d)[item] = item;
	else {
		(*d)[*i] = item;
		*i = item;
	}
	return item;
}

std::vector<l_item> bdecl(const std::string& s, size_t *pos) {
	size_t i = *pos + 1;
	std::vector<l_item> res;
	l_item item;

	while(s[i] != 'e') {
		if(s[i] == 'l') {
			item.data =  bdecl(s,&i);
			item.type = 'l';
			res.push_back(item);
		}
		else if(s[i] == 'i') {
			insert_int(&res, s, &i);
		}
		else if(isnum(s[i])) {
			insert_string(&res, s, &i);
		}
		if(i >= s.length()-1)
			break;
	}
	*pos = i+1;
	return res;
}

l_item insert_dict(dict*d, l_item *i, const std::string& s, size_t *pos) {
	l_item item;
	item.type = 'd';
	item.data = bdecd(s,pos);
	if(i == nullptr)
		(*d)[item] = item;
	else {
		l_item curr = *i;
		(*d)[curr] = item;
	}
	*i = item;
	return item;
}

dict bdecd(const std::string& s, size_t *pos) {
	size_t i = *pos + 1;
	dict res;
	l_item item, curr;
	short index = 0;
	while(s[i] != 'e') {
		if(s[i] == 'l') {
			if(index % 2 == 0) {
				curr = insert_list(&res,nullptr,s,&i);
				index = (index + 1) % 2;
			}
			else {
				insert_list(&res,&curr,s,&i);
				index = (index + 1) % 2;
			}
		}
		else if(s[i] == 'i') {
			if(index % 2 == 0) {
				curr = insert_int(&res,nullptr,s,&i);
				index = (index + 1) % 2;
			}
			else {
				insert_int(&res,&curr,s,&i);
				index = (index + 1) % 2;
			}
		}
		else if(isnum(s[i])) {
			if(index % 2 == 0) {
				curr = insert_string(&res,nullptr,s,&i);
				index = (index + 1) % 2;
			}
			else {
				insert_string(&res,&curr,s,&i);
				index = (index + 1) % 2;
			}
		}
		else if(s[i] == 'd') {
			if(index % 2 == 0) {
				curr = insert_dict(&res,nullptr,s,&i);
				index = (index + 1) % 2;
			}
			else {
				insert_dict(&res,&curr,s,&i);
				index = (index + 1) % 2;
			}

		}
		if(i >= s.length()-1)
			break;
	}
	*pos = i+1;
	return res;
}

void printlist(std::vector<l_item> l) {
	for(size_t i = 0 ; i < l.size() ; ++i) {
		if(l[i].type == 'l') {
			printlist(std::get<std::vector<l_item>>(l[i].data));
		}
		else if (l[i].type == 'i') {
			std::cout << std::get<int>(l[i].data) << std::endl ;
		}
		else if (l[i].type == 's') {
			std::cout << std::get<std::string>(l[i].data)<< std::endl ;
		}
	}
}

void printdict(dict d) {
	std::map<l_item,l_item>::iterator item;
	std::cout << '{' << std::endl;
	for( item = d.begin(); item != d.end(); item++) {
		std::cout << std::get<std::string>(item->first.data) << " : " ;
		if(item->second.type == 's') {
			std::cout << std::get<std::string>(item->second.data) << std::endl ;
		}
		else if (item->second.type == 'i') {
			std::cout << std::get<int>(item->second.data) << std::endl ;
		}
		else 
			printdict(std::get<dict>(item->second.data));
		
	}
	std::cout << '}' << std::endl;
}

l_item getItem(dict d, l_item key) {
	return d.at(key);
}

l_item getItem(dict d, std::string k) {
	std::map<l_item,l_item>::iterator item;
	for(item = d.begin(); item != d.end(); ++item) {
		if(std::get<std::string>(item->first.data) == k) {
			return item->second;
		}
	}
	l_item l ;
	l.type = 'e';
	return l;
}
