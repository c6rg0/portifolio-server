#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HTTP_REQUEST get_method(char *buffer)
{
	struct HTTP_REQUEST r;

	r.method = strtok_r(buffer, " ", &buffer);
	if (r.method == NULL) {
		printf("Method is NULL");
		exit(1);
	}

	r.target = strtok_r(buffer, " H", &buffer);
	if (r.target == NULL) {
		printf("Target is NULL");
		exit(1);
	}

	return r;
}
