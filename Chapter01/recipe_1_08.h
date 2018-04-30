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
    std::cout << rate << std::endl;
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

      // using iterators
      std::cout << "\nUsing iterators:\n";

      for (auto it = rates.begin(); it != rates.end(); ++it) {
        std::cout << *it << std::endl;
      }

      // using an index
      std::cout << "\nUsing an index:\n";

      for (size_t i = 0; i < rates.size(); ++i) {
        std::cout << rates[i] << std::endl;
      }
    }

    {
      auto rates = getRates();

      std::cout << "\nUsing for_each:\n";
      std::for_each(rates.begin(), rates.end(), print_rate);

      std::cout << "\nUsing for_each with lambda:\n";
      std::for_each(rates.begin(), rates.end(),
                    [](auto const rate) { std::cout << rate << std::endl; });
    }

    {
      std::cout << "\nUsing ranges:\n";
      auto rates = getRates();
      for (int rate : rates)
        std::cout << rate << std::endl;

      for (int& rate : rates)
        rate *= 2;

      std::cout << "\nUsing ranges with rvalue:\n";
      for (auto&& rate : getRates())
        std::cout << rate << std::endl;

      for (auto& rate : rates)
        rate *= 2;

      std::cout << "Using ranges with const reference:\n";
      for (auto const& rate : rates)
        std::cout << rate << std::endl;
    }

    {
      std::cout << "\nUsing ranges with a map:\n";
      for (auto&& kvp : getRates2())
        std::cout << kvp.first << std::endl;

      std::cout << "\nUsing ranges with a map and std::tie:\n";
      for (auto&& kvp : getRates2()) {
        bool flag;
        int rate;
        std::tie(rate, flag) = kvp;

        std::cout << rate << std::endl;
      }

      std::cout << "\nUsing destructuring under C++17:\n";
      for (auto && [ rate, flag ] : getRates2())
        std::cout << rate << std::endl;
    }
  }
} // namespace recipe_1_08
