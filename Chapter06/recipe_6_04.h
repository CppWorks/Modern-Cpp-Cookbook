#pragma once

// C++ does not have a hierarchical type system like other languages therefore, it does
// not have a possibility to store multiple types of value in a single variable.
// Developers have long time used void* for that purpose, but this only helps store
// pointers to anything and is not type-safe. C++17 has introduced a standard type-safe
// container, called std::any, that can hold a single value of any type.

#include <any>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace recipe_6_04 {
  using namespace std::string_literals;

  void log(std::any const& value)
  {
    if (value.has_value()) {
      auto const& tv = value.type();
      if (tv == typeid(int)) {
        std::cout << std::any_cast<int>(value) << std::endl;
      } else if (tv == typeid(std::string)) {
        std::cout << std::any_cast<std::string>(value) << std::endl;
      } else if (tv == typeid(std::chrono::time_point<std::chrono::system_clock>)) {
        auto t = std::any_cast<std::chrono::time_point<std::chrono::system_clock>>(value);
        auto now = std::chrono::system_clock::to_time_t(t);
        std::cout << std::put_time(std::localtime(&now), "%F %T") << std::endl;
      } else {
        std::cout << "unexpected value type" << std::endl;
      }
    } else {
      std::cout << "(empty)" << std::endl;
    }
  }

  inline bool is_integer(std::any const& a)
  {
    return a.type() == typeid(int);
  }

  void execute()
  {
    std::cout << "\nRecipe 6.04: Using std::any to store any value."
              << "\n-----------------------------------------------\n";
    {
      std::cout << "\nTo store values, use the constructor or assign them directly to a "
                   "std::any variable:\n";
      std::cout << "See source code.\n";

      std::any value(42); // integer     12
      value = 42.0;       // double      12.0
      value = "42"s;      // std::string "12"
    }

    {
      std::cout << "\nTo check whether the container stores a value, use the has_value() member function:\n";
      auto ltest = [](std::any const& a) {
        if (a.has_value())
          std::cout << "has value" << std::endl;
        else
          std::cout << "no value" << std::endl;
      };

      std::any value;
      ltest(value); // no value
      value = 42;
      ltest(value); // has value
      // To modify the stored value, use member functions emplace() , reset(), or swap():
      value.reset();
      ltest(value); // no value
    }

    {
      std::cout << "\nTo read values, use the non-member function std::any_cast():\n";
      std::any value = 42.0;

      try {
        auto d = std::any_cast<double>(value);
        std::cout << d << std::endl;
      } catch (std::bad_any_cast const& e) {
        std::cout << e.what() << std::endl;
      }

      try {
        auto pd = std::any_cast<double>(&value);
        std::cout << *pd << std::endl;
      } catch (std::bad_any_cast const& e) {
        std::cout << e.what() << std::endl;
      }

      try {
        auto i = std::any_cast<int>(value);
        std::cout << i << std::endl;
      } catch (std::bad_any_cast const& e) {
        std::cout << e.what() << std::endl;
      }

      value = "sample"s;
      try {
        auto s = std::any_cast<std::string>(value);
        std::cout << s << std::endl;
      } catch (std::bad_any_cast const& e) {
        std::cout << e.what() << std::endl;
      }

      value = std::vector<int>{ 1, 1, 2, 3, 5, 8 };
      try {
        auto v = std::any_cast<std::vector<int>>(value);
        for (auto e : v)
          std::cout << e << std::endl;
      } catch (std::bad_any_cast const& e) {
        std::cout << e.what() << std::endl;
      }
    }

    {
      std::cout << "\nCheck whether the container has any value, check the type of the stored value, and read the value from the container.\n";
      log(std::any{});                       // (empty)
      log(12);                               // 12
      log("12"s);                            // 12
      log(12.0);                             // unexpected value type
      log(std::chrono::system_clock::now()); // 2016-10-30 22:42:57
    }

    {
      std::cout << "\nTo store multiple values of any type, use a standard container "
                   "such as std::vector to hold values of the type std::any:\n";
      std::vector<std::any> values;
      values.push_back(std::any{});
      values.push_back(12);
      values.push_back("12"s);
      values.push_back(12.0);
      values.push_back(std::chrono::system_clock::now());

      for (auto const v : values)
        log(v);
    }

    {
      // Trying to assign a custom type to std::any.
      struct foo {
        foo() = default;
        foo(foo const&) = delete;
      };

      foo f;
      // std::any value = f; // error
    }
  }
}
