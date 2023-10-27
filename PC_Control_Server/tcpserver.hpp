#ifndef TCP_SERVER_
#define TCP_SERVER_

#include <iostream>
#include <netinet/in.h>
#include <csignal>
#include <sys/socket.h>
#include "command.hpp"
#include "parser.hpp"

#define DEFAULT_PORT 8080

class TcpServer {
private:
public:
  char buffer[200] = {0};
  char connection[40] = "Connected to client\n";
  char confirmation[40] = "Server Received Message\n";
  char terminate[6] = "close";
  int  server_socket = 0, new_socket = 0, server_bind = 0, server_listen = 0;
  int  byte_count = 0, num_clients = 0;
  pid_t pid = 1;
  sockaddr_in server_address, client_address;
  socklen_t client_length = sizeof(client_address);

  friend void interruptSignalCallback(int signum);

  TcpServer(sockaddr_in socket, int num_clients);
  bool createSocket();
  bool bind_();
  bool listen_();
  bool accept_();
  void clientHandling();
  void startCommunication();
  // void interruptCallback(int sigNum);
  // void handlingInterruptSignal();
  ~TcpServer();
};

#endif // TCP_SERVER_