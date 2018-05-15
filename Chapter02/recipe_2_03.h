#pragma once

#include <algorithm>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
// 1. Include the header <random>:
#include <random>

//  Modern C++ provides support for generating pseudo-random numbers through a
//  pseudo-random number library containing number generators and distributions.

// The pseudo-random number library contains two types of components:
// 1. Engines, which are generators of random numbers; these could produce either
// pseudo-random numbers with a uniform distribution or, if available, actual random
// numbers.
// 2. Distributions that convert the output of an engine into a statistical distribution.

// All engines (except for random_device) produce integer numbers in a uniform
// distribution, and all engines implement the following methods:
// 1. min(): This is a static method that returns the minimum value that can be produced
// by the generator.

// 2. max(): This is a static method that returns the maximum value that can be produced
// by the generator.

// 3. seed(): This initializes the algorithm with a start value (except for random_device,
// which cannot be seeded).

// 4. operator(): This generates a new number uniformly distributed between min() and
// max().

// 5. discard(): This generates and discards a given number of pseudo-random numbers.

// The following engines are available:
// 1. linear_congruential_engine
// 2. mersenne_twister_engine
// 3. subtract_with_carry_engine
// 4. discard_block_engine
// 5. independent_bits_engine
// 6. shuffle_order_engine

// All these generators produce integers in a uniform distribution. This is, however, only
// one of the many possible statistical distributions that random numbers are needed in
// most applications. To be able to produce numbers in other distributions, the library
// provides several classes that are called distributions and are converting the output of
// an engine according to the statistical distribution it implements. The following
// distributions are available:
// 1. Uniform
// 2. Bernoulli
// 3. Poisson
// 4. Normal
// 5. Sampling

namespace recipe_2_03 {
  void generate_and_print(std::function<int(void)> gen, int const iterations = 10000)
  {
    // map to store the numbers and  their repetition
    auto data = std::map<int, int>{};

    // generate random numbers
    for (auto n = 0; n < iterations; ++n)
      // 5. Generate the pseudo-random numbers
      ++data[gen()];

    // find the element with the most repetitions
    auto max
      = std::max_element(std::begin(data), std::end(data),
                         [](auto kvp1, auto kvp2) { return kvp1.second < kvp2.second; });

    // print the bars
    for (auto i = max->second / 200; i > 0; --i) {
      for (auto kvp : data) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(3)
                  << (kvp.second / 200 >= i ? (char)219 : ' ');
      }

      std::cout << std::endl;
    }

    // print the numbers
    for (auto kvp : data) {
      std::cout << std::fixed << std::setprecision(1) << std::setw(3) << kvp.first;
    }

    std::cout << std::endl;
  }

  void execute()
  {
    std::cout << "\nRecipe 2.03: Generating pseudo-random numbers."
              << "\n----------------------------------------------\n";

    {
      // The Mersenne twister is the slowest engine and the one that has the largest
      // internal state, but when initialized appropriately can produce the longest
      // non-repeating sequence of numbers. In the following examples, we will use
      // std::mt19937, a 32-bit Mersenne twister with 19937 bits of internal state

      // The engine is not seeded. As a result, it always produces the same sequence of
      // numbers.

      auto mtgen = std::mt19937{};

      std::cout << "Generating random numbers (always the same):\n";
      ;
      for (auto i = 0; i < 10; ++i) {
        std::cout << mtgen() << std::endl;
      }
      std::cout << "\n----------------------------------------------\n";
    }

    {
      std::cout << "Seeding the engine with current time (prone to attacks):\n";
      auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
      auto mtgen = std::mt19937{ static_cast<unsigned int>(seed) };

      for (auto i = 0; i < 10; ++i) {
        std::cout << mtgen() << std::endl;
      }
      std::cout << "\n----------------------------------------------\n";
    }

    {
      // The std::random_device class is an engine that is supposed to return true random
      // numbers, though implementations could actually be based on a pseudo-random
      // generator
      std::cout << "Seeding the engine with a random number:\n";
      std::random_device rd;
      auto mtgen = std::mt19937{ rd() };

      for (auto i = 0; i < 10; ++i) {
        std::cout << mtgen() << std::endl;
      }
      std::cout << "\n----------------------------------------------\n";
    }

    // Numbers produced by all engines follow a uniform distribution. To convert the
    // result to another statistical distribution, we have to use a distribution class.

    // Uniform distribution
    {
      // 2. Use an std::random_device generator for seeding a pseudo-random engine.
      std::random_device rd{};
      // 3. Use one of the available engines for generating numbers and initialize it with
      //    a random seed.
      auto mtgen = std::mt19937{ rd() };
      // 4. Use one of the available distributions for converting the output of the engine
      //    to one of the desired statistical distributions
      auto ud = std::uniform_int_distribution<>{ 1, 6 };

      std::cout << "Uniform distribution:\n";
      generate_and_print([&mtgen, &ud]() { return ud(mtgen); });
      std::cout << "\n----------------------------------------------\n";
    }

    // Normal distribution
    {
      std::random_device rd{};
      auto mtgen = std::mt19937{ rd() };
      // Normal distribution with the mean 5 and the standard deviation 2:
      auto nd = std::normal_distribution<>{ 5, 2 };

      std::cout << "Normal distribution:\n";
      // This distribution produces real numbers; therefore, in order to use the previous
      // generate_and_print() function, the numbers must be rounded to integers.
      generate_and_print(
        [&mtgen, &nd]() { return static_cast<int>(std::round(nd(mtgen))); });
      std::cout << "\n----------------------------------------------\n";
    }
  }
}
