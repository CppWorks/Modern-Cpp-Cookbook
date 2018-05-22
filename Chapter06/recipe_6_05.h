#pragma once

// Sometimes, it is useful to be able to store either a value or a null if a value is not available.

#include <map>
#include <optional>
#include <string>
#include <vector>
#include <iostream>

namespace recipe_6_05 {
  using namespace std::string_literals;

  struct foo {
    int a;
    double b;
  };

  struct bar {
    bar()
    {
      std::cout << "default ctor" << std::endl;
    }
    ~bar()
    {
      std::cout << "dtor" << std::endl;
    }
    bar(bar const& b)
    {
      std::cout << "copy ctor" << std::endl;
    }
    bar(bar&& b)
    {
      std::cout << "move ctor" << std::endl;
    }
  };

  // Use std::optional to return values from functions that may fail to produce a value:
  template <typename K, typename V>
  std::optional<V> find(int const key, std::map<K, V> const& m)
  {
    auto pos = m.find(key);
    if (pos != m.end())
      return pos->second;

    return {};
  }

  // Use std::optional for class data members that are optional:
  struct book {
    std::string title;
    std::optional<std::string> subtitle;
    std::vector<std::string> authors;
    std::string publisher;
    std::string isbn;
    std::optional<int> pages;
    std::optional<int> year;
  };

  // Use std::optional for parameters to functions that are optional:
  std::string extract(std::string const& text, std::optional<int> start,
                      std::optional<int> end)
  {
    auto s = start.value_or(0);
    auto e = end.value_or(text.length());
    return text.substr(s, e - s);
  }

  void process(std::optional<bar> const& arg)
  { /* do something with arg */
  }

  void execute()
  {
    std::cout << "\nRecipe 6.05: Using std::optional to store optional values."
              << "\n----------------------------------------------------------\n";

    auto lprint = [](auto const& o) {
      if (o)
        std::cout << *o << std::endl;
      else
        std::cout << "(empty)" << std::endl;
    };

    {
      std::cout << "\nTo store a value, use the constructor or assign the value directly "
                   "to an std::optional object:\n";
      std::optional<int> v1;
      lprint(v1); // (empty)
      std::optional<int> v2(42);
      lprint(v2); // 42
      v1 = 42;
      lprint(v1); // 42
      std::optional<int> v3 = v2;
      lprint(v3); // 42
    }

    {
      std::cout << "\nTo read the stored value, use operator* for simple types and "
                   "operator-> for complex types:\n";
      std::optional<int> v1{ 42 };
      std::cout << *v1 << std::endl; // 42

      std::optional<foo> v2{ foo{ 42, 10.5 } };
      std::cout << v2->a << ", " << v2->b << std::endl; // 42, 10.5
    }

    {
      std::cout << "\nAlternatively, use member functions value() and value_or() to read the stored value:\n";
      std::optional<std::string> v1{ "text"s };
      std::cout << v1.value() << std::endl; // text

      std::optional<std::string> v2;
      std::cout << v2.value_or("default"s) << std::endl; // default
    }

    {
      std::cout << "\nTo check whether the container stores a value, use a conversion operator to bool or the member function has_value():\n";

      std::optional<int> v1{ 42 };
      if (v1)
        std::cout << *v1 << std::endl;

      std::optional<foo> v2{ foo{ 42, 10.5 } };
      if (v2.has_value())
        std::cout << v2->a << ", " << v2->b << std::endl;
    }

    {
      std::cout << "\nTo modify the stored value, use member functions emplace() , reset(), or swap():\n";

      std::optional<int> v{ 42 };
      lprint(v); // 42
      v.reset();
      lprint(v); // (empty)
    }

    {
      std::cout << "\nfind(value, map) uses std::optional as return value:\n";

      std::map<int, std::string> m{ { 1, "one"s }, { 2, "two"s }, { 3, "three"s } };
      auto value = find(2, m);
      if (value)
        std::cout << *value << std::endl; // two

      value = find(4, m);
      if (value)
        std::cout << *value << std::endl;
    }

    {
      std::cout << "\nUse std::optional for function arguments:\n";

      auto v1 = extract("sample"s, {}, {});
      std::cout << v1 << std::endl; // sample

      auto v2 = extract("sample"s, 1, {});
      std::cout << v2 << std::endl; // ample

      auto v3 = extract("sample"s, 1, 4);
      std::cout << v3 << std::endl; // amp
    }

    {
      std::cout << "\nstd::optional can be copy constructed in e.g. in function argument:\n";

      // The first call to process() does not involve any additional object construction
      // because we pass an std::optional<bar> object. The second call, however, will
      // involve the copy construction of a bar object, because b2 is a bar and needs to
      // be copied to an std::optional<bar>; a copy is made even if bar has move semantics
      // implemented.

      std::optional<bar> b1{ bar{} };
      std::cout << "------------\n";
      bar b2{};
      std::cout << "------------\n";

      process(b1); // no copy
      std::cout << "------------\n";
      process(b2); // copy construction
      std::cout << "------------\n";
    }
  }
}
