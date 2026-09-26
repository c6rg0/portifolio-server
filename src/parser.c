#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HTTP_REQUEST get_method(char *buffer)
{
	struct HTTP_REQUEST r;

	r.method = strtok_r(buffer, " ", &buffer);
	r.target = strtok_r(buffer, " H", &buffer);
	r.protocol = strtok_r(buffer, " \n", &buffer);

	if (r.method == NULL || r.protocol == NULL || r.target == NULL) {
		printf("Header is broken");
		exit(1);
	}

	return r;
}
