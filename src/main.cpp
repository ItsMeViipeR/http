#include "CLI/CLI.hpp"
#include "Server.hpp"

using CLI::App;

int main(int argc, char **argv) {
  App app{"HTTP"};
  auto run = app.add_subcommand("run", "Runs the server");
  auto stop = app.add_subcommand("stop", "Stops the server");

  CLI11_PARSE(app, argc, argv);

  if (*run) {
    Server s;

    s.run();
  }

  return 0;
}
