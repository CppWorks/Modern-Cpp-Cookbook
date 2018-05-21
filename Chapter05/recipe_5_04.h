#pragma once

//  All these algorithms are available in the std namespace in the <algorithm> header.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

// default_searcher: basically delegates the searching to the standard std::search() algorithm.

// boyer_moore_searcher: implements the Boyer-Moore algorithm for string searching.

// boyer_moore_horspool_algorithm: implements the Boyer-Moore-Horspool algorithm for string searching.

// Many standard containers have a member function find(), for finding elements in the
// container. When such a method is available and suits your needs, it should be preferred
// to the general algorithms because these member functions are optimized based on the
// particularities of each container.

namespace recipe_5_04 {
  using namespace std::string_literals;

  inline bool IsPrime(int const number)
  {
    if (((!(number & 1)) && number != 2) || (number < 2)
        || (number % 3 == 0 && number != 3))
      return (false);

    for (int k = 1; 36 * k * k - 12 * k < number; ++k)
      if ((number % (6 * k + 1) == 0) || (number % (6 * k - 1) == 0))
        return (false);

    return true;
  }

  void print(std::vector<int> vi) {
    for(auto & item : vi)
      std::cout << item << " ";
    std::cout << std::endl;
  }

  void execute()
  {
    std::cout
      << "\nRecipe 5.04: Finding elements in a range."
      << "\n-----------------------------------------\n";

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };
      print(v);

      std::cout << "\nUse std::find() to find a value in a range:\n";
      auto it = std::find(v.cbegin(), v.cend(), 3);
      if (it != v.cend())
        std::cout << *it << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::find_if() to find a value in a range that meets a criterion from a unary predicate:\n";
      auto it = std::find_if(v.cbegin(), v.cend(), [](int const n) { return n > 10; });
      if (it != v.cend())
        std::cout << *it << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::find_if_not() to find a value in a range that does not "
                   "meet a criterion from a unary predicate:\n";
      auto it
        = std::find_if_not(v.cbegin(), v.cend(), [](int const n) { return n % 2 == 1; });
      if (it != v.cend())
        std::cout << *it << std::endl;
    }

    {
      std::vector<int> v1{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 };
      std::vector<int> v2{ 1, 0, 1 };

      std::cout << "\nUse std::find_end() to find the last occurrence of a subrange of elements in a range:\n";
      auto it = std::find_end(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());

      if (it != v1.cend())
        std::cout << "Found at index " << std::distance(v1.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };
      std::vector<int> p{ 5, 7, 11 };

      std::cout << "\nUse std::find_first_of() to search for the occurrence of any value "
                   "from a range in another range:\n";
      auto it = std::find_first_of(v.cbegin(), v.cend(), p.cbegin(), p.cend());

      if (it != v.cend())
        std::cout << "Found " << *it << " at index " << std::distance(v.cbegin(), it)
                  << std::endl;
    }

    {
      auto text = "The quick brown fox jumps over the lazy dog"s;
      auto word = "over"s;

      std::cout << "\nUse std::search() to search for the first occurrence of a subrange in a range:\n";
      auto it = std::search(text.cbegin(), text.cend(), word.cbegin(), word.cend());

      if (it != text.cend())
        std::cout << "Found \"" << word << "\" at index " << std::distance(text.cbegin(), it)
                  << std::endl;
    }

    {
      auto text = "The quick brown fox jumps over the lazy dog"s;
      auto word = "over"s;

      std::cout << "\nUse std::search() with a searcher, e.g. Boyer-Moore or Boyer-Moore-Horspool string searcher:\n";
      auto it = std::search(text.cbegin(), text.cend(),
                            std::boyer_moore_searcher(word.cbegin(), word.cend()));

      if (it != text.cend())
        std::cout << "Found " << word << " at index " << std::distance(text.cbegin(), it)
                  << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 };

      std::cout << "\nUse std::search_n() to search for N consecutive occurrences of a value in a range:\n";
      auto it = std::search_n(v.cbegin(), v.cend(), 2, 0);

      if (it != v.cend())
        std::cout << "Found at index " << std::distance(v.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::adjacent_find() to find two adjacent elements in a range "
                   "that are equal or satisfy a binary predicate:\n";
      auto it = std::adjacent_find(v.cbegin(), v.cend());
      if (it != v.cend())
        std::cout << "Found at index " << std::distance(v.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::adjacent_find() to find two adjacent elements in a range "
        "that are equal or satisfy a binary predicate:\n";
      auto it = std::adjacent_find(v.cbegin(), v.cend(), [](int const a, int const b) {
        return IsPrime(a) && IsPrime(b);
      });

      if (it != v.cend())
        std::cout << "Found at index " << std::distance(v.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::binary_search() to find whether an element exists in a sorted range:\n";
      auto success = std::binary_search(v.cbegin(), v.cend(), 8);

      if (success)
        std::cout << "Found!" << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::lower_bound() to find the first element in a range not less than a specified value:\n";
      auto it = std::lower_bound(v.cbegin(), v.cend(), 1);

      if (it != v.cend())
        std::cout << "Lower bound at " << std::distance(v.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::upper_bound() to find the first element in a range greater than a specified value:\n";
      auto it = std::upper_bound(v.cbegin(), v.cend(), 1);

      if (it != v.cend())
        std::cout << "Upper bound at " << std::distance(v.cbegin(), it) << std::endl;
    }

    {
      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };

      std::cout << "\nUse std::equal_range() to find a subrange in a range whose values "
                   "are equal to a specified value. The two returned iterators are "
                   "equivalent to those returned by std::lower_bound() and "
                   "std::upper_bound():\n";
      auto bounds = std::equal_range(v.cbegin(), v.cend(), 1);

      std::cout << "Range between indexes " << std::distance(v.cbegin(), bounds.first)
                << " and " << std::distance(v.cbegin(), bounds.second) << std::endl;
    }
  }
}
