#pragma once

// The library is available in the <chrono> header in the std::chrono namespace and
// defines and implements several components:

// Durations (this recipe)
// Time points
// Clocks

// http://en.cppreference.com/w/cpp/chrono
// https://github.com/HowardHinnant/date

#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

namespace recipe_6_01 {
  void execute()
  {
    std::cout << "Recipe 6.01: Expressing time intervals with chrono::duration.\n"
              << "-------------------------------------------------------------\n\n";

    {
      std::cout << "To work with time intervals, use the following:\n";
      std::cout << "See source code.\n";
      std::chrono::hours half_day(12);
      std::chrono::minutes half_hour(30);
      std::chrono::seconds half_minute(30);
      std::chrono::milliseconds half_second(500);
      std::chrono::microseconds half_milisecond(500);
      std::chrono::nanoseconds half_microsecond(500);
      // std::cout << half_day << " " << half_hour << " " << half_minute << " " << half_second << std::endl;
    }

    {
      std::cout << "\nUse the standard user-defined literal operators from C++14:\n";
      std::cout << "See source code.\n";

      using namespace std::chrono_literals;

      auto half_day = 12h;
      auto half_hour = 30min;
      auto half_minute = 30s;
      auto half_second = 500ms;
      auto half_milisecond = 500us;
      auto half_microsecond = 500ns;
    }

    {
      std::cout << "\nUse direct conversion from a lower precision duration to a higher precision duration:\n";

      std::chrono::hours half_day_in_h(12);
      std::chrono::minutes half_day_in_min(half_day_in_h);

      std::cout << half_day_in_h.count() << "h" << std::endl;
      std::cout << half_day_in_min.count() << "min" << std::endl;
    }

    {
      std::cout << "\nUse std::chrono::duration_cast to convert from a higher precision to a lower precision duration:\n";

      using namespace std::chrono_literals;

      auto total_seconds = 12345s;
      auto hours = std::chrono::duration_cast<std::chrono::hours>(total_seconds);
      auto minutes = std::chrono::duration_cast<std::chrono::minutes>(total_seconds % 1h);
      auto seconds
        = std::chrono::duration_cast<std::chrono::seconds>(total_seconds % 1min);

      std::cout << hours.count() << ':' << minutes.count() << ':' << seconds.count()
                << std::endl; // 3:25:45
    }

    {
      std::cout << "\nUse the conversion functions floor(), round(), and ceil() available in C++17 when rounding is necessary:\n";
      std::cout << "See source code.\n";

      using namespace std::chrono_literals;

      auto total_seconds = 12345s;
      auto m1 = std::chrono::floor<std::chrono::minutes>(total_seconds); // 205 min
      auto m2 = std::chrono::round<std::chrono::minutes>(total_seconds); // 206 min
      auto m3 = std::chrono::ceil<std::chrono::minutes>(total_seconds);  // 206 min
      auto sa = std::chrono::abs(total_seconds);
    }

    {
      std::cout << "\nUse arithmetic operations, compound assignments, and comparison operations to modify and compare time intervals:\n";
      std::cout << "See source code.\n";

      using namespace std::chrono_literals;

      // Note that when two durations of different time units are added or subtracted, the
      // result is a duration of the greatest common divisor of the two time units. That
      // means that if you add a duration representing seconds and a duration representing
      // minutes, the result is a duration representing seconds. The number of ticks can
      // be retrieved with the count() member function.

      auto d1 = 1h + 23min + 45s; // d1 = 5025s
      auto d2 = 3h + 12min + 50s; // d2 = 11570s
      std::cout << d1.count() << " " << d2.count() << std::endl;
      if (d1 < d2) {
        std::cout << "d1 smaller than d2\n";
      }
    }

    {
      std::cout << "\nDefine you own time interval:\n";
      std::cout << "See source code.\n";

      using namespace std::chrono_literals;

      // The default unit is the second, and for expressing other units, such as minutes
      // or milliseconds, we need to use a ratio. We can express time intervals such
      // as 1.2 sixths of a minute (which means 12 seconds), where 1.2 is the number of
      // ticks of the duration and ratio<10> (as in 60/6) is the time unit:
      std::chrono::duration<double, std::ratio<10>> d(1.2); // 12 sec

      assert(std::chrono::duration_cast<std::chrono::seconds>(d).count()
             == (12s).count());
    }
  }
}
