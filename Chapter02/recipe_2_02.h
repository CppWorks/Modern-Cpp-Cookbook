#pragma once

#include <bitset>
#include <iostream>
#include <limits.h>
// The numeric_limits<T> class template is available in the namespace std in the <limits> header.
#include <limits>

namespace recipe_2_02 {
  // Obsolete programming style with C-style macros like INT_MAX:
  int minimum(int const* const start, int const* const end)
  {
    int minval = INT_MAX;
    for (int const* p = start; p != end; ++p) {
      if (*p < minval)
        minval = *p;
    }
    return minval;
  }

  template <typename T, typename I>
  T minimum(I const start, I const end)
  {
    // Use min() and max() static methods to get the smallest and largest finite numbers
    // of a type.
    T minval = std::numeric_limits<T>::max();
    for (auto i = start; i < end; ++i) {
      if (*i < minval)
        minval = *i;
    }
    return minval;
  }

  template <typename T>
  void print_type_properties()
  {
    // Use other static methods and static constants to retrieve other properties of a numeric type.
    std::cout << "min=" << std::numeric_limits<T>::min() << std::endl
              << "max=" << std::numeric_limits<T>::max() << std::endl
              << "bits=" << std::numeric_limits<T>::digits << std::endl
              << "decdigits=" << std::numeric_limits<T>::digits10 << std::endl
              << "integral=" << std::numeric_limits<T>::is_integer << std::endl
              << "signed=" << std::numeric_limits<T>::is_signed << std::endl
              << "exact=" << std::numeric_limits<T>::is_exact << std::endl
              << "infinity=" << std::numeric_limits<T>::has_infinity << std::endl
              << "--------------------------------------" << std::endl;
  }

  int get_value()
  {
    return 0;
  }

  void execute()
  {
    std::cout << "\nRecipe 2.02: Limits and other properties of numeric types."
              << "\n----------------------------------------------------------\n";

    // C++ provides a class template called numeric_limits with specializations for every
    // numeric type that enables you to query the minimum and maximum value of a type, but
    // is not limited to that and offers additional constants for type properties
    // querying, such as whether a type is signed or not, how many bits it needs for
    // representing its values, for floating point types whether it can represent
    // infinity, and many others. All the static members of numeric_limits<T> are
    // constexpr, which means they can be used everywhere a constant expression is
    // expected.

    std::cout << "unsigned short properties:\n";
    print_type_properties<unsigned short>();
    std::cout << "double properties:\n";
    print_type_properties<double>();
    std::cout << "int properties:\n";
    print_type_properties<int>();

    int range[std::numeric_limits<char>::max() + 1] = { 0 };

    switch (get_value()) {
    case std::numeric_limits<int>::min():
      break;
    }

    auto n = 42;
    std::bitset<std::numeric_limits<decltype(n)>::digits> bits{
      static_cast<unsigned long long>(n)
    };
  }
} // namespace recipe_2_02
