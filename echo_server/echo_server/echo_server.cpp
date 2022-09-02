#include "echo_server.h"

//To Do:getaddrinfo
int main(int argc, char* argv[])
{
	int server_fd, connfd, ret;
	socklen_t len;
	sockaddr_in serveraddr, clientaddr;
	char readbuf[max_buffer] = { 0 };
	char ip[40] = { 0 };
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		std::cerr << "Error!(server)" << std::endl;
		exit(1);
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(server_port);
	serveraddr.sin_addr.s_addr = inet_addr(server_ip);
	ret = bind(server_fd, (sockaddr*)&serveraddr, sizeof(serveraddr));
	if (ret != 0)
	{
		close(server_fd);
		std::cerr << "bind Error!(server)" << std::endl;
		exit(2);
	}
	ret = listen(server_fd, 1024);
	if (ret != 0)
	{
		close(server_fd);
		std::cerr << "listen Error!(server)" << std::endl;
		exit(3);
	}
	len = sizeof(clientaddr);
	while (true)
	{
		connfd = accept(server_fd, (sockaddr*)&clientaddr, &len);
		std::cout << "connect successful!" << std::endl;
		if (server_fd < 0)
		{
			std::cerr << "accept Error!(server)" << std::endl;
			//跳过当前循环，尝试下次连接
			continue;
		}
		while ((ret = read(connfd, readbuf, max_buffer)))
		{
			std::cout << inet_ntoa(clientaddr.sin_addr) << ":" << readbuf << std::endl;
			write(connfd, readbuf, max_buffer);
		}
		if (ret == 0)
		{
			std::cerr << "close!(client)" << std::endl;
		}
		else
		{
			std::cerr << "read Error!(server)" << std::endl;
		}
		close(connfd);
	}
	close(server_fd);
	return 0;
}