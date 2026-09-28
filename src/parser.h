#ifndef PARSER_H
#define PARSER_H

#include <string>

class Lexer {
    public:
        std::string method;
        std::string target;
        std::string protocol;

        void get_rqst_tokens (char* buffer);
};
        
#endif
