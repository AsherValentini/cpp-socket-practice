#pragma once

#include <string>
#include <unistd.h>
#include <arpa/inet.h>

class TcpClient {
public:
	TcpClient(const std::string& server_ip, int server_port)
		: m_server_ip(server_ip), m_server_port(server_port), m_socket_fd(-1)
	{
		// 1. create the socket
		m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(m_sock_fd <0) {
			perror("socket creation failed");
			return;
		}

		// 2. Setup the server address in sockaddr_in
		sockaddr_in server_addr{};
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(m_server_port);

		// 3. Convert IP string to binary
		if (inet_pton(AF_INET, m_server_ip.c_str(), &server_addr.sin_addr) <= 0) {
			perror("invalid address / address not supported");
			close(m_sock_fd);
			m_sock_fd = -1;
			return;
		}

		// 4. Connect
		if(connect(m_sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
			perror("connection failed");
			close(m_sock_fd);
			m_sock_fd =  -1;
			return;
		}

		std::cout << "[TcpClient] created" << std::endl;

	}
	~TcpClient();

	void sendMessage(const std::string& message);

private:
	std::string m_server_ip;
	int m_server_port;
	int m_sock_fd;


};