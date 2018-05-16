#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// It must be well understood that the lambda expression is actually a class. In order to
// call it, the compiler needs to instantiate an object of the class. The object
// instantiated from a lambda expression is called a lambda closure.

// The lambda expression can capture variables by copy (or value) or by reference, and
// different combinations of the two are possible. However, it is not possible to capture
// a variable multiple times, and it is only possible to have & or = at the beginning of
// the capture list.

// A lambda can only capture variables from an enclosing function scope. It cannot capture
// variables with static storage duration (that is, variables declared in a namespace
// scope or with the static or external specifier).

/*
clang-format off
Lambda           Description
[](){}           Does not capture anything
[&](){}          Captures everything by reference
[=](){}          Captures everything by copy
[&x](){}         Capture only x by reference
[x](){}          Capture only x by copy
[&x...](){}      Capture pack extension x by reference
[x...](){}       Capture pack extension x by copy
[&, x](){}       Captures everything by reference except for x that is captured by copy
[=, &x](){}      Captures everything by copy except for x that is captured by reference
[&, this](){}    Captures everything by reference except for pointer this that is captured by copy (this is always captured by copy)
[x, x](){}       Error, x is captured twice
[&, &x](){}      Error, everything is captured by reference, cannot specify again to capture x by reference
[=, =x](){}      Error, everything is captured by copy, cannot specify again to capture x by copy
[&this](){}      Error, pointer this is always captured by copy
[&, =](){}       Error, cannot capture everything both by copy and by reference
clang-format on
*/

// The general form of a lambda expression, as of C++17, looks like this:

// [capture-list](params) mutable constexpr exception attr -> ret
// { body }

// All parts shown in this syntax are actually optional except for the capture list, that
// can, however, be empty, and the body, that can also be empty. The parameter list can
// actually be omitted if no parameters are needed. The return type does not need to be
// specified, as the compiler can infer it from the type of the returned expression. The
// mutable specifier (that tells the compiler the lambda can actually modify variables
// captured by copy), the constexpr specifier (that tells the compiler to generate a
// constexpr call operator), and the exception specifiers and attributes are all optional.

// The simplest possible lambda expression is []{}, though it is often written as [](){}.

namespace recipe_3_02 {
  using namespace std::string_literals;

  // These are the kind of functions the compiler generates internally for lambdas.
  inline bool is_positive(int const n)
  {
    return n > 0;
  }

  class range_selector {
    int start_;
    int end_;

  public:
    explicit range_selector(int const start, int const end)
      : start_(start)
      , end_(end)
    {
    }

    bool operator()(int const n)
    {
      return start_ <= n && n <= end_;
    }
  };

  struct __lambda_name__ {
    bool operator()(int const n) const
    {
      return n > 0;
    }
  };

  class __lambda_name_2__ {
    int start_;
    int end_;

  public:
    explicit __lambda_name_2__(int const start, int const end)
      : start_(start)
      , end_(end)
    {
    }

    __lambda_name_2__(const __lambda_name_2__&) = default;
    __lambda_name_2__(__lambda_name_2__&&) = default;
    __lambda_name_2__& operator=(const __lambda_name_2__&) = delete;
    ~__lambda_name_2__() = default;

    bool operator()(int const n) const
    {
      return start_ <= n && n <= end_;
    }
  };

  void execute()
  {
    std::cout << "Recipe 3.02: Using lambdas with standard algorithms.\n"
              << "----------------------------------------------------\n";

    auto numbers = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
    auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };

    {
      // Using full blown functions.
      auto positives = std::count_if(std::begin(numbers), std::end(numbers), is_positive);

      std::cout << "positives: " << positives << std::endl;

      auto start{ 5 }; // could be an input params
      auto end{ 10 };
      auto inrange = std::count_if(std::begin(numbers), std::end(numbers),
                                   range_selector(start, end));

      std::cout << "inrange(5, 10): " << inrange << std::endl;
    }

    {
      // Using anonymous lamdas with std::count_if.
      auto positives = std::count_if(std::begin(numbers), std::end(numbers),
                                     [](int const n) { return n > 0; });

      std::cout << "positives: " << positives << std::endl;

      auto start{ 5 };
      auto end{ 10 };
      auto inrange
        = std::count_if(std::begin(numbers), std::end(numbers),
                        [start, end](int const n) { return start <= n && n <= end; });

      std::cout << "inrange(5, 10): " << inrange << std::endl;
    }

    {
      // This time with std::accumulate.
      auto sum = std::accumulate(std::begin(numbers), std::end(numbers), 0,
                                 [](int const s, int const n) { return s + n; });

      std::cout << "sum: " << sum << std::endl;

      auto text
        = std::accumulate(std::begin(texts), std::end(texts), ""s,
                          [](std::string const s, std::string const n) { return s + n; });

      std::cout << "text: " << text << std::endl;
    }
  }
}
