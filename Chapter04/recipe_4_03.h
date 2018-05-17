#pragma once

#include <iostream>
#include <type_traits>

// Compile-time assertions are performed with "static_assert(condition, message)".
// As of C++17, the message is optional.

namespace recipe_4_03 {
  struct alignas(8) item {
    int id;
    bool active;
    double value;
  };

  template <typename T>
  class pod_wrapper {
    static_assert(std::is_pod<T>::value, "POD type expected!");

    T value;
  };

  struct point {
    int x;
    int y;
  };

  template <typename T>
  auto mul(T const a, T const b)
  {
    static_assert(std::is_integral<T>::value, "Integral type expected");

    return a * b;
  }

  void execute()
  {
    std::cout
      << "\nRecipe 4.03: Performing compile-time assertion checks with static_assert."
      << "\n-------------------------------------------------------------------------\n";

    pod_wrapper<int> w1;   // OK
    pod_wrapper<point> w2; // OK
    // pod_wrapper<std::string> w3; // Error: POD type expected

    auto v1 = mul(1, 2); // OK
    // auto v2 = mul(12.0, 42.5); // error: Integral type expected
  }
}
