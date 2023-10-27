#include "tcpserver.hpp"
#include <iostream>
#include <netinet/in.h>
#include <ostream>

int main(int argc, const char **argv) {
  if (argc < 2) {
    std::cerr << "Few arguments than expected" << std::endl;
    std::cout << "Specify port number" << std::endl;
    return 0;
  }

  sockaddr_in socket;
  socket.sin_family = AF_INET;
  socket.sin_port = htons(atoi(argv[1]));
  socket.sin_addr.s_addr = INADDR_ANY;

  TcpServer new_server(socket, 5);
  return 0;
}