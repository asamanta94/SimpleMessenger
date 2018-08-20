#include "server.h"

Server::Server()
{
	sock_fd = -1;
	client_fd = -1;
}

Server::~Server()
{

}

server_t Server::create()
{
	int ret = -1;

	ret = socket(AF_INET, SOCK_STREAM, 0);

	if(ret < 0)
	{
		cout << strerror(errno) << endl;
		return SERVER_ERROR;
	}

	sock_fd = ret;

	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1055);

	server_addr_len = sizeof(struct sockaddr);
	ret = bind(sock_fd, (const struct sockaddr *)&server_addr, server_addr_len);

	if(ret < 0)
	{
		cout << strerror(errno) << endl;
		return SERVER_ERROR;
	}

	return SERVER_OK;
}

server_t Server::listen_connections()
{
	int ret = listen(sock_fd, N_CONNECTION);

	if(ret < 0)
	{
		cout << strerror(errno) << endl;
		return SERVER_ERROR;
	}

	while((ret = accept(sock_fd, (struct sockaddr *)&server_addr, (socklen_t *)&server_addr_len)) > 0)
	{
		int new_client_fd = ret;
		pthread_t new_client_thread;

		pthread_create(&new_client_thread, nullptr, &Server::client_communicator, &new_client_fd);
	};

	return SERVER_OK;
}

server_t Server::communicate()
{
	char buf[256];

	while(true)
	{
		while(read(client_fd, buf, 256) == -1) cout << strerror(errno) << endl;

		if( !strcmp(buf, "exit") )
		{
			cout << "SERVER EXITING" << endl;
			return SERVER_OK;
		}

		cout << "SERVER: " << buf << endl;
		memset(buf, '\0', sizeof(char) * 256);
	}

	return SERVER_ERROR;
}

void * Server::client_communicator(void * data)
{
	int * client_fd = reinterpret_cast<int *>(data);

	char buf[256];

	while(true)
	{
		while(read(*client_fd, buf, 256) == -1) cout << strerror(errno) << endl;

		if( !strcmp(buf, "exit") )
		{
			cout << "SERVER EXITING" << endl;
			break;
		}

		cout << "SERVER: " << buf << endl;
		memset(buf, '\0', sizeof(char) * 256);
	}

	pthread_exit(nullptr);
}

int main(int argc, char * argv[])
{
	Server * server = nullptr;
	server = new Server();

	if( server->create() == SERVER_ERROR )
		exit(EXIT_FAILURE);

	server->listen_connections();

	return 0;
}
