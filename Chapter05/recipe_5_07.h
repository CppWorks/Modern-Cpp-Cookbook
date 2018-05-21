#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

namespace recipe_5_07 {
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

  std::ostream& operator<< (std::ostream& stream, const Task& task) {
    stream << task.priority << " " << task.name << std::endl;
    return stream;
  }

  template<class T>
  void printVector(std::vector<T> vec)
  {
    for(auto& item : vec)
      std::cout << item << " ";
    std::cout << std::endl;
  }


  void execute()
  {
    std::cout << "\nRecipe 5.07: Using set operations on a range."
              << "\n---------------------------------------------\n";

    {
      std::cout << "\nstd::set_union() to compute the union of two ranges into a third range:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_union(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                     std::back_inserter(v3));
      printVector(v1);
      printVector(v2);
      printVector(v3);
      // v3 = {1, 2, 3, 3, 4, 4, 5, 6, 8}
    }

    {
      std::cout << "\nstd::merge() to merge the content of two ranges into a third one. "
                   "It copies the entire content of the input ranges into the output "
                   "one, not just their union:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::merge(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), std::back_inserter(v3));
      printVector(v1);
      printVector(v2);
      printVector(v3);
      // v3 = {1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 8}
    }

    {
      std::cout << "\nstd::set_intersection() to compute the intersection of the two ranges into a third range:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_intersection(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                            std::back_inserter(v3));
      printVector(v1);
      printVector(v2);
      printVector(v3);
      // v3 = {2, 3, 4}
    }

    {
      std::cout << "\nstd::set_difference() to compute the difference of two ranges into a third range:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                          std::back_inserter(v3));
      printVector(v1);
      printVector(v2);
      printVector(v3);
      // v3 = {1, 4, 5}
    }

    {
      std::cout << "\nstd::set_symmetric_difference(): the output range will contain "
                   "elements that are present in any of the input ranges, but only in "
                   "one:\n";

      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3;

      std::set_symmetric_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                                    std::back_inserter(v3));
      printVector(v1);
      printVector(v2);
      printVector(v3);
      // v3 = {1, 3, 4, 5, 6, 8}
    }

    {
      std::cout << "\nstd::includes()to check if one range is a subset of another range. "
                   "That is, all its elements are also present in the other range:\n";
      std::vector<int> v1{ 1, 2, 3, 4, 4, 5 };
      std::vector<int> v2{ 2, 3, 3, 4, 6, 8 };
      std::vector<int> v3{ 1, 2, 4 };
      std::vector<int> v4{};
      printVector(v1);
      printVector(v2);
      printVector(v3);
      std::cout << "v4 is empty\n\n";

      auto i1
        = std::includes(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend()); // i1 = false
      std::cout << "v2 includes v1: " << std::boolalpha << i1 << std::endl;

      auto i2
        = std::includes(v1.cbegin(), v1.cend(), v3.cbegin(), v3.cend()); // i2 = true
      std::cout << "v3 includes v1: " << std::boolalpha << i2 << std::endl;

      auto i3
        = std::includes(v1.cbegin(), v1.cend(), v4.cbegin(), v4.cend()); // i3 = true
      std::cout << "v4 includes v1: " << std::boolalpha << i3 << std::endl;
    }

    std::cout << "\nDemonstrating with a POD type called Task that we also used in a previous recipe:\n";
    {
      std::vector<Task> v1{
        { 10, "Task 1.1"s }, { 20, "Task 1.2"s }, { 20, "Task 1.3"s },
        { 20, "Task 1.4"s }, { 30, "Task 1.5"s }, { 50, "Task 1.6"s },
      };

      std::vector<Task> v2{
        { 20, "Task 2.1"s }, { 30, "Task 2.2"s }, { 30, "Task 2.3"s },
        { 30, "Task 2.4"s }, { 40, "Task 2.5"s }, { 50, "Task 2.6"s },
      };

      std::vector<Task> v3;

      printVector(v1);
      printVector(v2);

      std::cout << "std::set_union:\n";
        std::set_union(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                     std::back_inserter(v3));
        printVector(v1);
        printVector(v2);
      printVector(v3);
      // v3 = {{ 10, "Task 1.1" },{ 20, "Task 1.2" },{ 20, "Task 1.3" },
      //       { 20, "Task 1.4" },{ 30, "Task 1.5" },{ 30, "Task 2.3" },
      //       { 30, "Task 2.4" },{ 40, "Task 2.5" },{ 50, "Task 1.6" }}

      std::vector<Task> v4;
      std::cout << "std::merge:\n";
      std::merge(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), std::back_inserter(v4));
      printVector(v1);
      printVector(v2);
      printVector(v4);
      // v4 = {{ 10, "Task 1.1" },{ 20, "Task 1.2" },{ 20, "Task 1.3" },
      //       { 20, "Task 1.4" },{ 20, "Task 2.1" },{ 30, "Task 1.5" },
      //       { 30, "Task 2.2" },{ 30, "Task 2.3" },{ 30, "Task 2.4" },
      //       { 40, "Task 2.5" },{ 50, "Task 1.6" },{ 50, "Task 2.6" }}

      std::vector<Task> v5;
      std::cout << "std::set_intersection:\n";
      std::set_intersection(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                            std::back_inserter(v5));
      printVector(v1);
      printVector(v2);
      printVector(v5);
      // v5 = {{ 20, "Task 1.2" },{ 30, "Task 1.5" },{ 50, "Task 1.6" }}

      std::vector<Task> v6;
      std::cout << "std::set_difference:\n";
      std::set_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                          std::back_inserter(v6));
      printVector(v1);
      printVector(v2);
      printVector(v6);
      // v6 = {{ 10, "Task 1.1" },{ 20, "Task 1.3" },{ 20, "Task 1.4" }}

      std::vector<Task> v7;
      std::cout << "std::set_symmetric_difference:\n";
      std::set_symmetric_difference(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(),
                                    std::back_inserter(v7));
      printVector(v1);
      printVector(v2);
      printVector(v7);
      // v7 = {{ 10, "Task 1.1" },{ 20, "Task 1.3" },{ 20, "Task 1.4" }
      //       { 30, "Task 2.3" },{ 30, "Task 2.4" },{ 40, "Task 2.5" }}
    }
  }
}
