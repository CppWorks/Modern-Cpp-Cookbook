#pragma once

// constexpr functions and objects can replace macros and hardcoded literals without any
// performance penalty.

#include <iostream>

namespace recipe_9_04 {
  // Define non-member functions that can be evaluated at compile time:
  constexpr unsigned int factorial(unsigned int const n)
  {
    return n > 1 ? n * factorial(n - 1) : 1;
  }

  class point3d {
    double x_;
    double y_;
    double z_;

  public:
    // Define constructors that can be executed at compile time to initialize constexpr
    // objects and member functions to be invoked during this period:
    constexpr point3d(double const x = 0, double const y = 0, double const z = 0)
      : x_{ x }
      , y_{ y }
      , z_{ z }
    {
    }

    constexpr double get_x() const
    {
      return x_;
    }
    constexpr double get_y() const
    {
      return y_;
    }
    constexpr double get_z() const
    {
      return z_;
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 9.04: Creating compile-time constant expressions."
              << "\n--------------------------------------------------------\n";

    {
      // Define variables that can have their values evaluated at compile time: (compile
      // time evaluation)
      constexpr unsigned int size = factorial(6);
      char buffer[size]{ 0 };

      int n;
      std::cout << "Enter factorial value: ";
      std::cin >> n;
      // runtime evaluation
      auto result = factorial(n);
      std::cout << result << std::endl;
    }

    {
      // Define variables that can have their values evaluated at compile time:
      constexpr point3d p{ 0, 1, 2 };
      constexpr auto x = p.get_x();
    }

    {
      static constexpr int c = 42;
      constexpr int const* p = &c;

      static constexpr int const& r = c;
    }
  }
}
