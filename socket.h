#include "../config/monitor.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#include <chrono>
#include <thread>

using namespace Monarchy;

int server_fd, new_socket = 0, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[Monitor::MSG_SIZE] = {0};  // from config/monitor.h
const int PORT = Monitor::SOCKET_PORT; // from config/monitor.h

void setup_socket() {
    // create a TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "failed to create a TCP socket" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        std::cout << "failed to set socket options" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // accept connections from any address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address))<0) {
        std::cout << "failed to bind socket" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // listen for any incoming connections
    if (listen(server_fd, 1) < 0) {
        std::cout << "failed to listen for new connections" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // accept any incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t*)&addrlen))<0) {
        std::cout << "failed to accept an incoming connection" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
