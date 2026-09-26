#ifndef PARSER_H
#define PARSER_H

struct HTTP_REQUEST {
	char *method;
	char *target;
	char *protocol;
	char *host;
	char *user_agent;
	char *accept;
	char *accept_lang;
	char *accept_encoding;
	char *connection;
	char *referer;
	char *sec_fetch_dest;
};

struct HTTP_REQUEST get_method(char *buffer);

#endif
