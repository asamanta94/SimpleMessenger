#ifndef SERVER_H
#define SERVER_H

#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#define DEFAULT_PORT	1025
#define N_CONNECTION	2

using namespace std;

enum server_t
{
	SERVER_OK,
	SERVER_ERROR
};

struct client_info_t
{
	char * name;
	int sock;
};

class Server
{
public:

	Server();
	~Server();

	server_t create();
	server_t listen_connections();
	server_t communicate();

	static void * client_communicator(void * client_fd);

private:

	int sock_fd;
	int client_fd;
	int server_addr_len;
	struct sockaddr_in server_addr;
};

#endif
