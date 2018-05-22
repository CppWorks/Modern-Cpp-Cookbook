#pragma once

// Type traits are basically meta-types that provide information about other types. The
// type traits library contains a long list of traits for querying type properties (such
// as checking whether a type is an integral type or whether two types are the same), but
// also for performing type transformation (such as removing const and volatile qualifiers
// or adding a pointer to a type).

// There are actually two categories of type traits:

// Traits that PROVIDE INFORMATION about types, their properties, or their relations (such
// as is_integer, is_arithmetic, is_array, is_enum, is_class, is_const, is_pod,
// is_constructible, is_same, and so on). These traits provide a constant bool member
// called VALUE.

// Traits that MODIFY PROPERTIES of types (such as add_const, remove_const, add_pointer,
// remove_pointer, make_signed, make_unsigned, and so on). These traits provide a member
// typedef called TYPE that represents the transformed type.

#include <string>
#include <type_traits>
#include <iostream>

namespace recipe_6_09 {
  using namespace std::string_literals;

  // 1. With enable_if, to define preconditions for the types a function template can be instantiated with:
  template <typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
  T multiply(T const t1, T const t2)
  {
    return t1 * t2;
  }

  template <typename T>
  struct pod_wrapper {
    // 2. With static_assert, to ensure that invariants are met:
    static_assert(std::is_pod<T>::value, "Type is not a POD!");
    T value;
  };

  template <typename T>
  struct const_wrapper {
    // 3. With std::conditional, to select between types:
    typedef typename std::conditional<std::is_const<T>::value, T,
                                      typename std::add_const<T>::type>::type const_type;
  };

  template <typename T>
  auto process(T arg)
  {
    // 4. With constexpr if, to enable the compiler to generate different code based on the type the template is instantiated with:
    if constexpr (std::is_same<T, bool>::value)
      return !arg;
    else if constexpr (std::is_integral<T>::value)
      return -arg;
    else if constexpr (std::is_floating_point<T>::value)
      return std::abs(arg);
    else
      return arg;
  }

  void execute()
  {
    std::cout << "\nRecipe 6.09: Using type traits to query properties of types."
              << "\n------------------------------------------------------------\n";
    std::cout << "See source code and next recipe.\n\n";
    {
      auto v1 = multiply(42.0, 1.5); // OK
                                     // auto v2 = multiply("42"s, "1.5"s); // error
    }

    {
      pod_wrapper<int> i{ 42 }; // OK
                                // pod_wrapper<std::string> s{ "42"s }; // error
    }

    {
      static_assert(std::is_const<const_wrapper<int>::const_type>::value);
      static_assert(std::is_const<const_wrapper<int const>::const_type>::value);
    }

    {
      auto v1 = process(false); // true
      auto v2 = process(42);    // -42
      auto v3 = process(-42.0); // 42.0
      auto v4 = process("42"s); // "42"
    }
  }
}
