//TODO: check if all these headers are required
#include "net.h"
#include "lex.h"
#include <iostream>
#include <string>
#include <array>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h> // open(), write(), close()

Network::Network (void)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1) {
        std::cout << "(Socket error)\n";
        exit(1);
    }

    sockaddr_in serv_addr;
    int port = 8080;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
        std::cout << "(Socket bind failed)\n";
        exit(1);
    }
}

void Network::Listen ()
{
    if (listen(sockfd, SOMAXCONN) != 0) {
        std::cout << "(Couldn't listen)\n";
        exit(1);
    }

    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (1) {
        clientfd = accept(sockfd, (sockaddr *)&client_addr, &client_len);

        if (clientfd < 0) {
            std::cout << "(Accept error)\n";
            exit(1);
        }
        std::cout << "(Accept success)\n";
        break;
    }
}

void Network::Response (void)
{
    //TODO: is this the most optimal buffer?
    char buffer[8192];

    ssize_t request = read(clientfd, buffer, 8192);
    std::cout << "(ssize_t request: " << request << ")\n";

    if (request <= 0) {
        std::cout << "(Request contains no data or read error)\n";
        exit(1);
    }
    //TODO
    //
    std::cout << buffer << "\n";

    //TODO: Refactor and move the below code
    /*
    FILE *fptr;
    fptr = fopen"/tmp/request09842089303", "w";
    if (!fptr) {
        std::cout << "(fopen error)\n";
        exit(1);
    }
    fwrite(buffer, sizeof(char), request, fptr);
    fclose(fptr);
    */

    Lexer lexer;
    lexer.get_rqst_tokens(buffer); // todo

    std::string response_message =
        "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html\">\n<body>\n<h1>My First Heading</h1>\n<p>My first paragraph.</p>\n</body>\n<head>\n</html>";

    ssize_t response;
    std::string get_str("GET");

    if ((lexer.method.compare(get_str)) == 0) {
        response = write(clientfd, response_message.data(), response_message.size());
        if (response < 0) {
            std::cout << "(Data wasn't written to target)\n";
            exit(1);
        }
        std::cout << "(Data sent to target)\n";
    } else {
        std::cout << "(method did not match GET)\n";
        std::cout << lexer.method;
        exit(1);
    }

    close(clientfd);
}

Network::~Network()
{
    if (sockfd)
        close(sockfd);
    if (clientfd)
        close(clientfd);
}
