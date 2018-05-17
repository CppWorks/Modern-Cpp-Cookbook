#pragma once

#include "funclib.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

// To implement the MAP function you should:

// Use std::transform on containers that support iterating and assignment to the elements,
// such as std::vector or std::list.

// Use other means such as explicit iteration and insertion for containers that do not
// support assignment to the elements, such as std::map.

// To implement the FOLD function you should:

// Use std::accumulate() on containers that support iterating.

// Use other means to explicitly process containers that do not support iterating, such as
// std::queue

// We have implemented the map in a functional way, without side-effects. That means it
// preserves the original range and returns a new one.

namespace recipe_3_07 {
  using namespace std::string_literals;

  template <class T = double>
  struct fround {
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
    operator()(const T& value) const
    {
      return std::round(value);
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 3.07: Implementing higher-order functions map and fold using "
                 "STL algorithms."
              << "\n---------------------------------------------------------------------"
                 "--------------\n";

    {
      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto r = funclib::mapf([](int const i) { return std::abs(i); }, vnums);
      // r = {0, 2, 3, 5, 1, 6, 8, 4, 9}
      for (auto& item : r)
        std::cout << item << " ";
      std::cout << std::endl;

      auto lnums = std::list<int>{ 1, 2, 3, 4, 5 };
      auto l = funclib::mapf([](int const i) { return i * i; }, lnums);
      // l = {1, 4, 9, 16, 25}
      for (auto& item : l)
        std::cout << item << " ";
      std::cout << std::endl;

      auto amounts = std::array<double, 5>{ 10.42, 2.50, 100.0, 23.75, 12.99 };
      auto a = funclib::mapf(fround<>(), amounts);
      // a = {10.0, 3.0, 100.0, 24.0, 13.0}
      for (auto& item : a)
        std::cout << item << " ";
      std::cout << std::endl;

      auto words
        = std::map<std::string, int>{ { "one", 1 }, { "two", 2 }, { "three", 3 } };
      auto m = funclib::mapf(
        [](std::pair<std::string, int> const kvp) {
          return std::make_pair(funclib::mapf(toupper, kvp.first), kvp.second);
        },
        words);
      // m = { {"ONE", 1}, {"TWO", 2}, {"THREE", 3} }
      for (auto & [ key, value ] : m) {
        std::cout << key << " " << value << std::endl;
      }

      auto priorities = std::queue<int>();
      priorities.push(10);
      priorities.push(20);
      priorities.push(30);
      priorities.push(40);
      priorities.push(50);
      auto p = funclib::mapf([](int const i) { return i > 30 ? 2 : 1; }, priorities);
      // p = {1, 1, 1, 2, 2}
      auto tmp_q = p;

      while (!tmp_q.empty()) {
        auto q_element = tmp_q.front();
        std::cout << q_element << " ";
        tmp_q.pop();
      }
      std::cout << "\n";
    }

    {
      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };
      auto s1 = funclib::foldl([](const int s, const int n) { return s + n; }, vnums,
                               0);                       // s1 = 22
      auto s2 = funclib::foldl(std::plus<>(), vnums, 0); // s2 = 22

      auto s3 = funclib::foldr([](const int s, const int n) { return s + n; }, vnums,
                               0);                       // s3 = 22
      auto s4 = funclib::foldr(std::plus<>(), vnums, 0); // s4 = 22

      auto texts = std::vector<std::string>{ "hello"s, " "s, "world"s, "!"s };
      auto txt1 = funclib::foldl(
        [](std::string const& s, std::string const& n) { return s + n; }, texts, ""s);
      // txt1 = "hello world!"
      auto txt2 = funclib::foldr(
        [](std::string const& s, std::string const& n) { return s + n; }, texts, ""s);
      // txt2 = "!world hello"

      char chars[] = { 'c', 'i', 'v', 'i', 'c' };
      auto str1 = funclib::foldl(std::plus<>(), chars, ""s); // str1 = "civic"
      auto str2 = funclib::foldr(std::plus<>(), chars, ""s); // str2 = "civic"

      auto words
        = std::map<std::string, int>{ { "one", 1 }, { "two", 2 }, { "three", 3 } };
      auto count = funclib::foldl(
        [](int const s, std::pair<std::string, int> const kvp) { return s + kvp.second; },
        words, 0);

      auto q = std::queue<int>{};
      q.push(1);
      q.push(2);
      q.push(3);
      q.push(4);
      q.push(5);
      auto sum = funclib::foldl(std::plus<>(), q, 0); // sum = 15
      std::cout << sum << std::endl;
    }

    {
      auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

      auto s = funclib::foldl(
        std::plus<>(),
        funclib::mapf([](int const i) { return i + i; },
                      funclib::mapf([](int const i) { return std::abs(i); }, vnums)),
        0);
      // s = 76
      std::cout << s << std::endl;
    }
  }
}
