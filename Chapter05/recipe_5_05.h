#pragma once

// Some standard containers, std::list and std::forward_list, provide a member function,
// sort(), which is optimized for those containers. These member functions should be
// preferred over the general standard algorithm, std::sort().

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace recipe_5_05 {
  using namespace std::string_literals;

  struct Task {
    int priority;
    std::string name;
  };

  bool operator<(Task const& lhs, Task const& rhs)
  {
    return lhs.priority < rhs.priority;
  }

  bool operator>(Task const& lhs, Task const& rhs)
  {
    return lhs.priority > rhs.priority;
  }

  void print(std::vector<int> vi) {
    for(auto & item : vi)
      std::cout << item << " ";
    std::cout << std::endl;
  }

  void print(std::vector<Task> tasks) {
  for(auto & task : tasks)
    std::cout << "{ " << task.priority << " " << task.name << " } ";
  std::cout << std::endl;
  }

  void execute()
  {
    std::cout
      << "\nRecipe 5.05: Sorting a range."
      << "\n-----------------------------\n";
    {
      std::cout << "\nUse std::sort() for sorting a range:\n";
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
      print(v);

      std::sort(v.begin(), v.end());
      // v = {1, 1, 2, 3, 5, 8, 13}
      print(v);

      std::sort(v.begin(), v.end(), std::greater<>());
      // v = {13, 8, 5, 3, 2, 1 ,1}
      print(v);
    }

    {
      std::cout << "\nUse std::stable_sort() for sorting a range but keeping the "
                   "original order of the equal elements:\n";

      std::vector<Task> v{
        { 10, "Task 1"s }, { 40, "Task 2"s }, { 25, "Task 3"s },
        { 10, "Task 4"s }, { 80, "Task 5"s }, { 10, "Task 6"s },
      };
      print(v);

      std::stable_sort(v.begin(), v.end());
      print(v);
      // {{ 10, "Task 1" },{ 10, "Task 4" },{ 10, "Task 6" },
      //  { 25, "Task 3" },{ 40, "Task 2" },{ 80, "Task 5" }}

      std::stable_sort(v.begin(), v.end(), std::greater<>());
      print(v);
      // {{ 80, "Task 5" },{ 40, "Task 2" },{ 25, "Task 3" },
      //  { 10, "Task 1" },{ 10, "Task 4" },{ 10, "Task 6" }}

      // the same in this case but not guaranteed
      std::sort(v.begin(), v.end());
      print(v);
    }

    {
      std::cout << "\nUse std::partial_sort() for sorting a part of a range (and leaving "
        "the rest in an unspecified order):\n";
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
      print(v);

      std::partial_sort(v.begin(), v.begin() + 4, v.end());
      print(v);
      // v = {1, 1, 2, 3, ?, ?, ?}

      std::partial_sort(v.begin(), v.begin() + 4, v.end(), std::greater<>());
      print(v);
      // v = {13, 8, 5, 3, ?, ?, ?}
    }

    {
      std::cout << "\nUse std::partial_sort_copy() for sorting a part of a range by "
        "copying the sorted elements to a second range and leaving the "
        "original range unchanged:\n";

      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
      std::vector<int> vc(v.size());
      print(v);
      print(vc);

      std::partial_sort_copy(v.begin(), v.end(), vc.begin(), vc.end());
      print(v);
      print(vc);
      // v  = {3, 13, 5, 8, 1, 2, 1}
      // vc = {1, 1, 2, 3, 5, 8, 13}

      std::partial_sort_copy(v.begin(), v.end(), vc.begin(), vc.end(), std::greater<>());
      print(v);
      print(vc);
      // vc = {13, 8, 5, 3, 2, 1, 1}
    }

    {
      std::cout << "\nUse std::nth_element() for sorting a range so that the Nth element "
                   "is the one that would be in that position if the range was "
                   "completely sorted, and the elements before it are all smaller and "
                   "the ones after it are all greater, without any guarantee that they "
                   "are also ordered:\n";

      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
      print(v);

      std::nth_element(v.begin(), v.begin() + 3, v.end());
      print(v);
      // pivot point: 8
      // all values < 8 to the left of 8, all values bigger than 8 to the right of 8:
      // v = {2, 1, 1, 3, 5, 8, 13}

      std::nth_element(v.begin(), v.begin() + 3, v.end(), std::greater<>());
      print(v);
      // pivot point: 3 (see vector above: v = {2, 1, 1, 3, 5, 8, 13} )
      // all values bigger than 3 to the left of 3, all values smaller than 3 to the right of 3:
      // v = {8, 13, 5, 3, 2, 1, 1}
    }

    {
      std::cout << "\nUse std::is_sorted() to check whether a range is sorted:\n";

      std::vector<int> v{ 1, 1, 2, 3, 5, 8, 13 };
      print(v);

      auto sorted = std::is_sorted(v.cbegin(), v.cend());
      std::cout << "Vector is sorted: " << std::boolalpha << sorted << std::endl;

      sorted = std::is_sorted(v.cbegin(), v.cend(), std::greater<>());
      std::cout << "Vector is reverse sorted: " << std::boolalpha << sorted << std::endl;
    }

    {
      std::cout << "\nUse std::is_sorted_until() to find a sorted subrange from the beginning of a range:\n";
      std::vector<int> v{ 3, 13, 5, 8, 1, 2, 1 };
      print(v);

      auto it = std::is_sorted_until(v.cbegin(), v.cend());
      auto length = std::distance(v.cbegin(), it);
      std::cout << "Vector is sorted until: " << *it << " at index: " << length << std::endl;
    }
  }
}
