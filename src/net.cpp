//TODO: check if all these headers are required
#include "net.h"
#include "lex.h"
#include "assets.h"
#include <iostream>
#include <string>
#include <array>
#include <fstream>
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
        std::cout << "\n(Accept success)\n";
        break;
    }
}

void Network::Response (void)
{
    //TODO: is this the most optimal buffer?
    char buffer[8192];

    ssize_t request = read(clientfd, buffer, 8192);

    if (request <= 0) {
        std::cout << "(Request contains no data or read error)\n";
        exit(1);
    }

    Lexer lexer;
    lexer.get_req_tokens(buffer); // todo

    Assets assets;
    std::string payload = assets.res_route(lexer.target);

    ssize_t response;
    // std::string get_str("GET");

    if ((lexer.method.compare("GET")) == 0) {
        response = write(clientfd, payload.data(), payload.size());
        if (response < 0) {
            std::cout << "(Data wasn't written to target)\n";
            exit(1);
        }
        std::cout << "(Data sent to target)\n";
    } else {
        std::cout << "(method did not match GET)\n";
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
