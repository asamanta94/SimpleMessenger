#include "client.h"

Client::Client()
{
    sock_fd = -1;
}

Client::~Client()
{

}

client_t Client::create()
{
    int ret = -1;

	ret = socket(AF_INET, SOCK_STREAM, 0);

	if(ret < 0)
	{
		cout << strerror(errno) << endl;
		return CLIENT_ERROR;
	}

	sock_fd = ret;

	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1055);

    return CLIENT_OK;
}

client_t Client::connect_server()
{
    int ret = connect(sock_fd, (const struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if(ret < 0)
    {
        cout << strerror(errno) << endl;
        return CLIENT_ERROR;
    }

    cout << "CONNECTED TO SERVER" << endl;

    return CLIENT_OK;
}

client_t Client::communicate()
{
    char buf[256];

    while(true)
    {
        cout << "CLIENT: ";
        cin >> buf;

        write(sock_fd, buf, 256);

        if( !strcmp(buf, "exit") )
        {
            cout << "CLIENT EXITING" << endl;
            return CLIENT_OK;
        }

        usleep(10000);

        memset(buf, '\0', sizeof(char) * 256);
    }

    return CLIENT_ERROR;
}

int main(int argc, char * argv[])
{
    Client * client = new Client();

    if( client->create() == CLIENT_ERROR )
        exit(EXIT_FAILURE);

    client->connect_server();

    usleep(10000);

    cout << "CLIENT STARTED" << endl;

    client->communicate();

    return 0;
}
