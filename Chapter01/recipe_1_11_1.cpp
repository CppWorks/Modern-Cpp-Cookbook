// All symbols that are not declared static have external linkage and their names must be
// unique throughout the program. The typical C solution for this problem is to declare
// those symbols static, changing their linkage from external to internal and therefore
// making them local to a translation unit. In this recipe, we will look at the C++
// solution for this problem -> unnamed namespaces.

// In other words: When a function is declared in a translation unit, it has external
// linkage. That means two functions with the same name from two different translation
// units would generate a linkage error because it is not possible to have two symbols
// with the same name.

// Solution:
// 1. Declare a namespace without a name in your source file.
// 2. Put the definition of the global function or variable in the unnamed namespace
//    without making them static.

#include "recipe_1_11_1.h"
#include <iostream>
#include <string>

using namespace std::string_literals;

// unnamed namespace
namespace {
  // function only available in this translation unit
  // there is another print function in recipe_1_11_2.cpp
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
