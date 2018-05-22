#pragma once

//  In this recipe, we will see how to use the chrono library and time points to measure
//  the execution of a function.

// A clock is a component that defines two things:

// A beginning of time called EPOCH; there is no constraint of what the epoch is, but
// typical implementations use January 1, 1970.

// A TICK RATE that defines the increment between two time points (such as a millisecond
// or nanosecond).

// The standard defines three types of clocks:

// system_clock: This uses the real-time clock of the current system to represent time
// points.

// high_resolution_clock: This represents a clock that uses the shortest possible tick
// period on the current system.

// steady_clock: This indicates a clock that is never adjusted. This means that, unlike
// the other clocks, as the time advances, the difference between two time points is
// always positive. You should rely on a steady clock to measure the function execution
// time.

#include <chrono>
#include <functional>
#include <iostream>

namespace recipe_6_02 {
  void func(int const count = 100000000)
  {
    for (int i = 0; i < count; ++i) {
    }
  }

  // Reusable component to measure execution time.
  template <typename Time = std::chrono::microseconds,
            typename Clock = std::chrono::high_resolution_clock>
  struct perf_timer {
    template <typename F, typename... Args>
    static Time duration(F&& f, Args... args)
    {
      auto start = Clock::now();

      std::__invoke(std::forward<F>(f), std::forward<Args>(args)...);

      auto end = Clock::now();

      return std::chrono::duration_cast<Time>(end - start);
    }
  };

  template <typename T>
  void print_clock()
  {
    std::cout << "precision: " << (1000000.0 * double(T::period::num)) / (T::period::den)
              << std::endl;
    std::cout << "steady:    " << T::is_steady << std::endl;
  }

  void execute()
  {
    std::cout << "\nRecipe 6.02: Measuring function execution time with a standard clock."
              << "\n---------------------------------------------------------------------\n";

    {
      std::cout << "\nMeasuring the execution of a function:\n";
      auto start = std::chrono::high_resolution_clock::now();

      func();

      auto diff = std::chrono::high_resolution_clock::now() - start;

      std::cout << std::chrono::duration<double, std::milli>(diff).count() << "ms"
                << std::endl;
      std::cout << std::chrono::duration<double, std::nano>(diff).count() << "ns"
                << std::endl;
    }

    {
      std::cout << "\nUsing a reusable component to measure execution time:\n";

      auto t = perf_timer<>::duration(func, 100000000);

      std::cout << std::chrono::duration<double, std::milli>(t).count() << "ms"
                << std::endl;
      std::cout << std::chrono::duration<double, std::nano>(t).count() << "ns"
                << std::endl;
    }

    {
      std::cout << "\nMeasuring the execution time in µ seconds:\n";
      auto t1 = perf_timer<std::chrono::nanoseconds>::duration(func, 100000000);
      auto t2 = perf_timer<std::chrono::microseconds>::duration(func, 100000000);
      auto t3 = perf_timer<std::chrono::milliseconds>::duration(func, 100000000);

      auto total = t1 + t2 + t3;

      std::cout << std::chrono::duration<double, std::micro>(total).count() << "µs"
                << std::endl;
    }

    {
      std::cout << "\nShow precision of the C++ standard clocks: system clock, high "
                   "resolution clock, steady clock.\n";
      // On my system the high resolution clock is not steady and shouldn't be used for
      // measuring the execution time. In my case only the steady clock should be used.
      print_clock<std::chrono::system_clock>();
      print_clock<std::chrono::high_resolution_clock>();
      print_clock<std::chrono::steady_clock>();
    }
  }
}
