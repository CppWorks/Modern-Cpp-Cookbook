#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

namespace recipe_1_08 {
  std::vector<int> getRates()
  {
    return std::vector<int>{ 1, 1, 2, 3, 5, 8, 13 };
  }

  void print_rate(int const rate)
  {
    std::cout << rate << " ";
  }

  std::multimap<int, bool> getRates2()
  {
    return std::multimap<int, bool>{ { 1, true }, { 1, true },  { 2, false }, { 3, true },
                                     { 5, true }, { 8, false }, { 13, true } };
  }

  void execute()
  {
    std::cout << "\nRecipe 1.08: Using range-based for loops to iterate on a range."
              << "\n---------------------------------------------------------------\n";
    {
      auto rates = getRates();

      std::cout << "\nObsolete/old style using iterators.\n";
      for (auto it = rates.begin(); it != rates.end(); ++it) {
        std::cout << *it << " ";
      }
      std::cout << "\n";

      std::cout << "\nObsolete/old style using an index:\n";
      for (size_t i = 0; i < rates.size(); ++i) {
        std::cout << rates[i] << " ";
      }
      std::cout << "\n";
    }

    {
      auto rates = getRates();

      std::cout << "\nObsolete/old style using for_each:\n";
      std::for_each(rates.begin(), rates.end(), print_rate);
      std::cout << "\n";
      std::cout << "\nObsolete/old style using for_each with a lambda:\n";
      std::for_each(rates.begin(), rates.end(),
                    [](auto const rate) { std::cout << rate << " "; });
      std::cout << "\n";
    }

    {
      std::cout << "\nRange-based for loops can be used in various ways:\n\n";

      std::cout << "By committing to a specific type for the elements of the sequence:\n";
      auto rates = getRates();
      for (int rate : rates)
        std::cout << rate << " ";
      std::cout << "\n";

      for (int& rate : rates)
        rate *= 2;

      std::cout << "\nBy not specifying a type and letting the compiler deduce it:\n";
      for (auto&& rate : getRates())
        std::cout << rate << " ";
      std::cout << "\n";

      for (auto& rate : rates)
        rate *= 2;

      for (auto const& rate : rates)
        std::cout << rate << " ";
      std::cout << "\n";

      std::cout << "\nUsing structured bindings and decomposition declaration in C++17\n";
      for (auto && [ rate, flag ] : getRates2())
        std::cout << rate << " ";
      std::cout << "\n";
    }

    {
      std::cout << "\nUsing ranges with a map:\n";
      for (auto&& kvp : getRates2())
        std::cout << kvp.first << " ";
      std::cout << "\n";

      std::cout << "\nUsing ranges with a map and std::tie:\n";
      for (auto&& kvp : getRates2()) {
        bool flag;
        int rate;
        std::tie(rate, flag) = kvp;

        std::cout << rate << " ";
      }
      std::cout << "\n";
    }
  }
} // namespace recipe_1_08
