/*
 * HTTP server:
 * 1. Set up sockets and networking information,
 * 2. Listen to connections,
 * 3. Recieve a HTTP request,
 * 4. Parse the request,
 * 5. Respond,
 */

#include "net.h"
#include <string>

int main(void)
{
    Network net;

	// TODO: Add signal termination
	while (1) {
        net.Listen();
		net.Response();
	}

	return 0;
}
