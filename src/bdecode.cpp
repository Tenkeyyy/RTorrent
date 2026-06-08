#include <string>

std::string bdecs(std::string s) {
	std::string chars = "";
	size_t i = 0;
	while(s[i] != ':') {
		chars += s[i];
		++i;
	}

	++i;

	size_t size = std::stoi(chars);

	std::string res = "";

	for(size_t j = 0; j < size; ++j) {
		res += s[i+j];
	}

	return res;
}
