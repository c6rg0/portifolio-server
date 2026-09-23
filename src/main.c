/*
 * HTTP server:
 * 1. Set up sockets and networking information,
 * 2. Listen to connections,
 * 3. Recieve a HTTP request,
 * 4. Parse the request,
 * 5. Respond,
 */

#include <errno.h>
#include <fcntl.h> // File control options
#include <linux/input.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h> // open(), write(), close()

int main(void)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket error\n");
		return 1;
	}

    struct sockaddr_in serv_addr;
    uint16_t port = 8080;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0){
        printf("Socket bind failed\n");
        return 1;
    }

    if (listen(sockfd, SOMAXCONN) != 0){
        printf("Couldn't listen\n");
        return 1;
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int clientfd;

    while (1){
        clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);

        if (clientfd < 0) {
            printf("Accept error\n");
            return 1;
        }
        printf("Accept success\n");
        break;
    }

	FILE *fptr;
	fptr = fopen("/tmp/request09842089303", "w");
    if (!fptr) {
        printf("fopen error\n");
        return 1;
    }

    char buffer[4096]; // 4096 has no meaning atp
    ssize_t request = read(clientfd, buffer, 4096);

    printf("request: %zd\n", request);
    if (request < 0){
        printf("Request contains no data?");
    }

    printf("buffer: %.*s\n", (int)request, buffer);
    fwrite(buffer, 1, request, fptr);

    fclose(fptr);
	close(sockfd);
	return 0;
}
