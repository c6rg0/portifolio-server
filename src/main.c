/*
 * HTTP server:
 * 1. Set up sockets and networking information,
 * 2. Listen to connections,
 * 3. Recieve a HTTP request,
 * 4. Parse the request,
 * 5. Respond,
 */

#include "net.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int sockfd = net_init();

	// TODO: Add support signal termination.
	while (1) {
		int clientfd = net_listen(sockfd);

		int buffer_size = sizeof(char) * 4096;
		char *buffer = malloc(buffer_size + 1);
		if (buffer == NULL) {
			printf("(Malloc error)");
			return 1;
		}

		int return_num = net_action(clientfd, buffer, buffer_size);
		free(buffer);

		if (return_num != 0)
			return 1;
	}

	return 0;
}
