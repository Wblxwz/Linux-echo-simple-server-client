#include "client.h"

int main(int argc, char* argv[])
{
	int client_fd, ret;
	char s[max_buffer];
	sockaddr_in serveraddr;
	client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd < 0)
	{
		std::cerr << "Error!(client)" << std::endl;
		exit(1);
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(server_port);
	serveraddr.sin_addr.s_addr = inet_addr(server_ip);
	ret = connect(client_fd, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (ret != 0)
	{
		close(client_fd);
		std::cerr << "connect Error!(client)" << std::endl;
		exit(2);
	}
	while (true)
	{
		std::cin >> s;
		write(client_fd, s, sizeof(s));
		read(client_fd, s, sizeof(s));
		std::cout << "echo:" << s << std::endl;
	}
	close(client_fd);
	return 0;
}
