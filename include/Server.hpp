#pragma once

#include <string>

class Server {
public:
  Server();
  ~Server();
  void run();
  std::string constructResponse(int code, std::string response);
  void setHost(std::string host);
  void setPort(int port);

private:
  std::string m_host = "localhost";
  int m_port = 8888;
  int m_serverSocket;
};
