#pragma once

#include <functional>
#include <iostream>

// Lambdas are basically unnamed function objects, which means that it should be possible
// to call them recursively. Indeed, they can be called recursively; however, the
// mechanism for doing it is not obvious, as it requires assigning the   lambda to a
// function wrapper and capturing the wrapper by reference. Though it can be argued that a
// recursive lambda does not really make sense and a function is probably a better design
// choice, in this recipe we will look at how to write a recursive lambda.

namespace recipe_3_04 {
  // The Fibonacci function is usually implemented recursively in C++ as follows:
  constexpr int fib(int const n)
  {
    return n <= 2 ? 1 : fib(n - 1) + fib(n - 2);
  }

  // In order to write a recursive lambda function, you must perform the following:

  // 1. Define the lambda in a function scope.

  // 2. Assign the lambda to an std::function wrapper.

  // 3. Capture the std::function object by reference in the lambda in order to call it
  // recursively.

  std::function<int(int const)> fib_create()
  {
    std::function<int(int const)> lfib
      = [&lfib](int const n) { return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2); };

    return lfib;
  }

  std::function<int(int const)> fib_create2()
  {
    std::function<int(int const)> f = [](int const n) {
      std::function<int(int const)> lfib
        = [&lfib](int n) { return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2); };
      return lfib(n);
    };

    return f;
  }

  void execute()
  {
    std::cout << "\nRecipe 3.04: Writing a recursive lambda."
              << "\n----------------------------------------\n";

    {
      std::cout << "Using a standard recursive funcion:\n";
      auto f10 = fib(10);

      std::cout << "fib(10): " << f10 << std::endl;
    }

    {
      std::cout << "\nUsing recursive lambdas:\n";
      std::function<int(int const)> fibonacci = [&fibonacci](int const n) {
        return n <= 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
      };

      auto f10 = fibonacci(10);

      std::cout << "fib(10): " << f10 << std::endl;
    }

    {
      // Actually better than fib_create2.
      auto lfib = fib_create();
      auto f10 = lfib(10); // is supposed to crash but doesn't
      std::cout << "fib(10): " << f10 << std::endl;
    }

    {
      // Now that fib_create works this is overly complicated.
      auto lfib = fib_create2();

      auto f10 = lfib(10);

      std::cout << "fib(10): " << f10 << std::endl;
    }
  }
}
