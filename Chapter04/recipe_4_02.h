#pragma once

#include <iostream>
#include <string>

// The operator # is called the stringizing operator

// The operator ## is called the token-pasting, merging, or concatenating operator.

// Through the indirection pattern the argument x will be expanded.

namespace recipe_4_02 {

#define MAKE_STR2(x) #x
// Helper macro doesn't have # or ## in it. So the argument will be expanded.
#define MAKE_STR(x) MAKE_STR2(x)

#define MERGE2(x, y) x##y
#define MERGE(x, y) MERGE2(x, y)

#define DECL_MAKE(x) DECL_MAKE2(x)
#define DECL_MAKE2(x)                                                                    \
  x* make_##x()                                                                        \
  {                                                                                      \
    return new x();                                                                      \
  }

#define NUMBER 42

  struct bar {
  };
  struct foo {
  };

  DECL_MAKE(foo)
  DECL_MAKE(bar)

  void execute()
  {
    std::cout << "\nRecipe 4.02: Using the indirection pattern for preprocessor "
                 "stringification and concatenation."
              << "\n---------------------------------------------------------------------"
                 "-------------------------\n";

    std::string s1{ MAKE_STR(sample) };  // s1 = "sample"
    std::string s2{ MAKE_STR2(sample) }; // s2 = "sample"

    std::string s3{ MAKE_STR(NUMBER) };  // s3 = "42"
    std::string s4{ MAKE_STR2(NUMBER) }; // s4 = "NUMBER"

    auto f = make_foo(); // f is a foo*
    auto b = make_bar(); // b is a bar*
  }
}
