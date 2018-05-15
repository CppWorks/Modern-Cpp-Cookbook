#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <random>

// Initialize a generator in order to produce the BEST sequence of pseudo-random numbers.
// In order to produce the best results, engines must have all their internal state
// properly initialized before generating numbers.

namespace recipe_2_04 {
  void monte_carlo_simulation()
  {
    auto seed_data = std::array<int, std::mt19937::state_size>{};

    // 1. Use a std::random_device to produce random numbers to be used as seeding values:
    std::random_device rd;

    // 2. Generate random data for all internal bits of the engine:
    std::generate(std::begin(seed_data), std::begin(seed_data), std::ref(rd));

    // 3. Create an std::seed_seq object from the previously generated pseudo-random data:
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));

    // 4. Create an engine object and initialize all the bits representing the internal
    // state of the engine; for example, a mt19937 has 19,937 bits of internal states:
    auto eng = std::mt19937{ seq };

    // 5. Use the appropriate distribution based on the requirements of the application:
    auto dist = std::uniform_real_distribution<>{ 0, 1 };

    auto const Simulations = 10;
    auto const Samples = 50000;

    std::cout << "\nCalculating PI several times by monte carlo simulation:\n";
    for (auto j = 0; j < Simulations; j++) {
      auto hit = 0;
      auto x = 0.0;
      auto y = 0.0;

      for (auto i = 0; i < Samples; i++) {
        x = dist(eng);
        y = dist(eng);

        if (y <= std::sqrt(1 - std::pow(x, 2)))
          hit += 1;
      }

      std::cout << "Pi: " << 4.0 * hit / Samples << std::endl;
    }
  }

  void execute()
  {
    std::cout << "\nRecipe 2.04: Initializing all bits of internal state of a "
                 "pseudo-random number generator."
              << "\n---------------------------------------------------------------------"
                 "--------------------\n";

    monte_carlo_simulation();
  }
} // namespace recipe_2_04
