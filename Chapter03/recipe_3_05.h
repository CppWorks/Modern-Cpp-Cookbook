#pragma once

#include <iostream>
#include <string>
#include <tuple>

// Functions with a variable number of arguments are called VARIADIC FUNCTIONS. Function
// templates with a variable number of arguments are called VARIADIC FUNCTION TEMPLATES.

// In order to write variadic function templates, you must perform the following steps:

// 1. Define an overload with a fixed number of arguments to end compile-time recursion if
// the semantics of the variadic function template require it (refer to [1] in the
// following code).

// 2. Define a template parameter pack to introduce a template parameter that can hold any
// number of arguments, including zero; these arguments can be either types, non-types, or
// templates (refer to [2]).

// 3. Define a function parameter pack to hold any number of function arguments, including
// zero; the size of the template parameter pack and the corresponding function parameter
// pack is the same and can be determined with the sizeof... operator (refer to [3]).

// 4. Expand the parameter pack in order to replace it with the actual arguments being
// supplied (refer to [4]).

namespace recipe_3_05 {
  template <typename T> // [1] overload with fixed number of arguments
  T add(T value)
  {
    return value;
  }

  template <typename T, typename... Ts> // [2] typename... Ts
  T add(T head, Ts... rest)             // [3] Ts... rest
  {
    return head + add(rest...); // [4] rest...
  }

  // It should be further added that a parameter pack can appear in a brace-initialization
  // and its size can be determined using the sizeof... operator.
  template <typename... T>
  auto make_even_tuple(T... a)
  {
    // The sizeof... operator can be used with both template parameter packs and function
    // parameter packs. sizeof...(a) and sizeof...(T) would produce the same value.
    static_assert(sizeof...(a) % 2 == 0, "expected an even number of arguments");

    std::tuple<T...> t{ a... };
    return t;
  }

  void execute()
  {
    std::cout
      << "\nRecipe 3.05: Writing a function template with a variable number of arguments."
      << "\n-----------------------------------------------------------------------------"
         "\n";
    {
      using namespace std::literals;

      auto s1 = add(1, 2, 3, 4, 5);
      // s1 = 15
      std::cout << s1 << std::endl;

      auto s2 = add("hello"s, " "s, "world"s, "!"s);
      // s2 = "hello world!"
      std::cout << s2 << std::endl;
    }

    {
      auto t1 = make_even_tuple(1, 2, 3, 4); // OK

      // compile time error: expected an even number of arguments
      // auto t2 = make_even_tuple(1, 2, 3);
    }
  }
}
