#include "tcpserver.hpp"
#include "command.hpp"
#include "parser.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

TcpServer::TcpServer(sockaddr_in socket, int num_clients) {
  this->server_address = socket;

  if (!TcpServer::createSocket()) {
    exit(EXIT_FAILURE);
  }

  if (!TcpServer::bind_()) {
    exit(EXIT_FAILURE);
  }

  if (!TcpServer::listen_()) {
    exit(EXIT_FAILURE);
  }

  TcpServer::startCommunication();
}

bool TcpServer::createSocket() {
  bool retStatus = true;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (server_socket == -1) {
    std::cerr << "Failed to create socket" << std::endl;
    retStatus = false;
  } else {
    std::cout << "Server socket created" << std::endl;
  }
  return retStatus;
}

bool TcpServer::bind_() {
  bool retStatus = true;
  server_bind =
      bind(server_socket, (sockaddr *)&server_address, sizeof(server_address));

  if (server_bind != 0) {
    std::cerr << "Failed to bind" << std::endl;
    retStatus = false;
  } else {
    std::cout << "Server bind successful" << std::endl;
  }
  return retStatus;
}

bool TcpServer::listen_() {
  bool retStatus = true;
  server_listen = listen(server_socket, 5);

  if (server_listen == -1) {
    std::cout << "Server is not able to listen" << std::endl;
    retStatus = false;
  } else {
    std::cout << "Server is listening on port "
              << ntohs(server_address.sin_port) << std::endl;
  }
  return retStatus;
}

bool TcpServer::accept_() {
  bool retStatus = true;
  new_socket =
      accept(server_socket, (struct sockaddr *)&client_address, &client_length);

  if (new_socket == -1) {
    std::cerr << "Failed to accept client" << std::endl;
  } else {
    std::cout << "Accepted client connection" << std::endl;
  }
  return retStatus;
}

void TcpServer::clientHandling() {
  byte_count = send((new_socket), connection, strlen(connection), 0);

  if (byte_count > 0) {
    std::cout << "Communication started" << std::endl;
  } else {
    std::cout << "Communication failed" << std::endl;
  }

  while (1) {
    std::memset(buffer, 0, 200);

    byte_count = recv((new_socket), buffer, sizeof(buffer), 0);

    if (byte_count > 0) {
      std::cout << "Message Received: " << buffer << std::endl;

      Command_(static_cast<char *>(buffer));
    } else {
      break;
    }

    byte_count = send((new_socket), confirmation, strlen(confirmation), 0);

    if (byte_count > 0) {
      std::cout << "Confirmation Message Sent to the client | Byte Count: "
                << byte_count << std::endl;
    } else {
      break;
    }

    std::vector<int>::size_type closeCheck =
        Parser_::parse_(terminate, buffer).size();

    if (closeCheck == 1) {
      std::cout << "Terminate Communication" << std::endl;
      break;
    }
  }
}

void TcpServer::startCommunication() {
  for (;;) {
    if (!(TcpServer::accept_())) {
      continue;
    }

    if ((pid = fork()) == -1) {
      // Failed to fork
      close(new_socket);
      continue;
    } else if (pid > 0) {
      // Successful fork
      // parent process
      close(new_socket);
      std::cout << "New client socket created" << std::endl;
      continue;
    } else if (pid == 0) {
      // New child process for client handling
      TcpServer::clientHandling();
    }
  }
}

TcpServer::~TcpServer() {
  close(server_socket);
  }
