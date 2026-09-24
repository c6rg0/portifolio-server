#ifndef PARSER_H
#define PARSER_H

struct HTTP_REQUEST {
	char *method;
	char *target;
	int protocol;
};

struct HTTP_REQUEST get_method(char *buffer);

#endif
