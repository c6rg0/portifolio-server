#ifndef NET_H
#define NET_H

int net_init(void);
int net_listen(int sockfd);
int net_action(int clientfd, char* buffer, int buffer_size);

#endif
