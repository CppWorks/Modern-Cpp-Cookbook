#include "recipe_1_11_1.h"
#include <iostream>
#include <string>

using namespace std::string_literals;

namespace {
  void print(std::string message)
  {
    std::cout << "[file1] " << message << std::endl;
  }
} // namespace

namespace recipe_1_11 {
  void file1_run()
  {
    print("run"s);
  }
} // namespace recipe_1_11