#pragma once

// The iterators and adapters discussed in this recipe are available in the std namespace
// in the <iterator> header. If you include headers such as, <algorithm>, you do not have
// to explicitly include <iterator>.

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <vector>

template<class T>
void print(T container) {
  for(auto & item : container)
    std::cout << item << " ";
  std::cout << std::endl;
}

namespace recipe_5_08 {
  void execute()
  {
    std::cout
      << "\nRecipe 5.08: Using iterators to insert new elements in a container."
      << "\n-------------------------------------------------------------------\n";
    {
      std:: cout << "\nstd::back_inserter() to insert elements at the end, for containers that have a push_back() method:\n";
      std::vector<int> v{ 1, 2, 3, 4, 5 };
      print(v);
      std::fill_n(std::back_inserter(v), 3, 0);
      print(v);
      // v={1,2,3,4,5,0,0,0}
    }

    {
      std::cout << "\nstd::front_inserter() to insert elements at the beginning, for "
                   "containers that have a push_front() method:\n";

      std::list<int> l{ 1, 2, 3, 4, 5 };
      print(l);
      std::fill_n(std::front_inserter(l), 3, 0);
      print(l);
      // l={0,0,0,1,2,3,4,5}
    }

    {
      std::cout << "\nstd::inserter() to insert anywhere in a container, for containers "
        "that have an insert() method:\n";

      std::vector<int> v{ 1, 2, 3, 4, 5 };
      print(v);
      std::fill_n(std::inserter(v, v.begin()), 3, 0);
      print(v);

      // v={0,0,0,1,2,3,4,5}
    }

    {
      std::cout << "\nstd::inserter() to insert anywhere in a container, for containers "
        "that have an insert() method:\n";

      std::list<int> l{ 1, 2, 3, 4, 5 };
      print(l);
      auto it = l.begin();
      std::advance(it, 3);

      std::fill_n(std::inserter(l, it), 3, 0);
      print(l);
      // l={1,2,3,0,0,0,4,5}
    }

    {
      std::vector<int> v{ 1, 2, 3, 4, 5 };
      std::back_insert_iterator<std::vector<int>> it(v);
      *it = 6;
    }

    {
      std::list<int> l{ 1, 2, 3, 4, 5 };
      std::front_insert_iterator<std::list<int>> it(l);
      *it = 0;
    }

    {
      std::vector<int> v{ 1, 2, 3, 4, 5 };
      *std::back_inserter(v) = 6;
    }

    {
      std::list<int> l{ 1, 2, 3, 4, 5 };
      *std::front_inserter(l) = 0;
    }
  }
}
