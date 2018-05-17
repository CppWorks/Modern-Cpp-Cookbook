#pragma once

#include <iostream>
#include <string>
#include <tuple>

// The examples in this recipe are based on the variadic function template add() that we
// wrote in the previous recipe, Writing a function template with a variable number of
// arguments.

/*
  clang-format off

Expression             Expansion
(... op pack)          ((pack$1 op pack$2) op ...) op pack$n
(init op ... op pack)  (((init op pack$1) op pack$2) op ...) op pack$n
(pack op ...)          pack$1 op (... op (pack$n-1 op pack$n))
(pack op ... op init)  pack$1 op (... op (pack$n-1 op (pack$n op init)))

clang-format on
*/

namespace recipe_3_06 {

  // To fold a parameter pack over a binary operator, use one of the following forms:

  // 1. Left folding with a unary form (... op pack)

  template <typename... Ts>
  auto add_Left(Ts... args)
  {
    return (... + args);
  }

  // 2. Left folding with a binary form (init op ... op pack)

  template <typename... Ts>
  auto add_to_one_Left(Ts... args)
  {
    return (1 + ... + args);
  }

  // 3. Right folding with a unary form (pack op ...)

  template <typename... Ts>
  auto add_Right(Ts... args)
  {
    return (args + ...);
  }

  // 4. Right folding with a binary form (pack op ... op init)

  template <typename... Ts>
  auto add_to_one_Right(Ts... args)
  {
    return (args + ... + 1);
  }

  // Fold expressions work with all overloads for the supported binary operators, but do
  // not work with arbitrary binary functions. It is possible to implement a workaround for
  // that by providing a wrapper type to hold a value and an overloaded operator for
  // that wrapper type.


  template <typename T>
  struct wrapper
  {
    T const & value;
  };
  template <typename T>
  constexpr auto operator<(wrapper<T> const & lhs,
                           wrapper<T> const & rhs)
  {
    return wrapper<T> {
      lhs.value < rhs.value ? lhs.value : rhs.value};
  }
  template <typename... Ts>
  constexpr auto min(Ts&&... args)
  {
    return (wrapper<Ts>{args} < ...).value;
  }


  void execute()
  {
    std::cout
      << "\nRecipe 3.06: Using fold expressions to simplify variadic function templates."
      << "\n----------------------------------------------------------------------------"
         "\n";

    using namespace std::literals;

    {
      auto s1 = add_Left(1, 2, 3, 4, 5);
      // s1 = 15
      std::cout << s1 << std::endl;

      auto s2 = add_Right("hello"s, " "s, "world"s, "!"s);
      // s2 = "hello world!"
      std::cout << s2 << std::endl;

      auto s3 = add_to_one_Left(1, 2, 3, 4, 5);
      // s3 = 16
      std::cout << s3 << std::endl;
    }

    {
      // The wrapper above is a simple class template that holds a constant reference to a
      // value of type T. An overloaded operator< is provided for this class
      // template; this overload does not return a Boolean to indicate that the first
      // argument is less than the second, but actually an instance of the wrapper class
      // type to hold the minimum value of the two arguments. The variadic function
      // template min() uses this overloaded operator< to fold the pack of arguments
      // expanded to instances of the wrapper class template.

      auto m = min(1, 2, 3, 4, 5); // m = 1
      std::cout << m << std::endl;
    }
  }
}
