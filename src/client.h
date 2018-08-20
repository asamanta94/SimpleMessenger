#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

using namespace std;

enum client_t
{
    CLIENT_OK,
    CLIENT_EXIT,
    CLIENT_ERROR
};

class Client
{

public:

    Client();
    ~Client();

    client_t create();
    client_t connect_server();
    client_t communicate();

private:

    int sock_fd;
    struct sockaddr_in server_addr;
};

#endif
