#pragma once

// Unlike regular classes, unions cannot have base classes nor can they be derived, and
// they cannot contain virtual functions (that would not make sense anyway). Unions are
// mostly used to define different representations of the same data. However, unions only
// work for types that are POD. If a union contains values of non-POD types, then these
// members require explicit construction with a placement new and explicit destruction,
// which is cumbersome and error-prone. In C++17, a type-safe union is available in the
// form of a standard library class template called std::variant.

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace recipe_6_06 {
  using namespace std::string_literals;

  struct foo {
    int value;

    explicit foo(int const i)
      : value(i)
    {
    }
  };

  void execute()
  {
    std::cout << "Recipe 6.06: Using std::variant as a type-safe union.\n"
              << "-----------------------------------------------------\n";

    {
      std::cout << "\nTo store a value, use the constructor or assign a value directly to a variant object:\n";

      std::variant<int, double, std::string> v;
      v = 42;   // v contains int 42
      v = 42.0; // v contains double 42.0
      v = "42"; // v contains string "42"
    }

    {
      std::cout << "\nTo read the stored values, use non-member functions std::get or "
                   "std::get_if:\n";

      std::variant<int, double, std::string> v = 42;

      auto i1 = std::get<int>(v); // int = index
      auto i2 = std::get<0>(v); // 0 = index
      std::cout << i1 << " == " << i2 << std::endl;

      try {
        auto f = std::get<double>(v);
      } catch (std::bad_variant_access const& e) {
        std::cout << e.what() << std::endl; // Unexpected index
      }
    }

    {
      std::cout << "\nTo check what is the stored alternative, use member function index():\n";

      std::variant<int, double, std::string> v = 42;
      static_assert(std::variant_size_v<decltype(v)> == 3);
      std::cout << "index = " << v.index() << std::endl;
      v = 42.0;
      std::cout << "index = " << v.index() << std::endl;
      v = "42";
      std::cout << "index = " << v.index() << std::endl;
    }

    {
      std::cout << "\nTo check whether a variant holds an alternative, use the "
                   "non-member function std::holds_alternative():\n";

      std::variant<int, double, std::string> v = 42;
      std::cout << "int? " << std::boolalpha << std::holds_alternative<int>(v)
                << std::endl; // int? true

      v = "42";
      std::cout << "int? " << std::boolalpha << std::holds_alternative<int>(v)
                << std::endl; // int? false
    }

    {
      std::cout
        << "\nTo modify the stored value, use member functions emplace() or swap().\n";

      std::variant<int, std::string, foo> v = 42;
      v.emplace<foo>(42);
    }

    {
      std::cout << "\nTo define a variant whose first alternative is not default "
                   "constructible, use std::monostate as the first alternative:\n";

      // std::variant<foo, int> v; // error

      std::variant<std::monostate, foo, int> v;
      v = 42;                                   // v contains int 42
      std::cout << std::get<int>(v) << std::endl;
      v = foo{ 42 }; // v contains foo{42}
      std::cout << std::get<foo>(v).value << std::endl;
    }

    {
      std::cout << "\nTo process the stored value of a variant and do something "
                   "depending on the type of the alternative, use std::visit():\n";

      std::variant<int, double, std::string> v = 42;
      std::visit([](auto&& arg) { std::cout << arg << std::endl; }, v);
      v = 42.0;
      std::visit([](auto&& arg) { std::cout << arg << std::endl; }, v);


      // if constexpr -> compile time
      // index() -> runtime
      std::visit(
        [](auto&& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, int>)
            std::cout << "int " << arg << std::endl;
          else if constexpr (std::is_same_v<T, double>)
            std::cout << "double " << arg << std::endl;
          else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "std::string " << arg << std::endl;
        },
        v);
    }
  }
}
