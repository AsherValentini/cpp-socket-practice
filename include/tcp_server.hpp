#include <iostream>
#include <thread>
#include <atomic>
#include <cstdint>

#include <unistd.h>
#include <arpa/inet.h>

class TcpServer{

public:
	TcpServer(int port = 5000) : m_port(port) {}
	void start() {
		m_running = true;
		m_server_thread = std::thread(&ServerTCP::run, this);
	}
	void stop() {
		m_running = false;
		if(m_server_thread.joinable()) {
			m_server_thread.join();
		}
	}

private:
	void run() {
		// step 1: create the socket and FD
		int server_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET -> address family IPv4 socket. SOCK_STREAM->TCP

		if (server_fd == 0) {
			perror("socket failed"); // prints system error and my error message. e.g. "socket failed: too many open files"
			return;
		}

		// step 2: bind the socket to an IP address and port
		sockaddr_in address{};
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(m_port);

		if(bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
			perror("bind failed");
			close(server_fd);
			return;
		}

		if (listen(server_fd, 3) < 0 ) {
			perror("listen failed");
			close(server_fd);
		}

		std::cout << "[ServerTCP] Listening on port:  " << m_port << "\n";

		while (m_running) {
			// Gain Client
			sockaddr_in client_addr{};
			socklen_t addrlen = sizeof(client_addr);
			int client_socket = accept(server_fd, (struct sockaddr*) &client_addr, &addrlen);

			if (client_socket < 0) {
				if (m_running) perror("accept");
				break;
			}

			// Handle Client
			// read the payload prefix
			std::uint32_t size;
			if(recv(client_socket, &size, sizeof(size), 0) <= 0) {
				close(client_socket);
				continue;
			}
			// read the payload
			size = ntohl(size);  // network to host byte order (incase host machine is not the same endianess as the network

			std::string buffer(size, '\0');
			if (recv(client_socket, buffer.data(), size, 0) <= 0) {
				close(client_socket);
				continue;
			}
			close(client_socket);
		}
		close(server_fd);
		std::cout << "[ServerTCP] Shutdown. \n";
	}
	int m_port;
	std::thread m_server_thread;
	std::atomic<bool> m_running{false};
}; 