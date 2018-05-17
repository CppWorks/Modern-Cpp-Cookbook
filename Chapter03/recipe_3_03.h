#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// In C++, lambdas are basically syntactic sugar for unnamed function objects, which are
// classes that implement the call operator. However, just like any other function, this
// can be implemented generically with templates. C++14 takes advantage of this and
// introduces generic lambdas that do not need to specify actual types for their
// parameters and use the auto specifier instead. Though not referred with this name,
// generic lambdas are basically LAMBDA TEMPLATES. They are useful in cases where we want
// to use the same lambda but with different types of parameter.

// Write generic lambdas:

// 1. By using the auto specifier instead of actual types for lambda expression
// parameters.

// 2. When you need to use multiple lambdas that only differ by their parameter types.

namespace recipe_3_03 {
  using namespace std::string_literals;

  // This is what the compiler generates internally.
  struct __lambda_name__ {
    template <typename T1, typename T2>
    auto operator()(T1 const s, T2 const n) const
    {
      return s + n;
    }

    __lambda_name__(const __lambda_name__&) = default;
    __lambda_name__(__lambda_name__&&) = default;
    __lambda_name__& operator=(const __lambda_name__&) = delete;
    ~__lambda_name__() = default;
  };

  void execute()
  {
    std::cout << "\nRecipe 3.03: Using generic lambdas."
              << "\n-----------------------------------\n";

    auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
    auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };

    // with non-generic lambdas
    {
      auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
                                 [](int const s, int const n) { return s + n; });

      auto text
        = std::accumulate(std::begin(texts), std::end(texts), ""s,
                          [](std::string const s, std::string const n) { return s + n; });
    }

    // with generic lambdas
    {
      std::cout << "Both std::accumulates calculated with a generic lambda:\n";
      auto lsum = [](auto const s, auto const n) { return s + n; };

      auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0, lsum);

      auto text = std::accumulate(std::begin(texts), std::end(texts), ""s, lsum);

      std::cout << sum << "\n" << text << "\n\n";
    }
  }
}
