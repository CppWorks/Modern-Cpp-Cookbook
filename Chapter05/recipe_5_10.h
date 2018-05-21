#pragma once

// Apart from begin()/end(), containers provide cbegin()/cend() to return constant
// iterators, rbegin()/rend() to return mutable reverse iterators, and crbegin()/crend()
// to return constant reverse iterators. In C++11/C++14, all these have non-member
// equivalents that work with standard containers, C-like arrays, and any custom type that
// specializes them.

// In C++17, even more non-member functions have been added:
// std::data()
// std::size()
// std::empty()

// <iterator> header, which is implicitly included with any of the following headers:
// <array>, <deque>, <forward_list>, <list>, <map>, <regex>, <set>, <string>,
// <unordered_map>, <unordered_set>, and <vector>.

// In this recipe, we will refer to the std::begin()/std::end() functions, but everything
// discussed also applies to the other functions: std::cbegin()/std::cend(),
// std::rbegin()/std::rend(), and std::crbegin()/std::crend().

#include "recipe_5_09.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace recipe_5_10 {
  using namespace std::string_literals;

  template <typename F, typename C>
  void process(F&& f, C const& c)
  {
    std::for_each(std::begin(c), std::end(c), std::forward<F>(f));
  }

  template<class T>
  void print(T& container) {
    for (auto & item : container)
      std::cout << item << " ";
    std::cout << std::endl;
  }

  void execute()
  {
    std::cout << "\nRecipe 5.10: Container access with non-member functions."
              << "\n--------------------------------------------------------\n";

    std::cout << "\nUse the non-member std::begin()/std::end() function and the other "
                 "variants, as well as std::data(), std::size() and std::empty() with:\n";

    std::cout << "\nStandard containers:\n";
    std::vector<int> v1{ 1, 2, 3, 4, 5 };
    for (auto i = std::begin(v1); i != std::end(v1); ++i)
      std::cout << *i << " ";
    std::cout << std::endl;
    print(v1);

    std::vector<int> v2;
    std::copy(std::cbegin(v1), std::cend(v1), std::back_inserter(v2));
    print(v2);

    std::cout << "\n(C-like) arrays:\n";
    int a[5] = { 1, 2, 3, 4, 5 };
    print(a);
    auto pos = std::find_if(std::crbegin(a), std::crend(a),
                            [](int const n) { return n % 2 == 0; });
    std::cout << "First even member from back: " << *pos << std::endl;

    std::cout << "\nCustom types that provide corresponding member functions, "
                 "begin()/end(), data(), empty(), or size():\n";
    recipe_5_09::dummy_array<std::string, 5> sa;
    recipe_5_09::dummy_array<int, 5> sb;
    sa[0] = "1"s;
    sa[1] = "2"s;
    sa[2] = "3"s;
    sa[3] = "4"s;
    sa[4] = "5"s;

    std::transform(std::begin(sa), std::end(sa), std::begin(sb),
                   [](std::string const& s) { return std::stoi(s); });
    print(sa);
    print(sb);

    std::cout
      << "\nGeneric code (templates) where the type of the container is not known:\n";
    auto l = [](auto const e) { std::cout << e << " "; };
    process(l, v1);
    std::cout << std::endl;
    process(l, a);
    std::cout << std::endl;
    process(l, sa);
    std::cout << std::endl;
  }
}
