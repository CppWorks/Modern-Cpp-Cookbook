#pragma once

// The standard library provides several unordered associative containers:
// std::unordered_set, std::unordered_multiset, std::unordered_map, and
// std::unordered_map. These containers do not store their elements in a particular order;
// instead, they are grouped in buckets. The bucket an element belongs to depends on the
// hash value of the element. These standard containers use, by default, the std::hash
// class template to compute the hash value. The specialization for all basic types and
// also some library types is available. However, for custom types, you must specialize
// the class template yourself.

#include <iostream>
#include <set>
#include <string>
#include <unordered_set>

namespace recipe_6_03 {
  using namespace std::string_literals;

  struct Item {
    int id;
    std::string name;
    double value;

    Item(int const id, std::string const& name, double const value)
      : id(id)
      , name(name)
      , value(value)
    {
    }

    // This class provides equality operators. Use all fields in the hashing algorithm
    // that are used in the equal comparator.

    // If your custom type contains an array and is used to determine the equality of
    // two objects and, therefore, needs to be used to compute the hash, then treat the
    // array as if its elements were data members of the class. In other words, apply
    // the same algorithm described earlier for all elements of the array.
    bool operator==(Item const& other) const
    {
      return id == other.id && name == other.name && value == other.value;
    }

    bool operator!=(Item const& other) const
    {
      return !(*this == other);
    }

    bool operator<(Item const& other) const
    {
      return id < other.id || name < other.name || value < other.value;
    }
  };
}

// The algorithm described here was presented in the book Effective Java 2nd Edition by
// Joshua Bloch.
namespace std {
  // The specialization must be in the namespace std because that is the namespace where
  // the class template hash is defined:
  template <>
  // 1. Specialize the std::hash class template for your custom type:
  struct hash<recipe_6_03::Item> {
    // 2. Define synonyms for the argument and result type:
    typedef recipe_6_03::Item argument_type;
    typedef size_t result_type;

    // 3. Implement the call operator so that it takes a constant reference to your type
    // and returns a hash value:
    result_type operator()(argument_type const& item) const
    {
      // Start with an initial value that should be a prime number:
      result_type hashValue = 17;
      // For each field use following formula to adjust the hash value:
      // hashValue = prime * hashValue + hashFunc(field)

      // You can use the same prime number for all fields with the above formula, but it
      // is recommended to have a different value (eg. 31).

      // The use of prime 31 is advantageous for performance optimizations, because 31 * x
      // can be replaced by the compiler with (x << 5) - x, which is faster. Similarly,
      // you can use 127, because 127 * x is equal to (x << 7) - x or 8191, because 8191 *
      // x is equal to (x << 13) - x.

      // Use specialization of std::hash to determine the hash value for class data
      // members.
      hashValue = 31 * hashValue + std::hash<int>{}(item.id);
      hashValue = 31 * hashValue + std::hash<std::string>{}(item.name);
      hashValue = 31 * hashValue + std::hash<double>{}(item.value);

      return hashValue;
    }
  };
}

namespace recipe_6_03 {
  void execute()
  {
    std::cout << "\nRecipe 6.03: Generating hash values for custom types."
              << "\n-----------------------------------------------------\n";

    std::set<Item> set1{
      { 1, "one"s, 1.0 },
      { 2, "two"s, 2.0 },
      { 3, "three"s, 3.0 },
      { 4, "four"s, 4.0 },
    };

    for (auto& item : set1)
      std::cout << item.value << " " << item.name << " " << item.id << std::endl;

    std::unordered_set<Item> set2{
      { 1, "one"s, 1.0 },
      { 2, "two"s, 2.0 },
      { 3, "three"s, 3.0 },
      { 4, "four"s, 4.0 },
    };

    std::cout << "------------\n";

    for(auto& item : set2)
      std::cout << item.value << " " << item.name << " " << item.id <<  std::endl;
  }
}
