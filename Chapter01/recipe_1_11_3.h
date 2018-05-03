// Template arguments cannot be names with internal linkage, so using static variables is
// not possible. On the other hand, symbols in an unnamed namespace have external linkage
// and can be used as template arguments.

#include <iostream>

template <int const& Size>
class test {
};

static int Size1 = 10;

// unnamed namespace solves the problem
namespace {
  int Size2 = 10;
}

namespace recipe_1_11_3 {
  void execute()
  {
    std::cout << "\nRecipe 1.11: Using unnamed namespaces instead of static globals."
              << "\n------------------------------------------------------------------\n";

    // Error, Size1 has internal linkage
    // => Should be an error but isn't. At least not in C++17.
    test<Size1> t1;
    test<Size2> t2;
  }
}
