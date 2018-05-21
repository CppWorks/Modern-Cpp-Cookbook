#pragma once

// In this recipe, we will see why vector should be the preferred choice for a container
// and what are the most common operations with vector.

// std::vector is very similar in semantics to C-like arrays but has a variable size.

// The rule of thumb for C++ containers is: use std::vector as the default container
// unless you have good reasons to use another one.

#include <array>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>

namespace recipe_5_01 {
  using namespace std::string_literals;

  void process(int const* const arr, int const size)
  {
    for (int i = 0; i < size; ++i)
      std::cout << arr[i] << " ";
    std::cout << std::endl;
  }

  struct foo {
    int a;
    double b;
    std::string c;

    foo(int a, double b, std::string const& c)
      : a(a)
      , b(b)
      , c(c)
    {
    }
  };

  void execute()
  {
    std::cout << "Recipe 5.01: Using vector as a default container.\n"
              << "-------------------------------------------------\n\n";

    std::cout << "Initialize a std::vector class template.\n";
    std::cout << ".......................................\n";
    {
      std::cout << "\nInitialize from an initialization list:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 5 };
      process(&v1[0], v1.size());
      // 1 2 3 4 5

      std::cout << "\nInitialize from a C-like array:\n";
      int arr[] = { 1, 2, 3, 4, 5 };
      // Note: arr + 5 (beyond the end pointer)
      std::vector<int> v2(arr, arr + 5);
      process(&v2[0], v2.size());
      // 1 2 3 4 5

      std::cout << "\nInitialize from another container:\n";
      std::list<int> l{ 1, 2, 3, 4, 5 };
      std::vector<int> v3(l.begin(), l.end());
      process(&v3[0], v3.size());
      // 1 2 3 4 5

      std::cout << "\nInitialize from a count and a value:\n";
      std::vector<int> v4(5, 1);
      process(&v4[0], v4.size());
      // 1 1 1 1 1
    }

    std::cout << "\nModify the content of std::vector.\n";
    std::cout << ".................................\n";
    {
      std::cout << "\nAdd an element at the end of the vector with push_back():\n";
      std::vector<int> v1{ 1, 2, 3, 4, 5 };
      v1.push_back(6);
      std::cout << "Remove an element from the end of the vector with pop_back():\n";
      v1.pop_back();
      process(&v1[0], v1.size());

      std::cout << "\nInsert anywhere in the vector with insert():\n";
      int arr[] = { 1, 2, 3, 4, 5 };
      std::vector<int> v2;
      v2.insert(v2.begin(), arr, arr + 5);
      process(&v2[0], v2.size());

      std::vector<foo> v3;
      std::cout << "\nAdd an element by creating it at the end of the vector with emplace_back():\n";
      v3.emplace_back(1, 1.0, "one"s);
      std::cout << "Insert an element by creating it anywhere in the vector with emplace():\n";
      v3.emplace(v3.begin(), 2, 2.0, "two"s);
      v3.emplace_back(3, 3.0, "three"s);
      for (auto& item : v3)
        std::cout << item.a << " " << item.b << " " << item.c << std::endl;
    }

    std::cout << "\nModify the whole content of the vector.\n";
    std::cout << ".......................................\n";
    {
      std::cout << "\nAssign from another vector with operator=; this replaces the content "
                   "of the container:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 5 };
      std::vector<int> v2{ 10, 20, 30 };
      v2 = v1;
      process(&v1[0], v1.size());
      process(&v2[0], v2.size());

      std::cout << "\nAssign from another sequence defined by a begin and end iterator "
                   "with the assign() method; this replaces the content of the "
                   "container:\n";
      int arr[] = { 1, 2, 3, 4, 5 };
      std::vector<int> v3;
      v3.assign(arr, arr + 5);
      process(&v3[0], v3.size());

      std::cout << "\nSwap the content of two vectors with the swap() method:\n";
      std::vector<int> v4{ 1, 2, 3, 4, 5 };
      std::vector<int> v5{ 10, 20, 30 };
      process(&v4[0], v4.size());
      process(&v5[0], v5.size());
      std::cout << "..............\n";
      v4.swap(v5);
      process(&v4[0], v4.size());
      process(&v5[0], v5.size());

      std::cout << "\nRemove all the elements with the clear() method: (Does not free "
                   "any memory.)";
      std::vector<int> v6{ 1, 2, 3, 4, 5 };
      v6.clear();
      process(&v6[0], v6.size());

      std::cout << "\nRemove one or more elements with the erase() method:\n";
      std::vector<int> v7{ 1, 2, 3, 4, 5 };
      v7.erase(v7.begin() + 2, v7.begin() + 4);
      process(&v7[0], v7.size());
    }

    std::cout << "\nTo get the address of the first element in a vector.\n";
    std::cout << "....................................................\n";
    {
      std::vector<int> v{ 1, 2, 3, 4, 5 };

      std::cout << "\nUse the data() method, which returns a pointer to the first element:\n";
      process(v.data(), static_cast<int>(v.size()));
      std::cout << "\nGet the address of the first element:\n";
      process(&v[0], static_cast<int>(v.size()));
      std::cout << "\nGet the address of the element referred by the front() method:\n";
      process(&v.front(), static_cast<int>(v.size()));
      std::cout << "\nGet the address of the element pointed by the iterator returned from begin()\n";
      process(&*v.begin(), static_cast<int>(v.size()));
    }

    {
      std::list<int> l{ 1, 2, 3, 4, 5 };
      std::vector<int> v(l.begin(), l.end());
      // process(v.data(), v.size());
    }

    {
      std::cout << "\nIf you need to free additional reserved memory, you can use the "
                   "shrink_to_fit() method to request this, but it is an implementation "
                   "decision whether to free any memory or not. An alternative to this "
                   "non-binding method, available since C++11, is to do a swap with a "
                   "temporary, empty vector: (Compare to clear().)\n";
      std::vector<int> v{ 1, 2, 3, 4, 5 };
      std::vector<int>().swap(v); // v.size = 0, v.capacity = 0
      process(&v[0], v.size());
    }
  }
}
