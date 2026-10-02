#include "lex.h"
#include <string>
#include <cstring>
#include <iostream>

void Lexer::get_req_tokens (char* buffer)
{
    //TODO: refactor this whole function

    char* token = std::strtok(buffer, " \n\r\t");
    if (!token){
        std::cout << "broken\n";
        exit(1);
    }
    method = token;

    token = std::strtok(nullptr, " \n\r\t");
    if (!token){
        std::cout << "broken\n";
        exit(1);
    }
    target = token;

    token = std::strtok(nullptr, " \n\r\t");
    if (!token){
        std::cout << "broken\n";
        exit(1);
    }
    protocol = token;
}
