#include "lex.h"
#include <string>
#include <cstring>
#include <iostream>

void Lexer::get_rqst_tokens (char* buffer)
{
    //TODO: refactor this whole function

    char* token = std::strtok(buffer, " \n\r\t");
    if (!token){
        std::cout << "broken\n";
        exit(1);
    }
    method = token;
    std::cout << "method: " << method << '\n';

    token = std::strtok(nullptr, " \n\r\t");
    if (!token){
        std::cout << "broken\n";
        exit(1);
    }
    target = token;
    std::cout << "target: " << target << '\n';

    token = std::strtok(nullptr, " \n\r\t");
    if (!token){
        std::cout << "broken\n";
        exit(1);
    }
    protocol = token;
    std::cout << "protocol: " << protocol << '\n';
}
