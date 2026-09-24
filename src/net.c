#include "parser.h"
#include <errno.h>
#include <fcntl.h> // File control options
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h> // open(), write(), close()

int net_init(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("(Socket error)\n");
		return 1;
	}

	struct sockaddr_in serv_addr;
	uint16_t port = 8080;

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
		printf("(Socket bind failed)\n");
		return 1;
	}

	return sockfd;
}

int net_listen(int sockfd)
{
	if (listen(sockfd, SOMAXCONN) != 0) {
		printf("(Couldn't listen)\n");
		return 1;
	}

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int clientfd;

	while (1) {
		clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);

		if (clientfd < 0) {
			printf("(Accept error)\n");
			return 1;
		}
		printf("(Accept success)\n");
		break;
	}

	return clientfd;
}

int net_action(int clientfd, char *buffer, int buffer_size)
{
	ssize_t request = read(clientfd, buffer, buffer_size);
	printf("(ssize_t request: %zd)\n", request);

	if (request <= 0) {
		printf("(Request contains no data or read error)\n");
		return 1;
	}
	printf("%.*s\n", (int)request, buffer);

	FILE *fptr;
	fptr = fopen("/tmp/request09842089303", "w");
	if (!fptr) {
		printf("(fopen error)\n");
		return 1;
	}
	fwrite(buffer, sizeof(char), request, fptr);
	fclose(fptr);

	struct HTTP_REQUEST r;
	r = get_method(buffer);

	char *response_message =
		"HTTP/1.1 200 OK\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html>\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html\">\n<body>\n<h1>My First Heading</h1>\n<p>My first paragraph.</p>\n</body>\n<head>\n</html>";

	ssize_t response;

	if (strcmp(r.method, "GET") == 0) {
		response = write(clientfd, response_message, strlen(response_message));
		if (response < 0) {
			printf("(Data wasn't written to target)\n");
			return 1;
		}
		printf("(Data sent to target)\n");
	} else {
		printf("(method did not match GET)\n");
		printf("(method: %.*s)\n", (int)strlen(r.method), r.method);
		return 1;
	}

	printf("(target: %.*s)\n", (int)strlen(r.target), r.target);

	close(clientfd);
	return 0;
}
