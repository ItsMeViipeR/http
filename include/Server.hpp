#pragma once

#include <string>

class Server {
public:
  Server();
  ~Server();
  void run();
  std::string constructResponse(int code, std::string response);

private:
  std::string m_host = "localhost";
  int m_port = 8888;
};
