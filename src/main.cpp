#include "CLI/CLI.hpp"

using CLI::App;

int main(int argc, char **argv) {
  App app{"HTTP"};

  CLI11_PARSE(app, argc, argv);
  return 0;
}
