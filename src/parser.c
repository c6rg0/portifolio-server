#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HTTP_REQUEST get_req_type(char *buffer)
{
	struct HTTP_REQUEST r;
	char *saveptr = NULL;

	// Whitespace marks the end of the token
	char *token = strtok_r(buffer, " ", &saveptr);

	if (token == NULL) {
		printf("token is NULL");
		exit(1);
	}
	r.req_type = token;

	return r;
}
