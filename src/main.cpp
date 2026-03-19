#include "CLI/CLI.hpp"
#include "Server.hpp"

using CLI::App;
using CLI::Option;

int main(int argc, char **argv) {
  App app{"HTTP"};
  auto run = app.add_subcommand("run", "Runs the server");
  auto stop = app.add_subcommand("stop", "Stops the server");

  std::string hostInput;
  int portInput;

  Option *host = run->add_option("--host", hostInput, "Server host address");
  Option *port = run->add_option("--port", portInput, "Server port");

  CLI11_PARSE(app, argc, argv);

  if (*run) {
    Server s;

    if (host->count() > 0) {
      s.setHost(hostInput);
    }

    if (port->count() > 0) {
      s.setPort(portInput);
    }

    s.run();
  }

  return 0;
}
