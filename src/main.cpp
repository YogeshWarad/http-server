#include "server.hpp"

int main() {
    Server server(8080);  // Listen on port 8080
    server.run();
    return 0;
}
