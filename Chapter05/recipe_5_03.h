#pragma once

// A std::bitset is NOT a good choice when you do not know the number of bits at compile time.

// The standard alternative for this is to use the std::vector<bool> container that is a
// specialization of std::vector with space and speed optimizations, as implementations do
// not actually store Boolean values, but individual bits for each element.

// For this reason, however, std::vector<bool> does not meet the requirements of a
// standard container or sequential container, nor does std::vector<bool>::iterator meet
// the requirements of a forward iterator. As a result, this specialization cannot be used
// in generic code where a vector is expected. On the other hand, being a vector, it has a
// different interface from that of std::bitset and cannot be viewed as a binary
// representation of a number. There are no direct ways to construct std::vector<bool>
// from a number or string nor to convert to a number or string.

// The vector<bool> class is available in the std namespace in the <vector> header.

// An alternative to std::vector<bool> is std::dequeu<bool>, which is a standard container
// (a double-ended queue) that meets all container and iterator requirements and can be
// used with all standard algorithms. However, this will not have the space optimization
// that std::vector<bool> is providing.

#include <iostream>
#include <vector>
#include <algorithm>

namespace recipe_5_03 {

  // The std::vector<bool> interface is very different from std::bitset. If you want to be
  // able to write code in a similar manner, you can create a wrapper on
  // std::vector<bool>, which looks like std::bitset, where possible. The following
  // implementation provides members similar to what is available in std::bitset:

  class bitvector {
    std::vector<bool> bv;

  public:
    bitvector() = default;
    bitvector(bitvector const&) = default;
    bitvector(bitvector&&) = default;
    bitvector& operator=(bitvector const&) = default;
    bitvector& operator=(bitvector&&) = default;

    bitvector(std::vector<bool> const& bv)
      : bv(bv)
    {
    }
    bool operator[](size_t const i)
    {
      return bv[i];
    }

    inline bool any() const
    {
      for (auto b : bv)
        if (b)
          return true;
      return false;
    }

    inline bool all() const
    {
      for (auto b : bv)
        if (!b)
          return false;
      return true;
    }

    inline bool none() const
    {
      return !any();
    }

    inline size_t count() const
    {
      return std::count(bv.cbegin(), bv.cend(), true);
    }

    inline size_t size() const
    {
      return bv.size();
    }

    inline bitvector& add(bool const value)
    {
      bv.push_back(value);
      return *this;
    }

    inline bitvector& remove(size_t const index)
    {
      if (index >= bv.size())
        throw std::out_of_range("Index out of range");
      bv.erase(bv.begin() + index);
      return *this;
    }

    inline bitvector& set(bool const value = true)
    {
      for (size_t i = 0; i < bv.size(); ++i)
        bv[i] = value;
      return *this;
    }

    inline bitvector& set(size_t const index, bool const value = true)
    {
      if (index >= bv.size())
        throw std::out_of_range("Index out of range");
      bv[index] = value;
      return *this;
    }

    inline bitvector& reset()
    {
      for (size_t i = 0; i < bv.size(); ++i)
        bv[i] = false;
      return *this;
    }

    inline bitvector& reset(size_t const index)
    {
      if (index >= bv.size())
        throw std::out_of_range("Index out of range");
      bv[index] = false;
      return *this;
    }

    inline bitvector& flip()
    {
      bv.flip();
      return *this;
    }

    std::vector<bool>& data()
    {
      return bv;
    }
  };

  void print(std::vector<bool> bv) {
    for (auto item : bv)
      std::cout << item << " ";
    std::cout << std::endl;
  }


  void execute()
  {
    std::cout
      << "\nRecipe 5.03: Using vector<bool> for variable-size sequences of bits."
      << "\n--------------------------------------------------------------------\n";

    {
      std::cout
        << "\nTo manipulate an std::vector<bool>, use the same methods you would use for an std::vector<T>:\n";

      std::cout << "\nCreating an empty vector:\n";
      // create an empty vector
      std::vector<bool> bv; // []
      print(bv);

      std::cout << "Adding bits to the vector:\n";
      // add bits to the vector
      bv.push_back(true);  // [1]
      bv.push_back(true);  // [1, 1]
      bv.push_back(false); // [1, 1, 0]
      bv.push_back(false); // [1, 1, 0, 0]
      bv.push_back(true);  // [1, 1, 0, 0, 1]
      print(bv);

      std::cout << "\nSetting the values of individual bits:\n";
      // set values of individual bits
      bv[3] = true; // [1, 1, 0, 1, 1]
      print(bv);

      std::cout << "\nUsing generic algorithms:\n";
      // use generic algorithms
      auto count_of_ones = std::count(bv.cbegin(), bv.cend(), true);
      std::cout << "Count of 1s: " << count_of_ones << std::endl;

      std::cout << "\nRemoving bits from the vector:\n";
      // remove a bit from the vector
      bv.erase(bv.begin() + 2); // [1, 1, 1, 1]
      print(bv);
    }

    {
      // The index operator cannot return a reference to a specific element because
      // elements are not stored individually.
      std::vector<bool> bv;
      bv.resize(10);
      // auto& bit1 = bv[0]; // error

      // Dereferencing an iterator cannot produce a reference to bool for the same reason:
      // auto& bit2 = *bv.begin(); // error
    }

    {
      // Class bitvector is only a basic implementation, and if you want to use such a
      // wrapper, you should add additional methods, such as bit logic operations,
      // shifting, maybe reading and writing from and to streams:
      std::cout << "\nUsing custom bitvector class:\n";

      bitvector bv;
      bv.add(true).add(true).add(false); // [1, 1, 0]
      bv.add(false);                     // [1, 1, 0, 0]
      bv.add(true);                      // [1, 1, 0, 0, 1]

      if (bv.any())
        std::cout << "Bitvector has some 1s." << std::endl;
      if (bv.all())
        std::cout << "Bitvector has only 1s." << std::endl;
      if (bv.none())
        std::cout << "Bitvector has no 1s." << std::endl;
      std::cout << "Bitvector has " << bv.count() << " 1s." << std::endl;

      bv.set(2, true); // [1, 1, 1, 0, 1]
      bv.set();        // [1, 1, 1, 1, 1]

      bv.reset(0); // [0, 1, 1, 1, 1]
      bv.reset();  // [0, 0, 0, 0, 0]

      bv.flip(); // [1, 1, 1, 1, 1]
    }
  }
}
