#pragma once

#include <iostream>

namespace recipe_1_09 {

  // simple array
  template <typename T, size_t const Size>
  class dummy_array {
    T data[Size] = {};

  public:
    T const& GetAt(size_t const index) const
    {
      if (index < Size)
        return data[index];
      throw std::out_of_range("index out of range");
    }

    void SetAt(size_t const index, T const& value)
    {
      if (index < Size)
        data[index] = value;
      else
        throw std::out_of_range("index out of range");
    }

    size_t GetSize() const
    {
      return Size;
    }
  };

  // To enable a custom type to be used in range-based for loops, you need to do the
  // following:

  // 1. Create mutable and constant iterators for the type that must implement the
  //    following operators:
  // - operator++ for incrementing the iterator.
  // - operator* for dereferencing the iterator and accessing the actual element pointed
  //   by the iterator.
  // - operator!= for comparing with another iterator for inequality.

  // 2. Provide free begin() and end() functions for the type.

  // We need to provide the following minimal implementation of an iterator class:
  // C = Collection of type T
  template <typename T, typename C, size_t const Size>
  class dummy_array_iterator_type {
  public:
    dummy_array_iterator_type(C& collection, size_t const index)
      : index(index)
      , collection(collection)
    {
    }

    bool operator!=(dummy_array_iterator_type const& other) const
    {
      return index != other.index;
    }

    T const& operator*() const
    {
      // GetAt is defined in our dummy_array class
      return collection.GetAt(index);
    }

    dummy_array_iterator_type const& operator++()
    {
      ++index;
      return *this;
    }

  private:
    size_t index;
    C& collection;
  };

  // We need to provide alias templates for mutable and constant iterators:
  template <typename T, size_t const Size>
  using dummy_array_iterator = dummy_array_iterator_type<T, dummy_array<T, Size>, Size>;

  template <typename T, size_t const Size>
  using dummy_array_const_iterator
    = dummy_array_iterator_type<T, dummy_array<T, Size> const, Size>;

  // We need to provide free begin() and end() functions that return the corresponding
  // begin and end iterators, with overloads for both alias templates:
  template <typename T, size_t const Size>
  inline dummy_array_iterator<T, Size> begin(dummy_array<T, Size>& collection)
  {
    return dummy_array_iterator<T, Size>(collection, 0);
  }

  template <typename T, size_t const Size>
  inline dummy_array_iterator<T, Size> end(dummy_array<T, Size>& collection)
  {
    return dummy_array_iterator<T, Size>(collection, collection.GetSize());
  }

  template <typename T, size_t const Size>
  inline dummy_array_const_iterator<T, Size> begin(dummy_array<T, Size> const& collection)
  {
    return dummy_array_const_iterator<T, Size>(collection, 0);
  }

  template <typename T, size_t const Size>
  inline dummy_array_const_iterator<T, Size> end(dummy_array<T, Size> const& collection)
  {
    return dummy_array_const_iterator<T, Size>(collection, collection.GetSize());
  }

  // Just a simple print function for testing.
  template <typename T, const size_t Size>
  void print_dummy_array(dummy_array<T, Size> const& arr)
  {
    // When performing argument dependent lookup in the range-based loop, the compiler
    // will identify the two begin() and end() functions that we wrote (that take a
    // reference to a dummy_array) and therefore the code it generates becomes valid.

    for (auto&& e : arr) {
      std::cout << e << " ";
    }
    std::cout << "\n";
  }

  // A possible alternative to enable range-based for loops for the simple range class we
  // considered for this recipe is to provide member begin() and end() functions. In
  // general, that could make sense only if you own and can modify the source code. On the
  // other hand, the solution shown in this recipe works in all cases and should be
  // preferred to other alternatives.

  void execute()
  {
    std::cout << "\nRecipe 1.09: Enabling range-based for loops for custom types."
              << "\n-------------------------------------------------------------\n";
    {
      std::cout << "\nRange-based for loops do not work out of the box with any type\n"
                   "representing a range, but require the presence of a begin() and\n"
                   "end() function (for non-array types) either as a member or free\n"
                   "function.\n";
      dummy_array<int, 3> arr;
      arr.SetAt(0, 1);
      arr.SetAt(1, 2);
      arr.SetAt(2, 3);

      std::cout << "\nPrinting custom array:\n";
      for (auto&& e : arr) {
        std::cout << e << " ";
      }
      std::cout << "\n";

      std::cout << "\nPrint custom array with separate function:\n";
      print_dummy_array(arr);
    }
  }
}
