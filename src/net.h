#ifndef NET_H
#define NET_H

class Network {
public:
    Network (void);
    void Listen (void);
    void Response (void);
    ~Network ();
private:
    int sockfd;
    int clientfd;
};

#endif
