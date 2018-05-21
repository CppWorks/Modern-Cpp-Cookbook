#pragma once

// Except for std::iota() , which is available in the <numeric> header, all the other
// algorithms are found in the <algorithm> header.

#include <array>
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <iostream>

void print(std::vector<int> vi) {
  for(auto & item : vi)
    std::cout << item << " ";
  std::cout << std::endl;
}

template <class T, size_t size>
void print(std::array<T, size> ai)
{
  for (auto& item : ai)
    std::cout << item << " ";
  std::cout << std::endl;
}

namespace recipe_5_06 {
  void execute()
  {
    std::cout << "\nRecipe 5.06: Initializing a range."
              << "\n----------------------------------\n";

    {
      std::cout << "\nUse std::fill() to assign a value to all the elements of a range:\n";
      std::vector<int> v(5);
      std::fill(v.begin(), v.end(), 42);
      print(v);
      // v = {42, 42, 42, 42, 42}

      std::array<int, 5> a;
      std::fill(a.begin(), a.end(), 42);
      print(a);
      // a = {42, 42, 42, 42, 42}
    }

    {
      std::cout << "\nstd::fill_n() to assign values to a number of elements of a range:\n";
      std::vector<int> v(10);
      std::fill_n(v.begin(), 5, 42);
      print(v);
      // v = {42, 42, 42, 42, 42, 0, 0, 0, 0, 0}
    }

    {
      std::cout << "\nstd::generate() to assign the value returned by a function to the elements of a range:\n";
      std::random_device rd{};
      std::mt19937 mt{ rd() };
      std::uniform_int_distribution<> ud{ 1, 10 };

      std::vector<int> v(5);

      std::generate(v.begin(), v.end(), [&ud, &mt] { return ud(mt); });
      print(v);
    }

    {
      std::cout << "\nstd::generate_n() to assign the value returned by a function to a "
                   "number of elements of a range:\n";
      std::vector<int> v(10);

      auto i = 0;
      std::generate_n(v.begin(), v.size() / 2, [&i] { i++; return i * i; });
      print(v);
      // v = {1, 4, 9, 16, 25}
    }

    {
      std::cout << "\nstd::iota() - the name iota is taken from the programming language "
                   "APL - to assign sequentially increasing values to the elements of a "
                   "range:\n";
      std::vector<int> v(5);

      std::iota(v.begin(), v.end(), 1);
      print(v);
      // v = {1, 2, 3, 4, 5}
    }
  }
}
