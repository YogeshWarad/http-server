#include "server.hpp"
#include <iostream>

Server::Server(int port) : port_(port) {}

void Server::run() {
    std::cout << "Listening on port " << port_ << "...\n";
    // Accept connections here (Week 2)
}
