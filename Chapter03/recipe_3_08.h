#pragma once

#include "funclib.h"
#include <iostream>
#include <string>

namespace recipe_3_08 {
  template <typename F, typename G>
  auto operator*(F&& f, G&& g)
  {
    return funclib::compose(std::forward<F>(f), std::forward<G>(g));
  }

  void execute()
  {
    std::cout << "\nRecipe 3.08: Composing functions into a higher-order function."
              << "\n--------------------------------------------------------------\n";

    using namespace funclib;

    auto vnums = std::vector<int>{ 0, 2, -3, 5, -1, 6, 8, -4, 9 };

    {
      auto v = compose([](int const n) { return std::to_string(n); },
                       [](int const n) { return n * n; })(-3);

      auto n = compose(
        [](int const n) { return std::to_string(n); }, [](int const n) { return n * n; },
        [](int const n) { return n + n; }, [](int const n) { return std::abs(n); })(-3);

      auto s
        = compose([](std::vector<int> const& v) { return foldl(std::plus<>(), v, 0); },
                  [](std::vector<int> const& v) {
                    return mapf([](int const i) { return i + i; }, v);
                  },
                  [](std::vector<int> const& v) {
                    return mapf([](int const i) { return std::abs(i); }, v);
                  })(vnums);
    }

    {
      auto n = ([](int const n) { return std::to_string(n); } *
                [](int const n) { return n * n; } * [](int const n) { return n + n; } *
                [](int const n) { return std::abs(n); })(-3);

      auto c = [](std::vector<int> const& v) { return foldl(std::plus<>(), v, 0); } *
        [](std::vector<int> const& v) {
          return mapf([](int const i) { return i + i; }, v);
        }
        * [](std::vector<int> const& v) {
            return mapf([](int const i) { return std::abs(i); }, v);
          };

      auto s = c(vnums);
    }
  }
}
