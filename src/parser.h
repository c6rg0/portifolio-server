#ifndef PARSER_H
#define PARSER_H

struct HTTP_REQUEST {
    char* req_type;
    int HTTP_version;
};

struct HTTP_REQUEST get_req_type (char *buffer);

#endif
