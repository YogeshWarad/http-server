#include "server.hpp"
#include <iostream>

// server.cpp
#include "server.hpp"
#include <iostream>
#include <cstring>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")


Server::Server(int port) : port_(port), server_fd_(-1) {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(EXIT_FAILURE);
    }

}

void Server::setupSocket() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_);

    int opt = 1;
    setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    if (bind(server_fd_, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd_, 5) < 0) {
        std::cerr << "Listen failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port_ << std::endl;
}

void Server::acceptConnections() {
    sockaddr_in client_addr;

    int client_len = sizeof(client_addr);


    while (true) {
        int client_fd = accept(server_fd_, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            std::cerr << "Failed to accept connection." << std::endl;
            continue;
        }
        std::cout << "Accepted new connection." << std::endl;

        closesocket(client_fd);

    }
}

void Server::run() {
    setupSocket();
    acceptConnections();

    WSACleanup();

}
