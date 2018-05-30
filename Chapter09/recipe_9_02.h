#pragma once

// The exception specification from C++03 which allowed you to indicate what types of
// exceptions a function could throw has been deprecated and replaced with the new C++11
// noexcept specification. This specification only allows you to indicate whether a
// function may throw or not.

// As of C++17, exception specification is part of the function type, but not part of the
// function signature; it may appear as part of any function declarator. Because exception
// specification is not part of the function signature, two function signatures cannot
// differ only in the exception specification. Prior to C++17, exception specification was
// not part of the function type and could only appear as part of lambda declarators or
// top-level function declarators; they could not appear even in typedef or type alias
// declarations.

// There are several ways in which the process of throwing an exception can be specified:

// 1. If no exception specification is present, then the function could potentially throw exceptions.

// 2. noexcept(false) is equivalent to no exception specification.

// 3.  noexcept(true) and noexcept indicate that a function does not throw any exception.

// 4. throw() is equivalent to noexcept(true) but deprecated.

// Using exception specifications must be done with care because, if an exception (either
// thrown directly or from another function that is called) leaves a function marked as
// non-throwing, the program is terminated immediately and abnormally with a call to
// std::terminate().

// Pointers to the functions that do not throw exceptions can be implicitly converted into
// pointers to functions that may throw exceptions, but not the opposite.

#include <iostream>

namespace recipe_9_02 {
  // Use nothrow in a function declaration to indicate that the function is not throwing
  // any exception:
  void func_no_throw() noexcept {}

  // Use nothrow(expr) in a function declaration, such as template metaprogramming, to
  // indicate that the function may or may not throw an exception based on a condition
  // that evaluates to bool:
  template <typename T>
  T generic_func_1() noexcept(std::is_nothrow_constructible<T>::value)
  {
    return T{};
  }

  // Use the noexcept operator at compile time to check whether an expression is declared
  // to not throw any exception:
  template <typename T>
  T generic_func_2() noexcept(noexcept(T{}))
  {
    return T{};
  }

  template <typename F, typename A>
  auto func(F&& f, A&& arg) noexcept
  {
    // Use the noexcept operator at compile time to check whether an expression is declared
    // to not throw any exception:
    static_assert(!noexcept(f(arg)), "F is throwing!");
    return f(arg);
  }

  int double_it(int const i) noexcept
  {
    return i + i;
  }

  int half_it(int const i)
  {
    throw std::runtime_error("not implemented!");
  }

  struct foo {
    foo() {}
  };

  void execute()
  {
    std::cout << "\nRecipe 9.02: Using noexcept for functions that do not throw."
              << "\n------------------------------------------------------------\n";

    std::cout << std::boolalpha << noexcept(func_no_throw()) << std::endl // true
              << noexcept(generic_func_1<int>()) << std::endl             // true
              << noexcept(generic_func_1<std::string>()) << std::endl     // true
              << noexcept(generic_func_2<int>()) << std::endl             // true
              << noexcept(generic_func_2<std::string>()) << std::endl     // true
              << noexcept(generic_func_2<foo>()) << std::endl             // false
              << noexcept(double_it(42)) << std::endl                     // true
              << noexcept(half_it(42)) << std::endl                       // false
              << noexcept(func(half_it, 42)) << std::endl;                // true
    // << noexcept(func(double_it, 42)) << std::endl;              // true
  }
}
