#pragma once

#include <atomic>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// For checking types.
template <class T> class TD;

namespace recipe_1_01 {
  // For "..."s
  using namespace std::string_literals;

  class foo {
    int x;

  public:
    foo(int const x = 0)
      : x{ x }
    {
    }
    int& get()
    {
      return x;
    }
  };

  auto proxy_get(foo& f)
  {
    return f.get();
  }
  decltype(auto) proxy_get2(foo& f)
  {
    return f.get();
  }

  void execute()
  {
    std::cout << "Recipe 1.01: Using auto whenever possible.\n"
              << "------------------------------------------\n";
    {
      // Using auto ensures that you always use the correct type and that implicit
      // conversion will not occur.
      auto i = 42;                                      // int
      auto d = 42.5;                                    // double
      auto s = "text";                                  // const char*
      auto s1 = "text"s;                                // std::string
      auto b = new char[10]{ 0 };                       // char*
      auto p = std::make_shared<int>(42);               // std::shared_ptr<int>
      auto v = { 1, 2, 3 };                             // std::initializer_list<int>
      auto l = [](char const c) { return toupper(c); }; // int(char)
                                                        // TD<decltype(s)> sType;
                                                        // TD<decltype(s1)> s1Type;
    }

    {
      auto s = std::string{ "text" };       // std::string
      auto v = std::vector<int>{ 1, 2, 3 }; // std::vector<int>
                                            // TD<decltype(s)> sType;
    }

    {
      auto v = std::vector<int>{ 1, 2, 3 };
      // implicit conversion, possible loss of data
      int size1 = v.size();

      // Correct type.
      auto size2 = v.size();
      // size_t = unsigned long
      // TD<decltype(size2)> sType;

      // error, narrowing conversion
      // auto size3 = int{ v.size() };
    }

    {
      std::map<int, std::string> m;

      // When you want to iterate over a range, you don't care about the actual type of
      // the iterator.
      for (std::map<int, std::string>::const_iterator it = m.cbegin(); it != m.cend();
           ++it) {
      }

      // Looks simpler and saves you from typing and caring about actual types.
      for (auto it = m.cbegin(); it != m.cend(); ++it) {
      }
    }

    {
      // The auto specifier is only a placeholder for the type, not for the const/volatile
      // and references specifiers!
      foo f(42);
      auto x = f.get();
      x = 100;
      assert(f.get() == 42);
      std::cout << f.get() << std::endl; // prints 42
    }

    {
      foo f(42);
      //  If you need a const/volatile and/or reference type, then you need to specify
      //  them explicitly. If you need a const/volatile and/or reference type, then you
      //  need to specify them explicitly.
      auto& x = f.get();
      x = 100;
      assert(f.get() == 100);
      std::cout << f.get() << std::endl; // prints 100
    }

    {
      // It is not possible to use auto for types that are not moveable.
      // auto ai = std::atomic<int>(42);
    }

    {
      // It is not possible to use auto for multi-word types, such as long long, long
      // double.

      // error
      // auto l1 = long long{42};

      using llong = long long;
      auto l2 = llong{ 42 }; // OK
      auto l3 = 42LL;        // OK
    }

    {
      auto f = foo{ 42 };
      // The compiler will deduce the return type of proxy_get() as being int, not int&.
      // Trying to assign that value to an int& fails with an error cannot convert from
      // 'int' to 'int &'.
      // auto& x = proxy_get(f);
    }

    {
      // We need to actually return auto&. However, this is a problem with templates and
      // perfect forwarding the return type without knowing whether that is a value or a
      // reference. The solution to this problem in C++14 is decltype(auto) that will
      // correctly deduce the type
      auto f = foo{ 42 };
      decltype(auto) x = proxy_get(f);
      auto y = proxy_get2(f);
      // Only this keeps the reference -> z -> int &
      decltype(auto) z = proxy_get2(f);
      // TD<decltype(x)> xType;
      // TD<decltype(y)> yType;
      // TD<decltype(z)> zType;
    }

    {
      //  As of C++14, both lambda return type and lambda parameter types can be auto.
      //  Such a lambda is called a *generic lambda* because the closure type defined by
      //  the lambda has a templated call operator.
      auto ladd = [](auto const a, auto const b) { return a + b; };

      // This lambda can be used to add anything for which the operator+ is defined.
      auto i = ladd(40, 2);            // 42
      auto s = ladd("forty"s, "two"s); // "fortytwo"s
    }
  }

  // C++11 requires trailing return type.
  auto func1(int const i) -> int
  {
    return 2 * i;
  }

  // C++14  deduces the type of the return value.
  auto func2(int const i)
  {
    return 2 * i;
  }

} // namespace recipe_1_01
