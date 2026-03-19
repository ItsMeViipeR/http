#include "../include/Server.hpp"
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

Server::Server() {}

Server::~Server() {}

std::string Server::constructResponse(int code, std::string response) {
  std::string httpResponse = "HTTP/1.1 " + std::to_string(code) + " OK\r\n";
  httpResponse += "Content-Type: text/plain\r\n";
  httpResponse +=
      "Content-Length: " + std::to_string(response.length()) + "\r\n";
  httpResponse += "\r\n";
  httpResponse += response;

  return httpResponse;
}

void Server::run() {
  std::cout << "Running on http://" << m_host << ":" << m_port << std::endl;

  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    perror("socket failed");
    return;
  }

  // Permet de redémarrer le serveur instantanément sur le même port
  int opt = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(m_port);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0) {
    perror("bind failed");
    close(serverSocket);
    return;
  }

  if (listen(serverSocket, 5) < 0) {
    perror("listen failed");
    close(serverSocket);
    return;
  }

  while (true) {
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
      perror("accept failed");
      continue;
    }

    char buffer[2048] = {0};
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead > 0) {
      std::cout << "Message from client: " << buffer << std::endl;
      std::string response = constructResponse(200, "Hello, World");
      send(clientSocket, response.c_str(), response.length(), 0);
    }

    // TRÈS IMPORTANT : Fermer le socket client après usage
    close(clientSocket);
  }

  close(serverSocket); // Note: Inatteignable ici à cause du while(true)
}