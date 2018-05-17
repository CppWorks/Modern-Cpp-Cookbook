#pragma once

#include <functional>
#include <iostream>
#include <tuple>

namespace recipe_3_09 {
  int add(int const a, int const b)
  {
    return a + b;
  }

  struct foo {
    int x = 0;

    void increment_by(int const n)
    {
      x += n;
    }
  };

  namespace details {
    template <class F, class T, std::size_t... I>
    auto apply(F&& f, T&& t, std::index_sequence<I...>)
    {
      return std::__invoke(std::forward<F>(f), std::get<I>(std::forward<T>(t))...);
    }
  }

  template <class F, class T>
  auto apply(F&& f, T&& t)
  {
    return details::apply(
      std::forward<F>(f), std::forward<T>(t),
      std::make_index_sequence<std::tuple_size<std::decay_t<T>>::value>{});
  }

  void execute()
  {
    std::cout << "\nRecipe 3.09: Uniformly invoking anything callable."
              << "\n--------------------------------------------------\n";

    {
      auto a1 = add(1, 2); // a1 = 3

      int (*fadd)(int const, int const) = &add;
      auto a2 = fadd(1, 2); // a2 = 3

      auto fadd2 = &add;
      auto a3 = fadd2(1, 2); // a3 = 3
    }

    {
      foo f;
      f.increment_by(3);
      auto x1 = f.x; // x1 = 3

      void (foo::*finc)(int const) = &foo::increment_by;
      (f.*finc)(3);
      auto x2 = f.x; // x2 = 6

      auto finc2 = &foo::increment_by;
      (f.*finc2)(3);
      auto x3 = f.x; // x3 = 9
    }

    {
      auto a1 = std::__invoke(add, 1, 2); // a1 = 3

      auto a2 = std::__invoke(&add, 1, 2); // a2 = 3

      int (*fadd)(int const, int const) = &add;

      auto a3 = std::__invoke(fadd, 1, 2); // a3 = 3
    }

    {
      foo f;
      auto x1 = std::__invoke(&foo::x, f); // x1 = 0

      std::__invoke(&foo::increment_by, f, 10);
      auto x2 = std::__invoke(&foo::x, f); // x2 = 10

      auto x3 = std::__invoke(std::plus<>(), std::__invoke(&foo::x, f), 3); // x3 = 13

      auto x4 = std::__invoke(&foo::x, f); // x4 = 10
    }

    {
      auto l = [](auto a, auto b) { return a + b; };

      auto a = std::__invoke(l, 1, 2); // a = 3
    }

    {
      auto a = apply(add, std::make_tuple(1, 2));
    }
  }
}
