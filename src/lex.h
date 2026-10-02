#ifndef LEX_H
#define LEX_H

#include <string>

class Lexer {
public:
	std::string method;
	std::string target;
	std::string protocol;

	void get_req_tokens(char* buffer);
};

#endif
