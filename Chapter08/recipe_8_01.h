#pragma once

// Thread library is the goto

// Plain Threads are the GOTO of todays computing:
// https://www.youtube.com/watch?v=4OCUEgSNIAY

// The C++ Standard Library for Parallelism and Concurrency:
// https://github.com/STEllAR-GROUP/hpx/

// Threads could be software; they can run on single processing units, usually by time
// slicing. They could be hardware as well; they can run simultaneously, that is, in
// parallel, on systems with multiprocessors or multicores. Many software threads can run
// concurrently on a hardware thread too. The C++ library provides support for working
// with software threads.

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
// A thread of execution is represented by the thread class available in the std namespace
// in the <thread> header. Additional thread utilities are available in the same header
// but in the std::this_thread namespace.
#include <thread>

namespace recipe_8_01 {
  // The thread function, in this case, cannot return a value. It is not illegal for the
  // function to actually have a return type other than void, but it ignores any value
  // that is directly returned by the function. If it has to return a value, it can do so
  // using a shared variable or a function argument. In a future recipe, we will see how a
  // thread function returns a value to another thread using a promise.
  void func1()
  {
    std::cout << "Thread func without params." << std::endl;
  }

  // If the function terminates with an exception, the exception cannot be caught with a
  // try...catch statement in the context where a thread was started and the program
  // terminated abnormally with a call to std::terminate(). All exceptions must be caught
  // within the executing thread, but they can be transported across threads via an
  // std::exception_ptr object. We'll discuss this topic in the next recipe.
  void func2(int const i, double const d, std::string const s)
  {
    std::cout << i << ", " << d << ", " << s << std::endl;
  }

  void func3(int& i)
  {
    i *= 2;
  }

  inline void print_time()
  {
    auto now = std::chrono::system_clock::now();
    auto stime = std::chrono::system_clock::to_time_t(now);
    auto ltime = std::localtime(&stime);

    std::cout << std::put_time(ltime, "%c") << std::endl;
  }

  void func4()
  {
    using namespace std::chrono;

    print_time();

    // To stop the execution of a thread for a specified duration, use the
    // std::this_thread::sleep_for() function:
    std::this_thread::sleep_for(1ms);

    print_time();
  }

  void func5()
  {
    using namespace std::chrono;

    print_time();

    // To stop the execution of a thread until a specified moment in time, use the
    // std::this_thread::sleep_until() function:
    std::this_thread::sleep_until(std::chrono::system_clock::now() + 1ms);

    print_time();
  }

  void func6(std::chrono::milliseconds timeout)
  {
    auto now = std::chrono::system_clock::now();
    auto then = now + timeout;

    do {
      // To suspend the execution of the current thread and provide an opportunity to
      // another thread to perform the execution, use std::this_thread::yield():
      std::this_thread::yield();
    } while (std::chrono::system_clock::now() < then);
  }

  void execute()
  {
    std::cout << "Recipe 8.01: Working with threads.\n"
              << "----------------------------------\n";

    {
      std::cout << "Start thread with function with no arguments:\n";

      // To create an std::thread object without starting the execution of a new thread,
      // use its default constructor:
      // std::thread t;

      // Each thread has an identifier that can be retrieved--for the current thread, call
      // the std::this_thread::get_id() function; for another thread of execution
      // represented by a thread object, call its get_id() method.

      // Start the execution of a function on another thread by constructing an
      // std::thread object and passing the function as an argument:
      std::thread t(func1);

      // Joining a thread implies blocking the execution of the current thread until the
      // joined thread ends its execution.

      // The joinable() method indicates whether a thread can be joined or not.

      // To wait for a thread to finish the execution, use the join() method on the thread
      // object:
      t.join();

      // Detaching a thread means decoupling the thread object from the thread of
      // execution it represents, allowing both the current thread and the detached thread
      // to be executed at the same time.

      // To allow a thread to continue its execution independently of the current thread
      // object, use the detach() method:
      // t.detach();
    }

    {
      std::cout << "\nThe same with a lambda:\n";

      std::thread t([]() { std::cout << "Thread func without params." << std::endl; });
      t.join();
    }

    {
      std::cout << "\nStart thread with function with arguments:\n";

      // Start the execution of a function with arguments on another thread by
      // constructing an std::thread object and passing the function as an argument to the
      // constructor, followed by its arguments:
      std::thread t(func2, 42, 42.0, "42");
      t.join();
    }

    {
      std::cout << "\nThe same with a lambda:\n";

      std::thread t(
        [](int const i, double const d, std::string const s) {
          std::cout << i << ", " << d << ", " << s << std::endl;
        },
        42, 42.0, "42");
      t.join();
    }

    {
      std::cout << "\nPass constant arguments to a function with std::ref():\n";

      int n = 42;
      // To pass arguments by reference to a function, thread wrap them in either std::ref
      // or std::cref (if the reference is constant):
      std::thread t(func3, std::ref(n));
      t.join();

      std::cout << n << std::endl;
    }

    {
      std::cout << "\nThe same with a lambda:\n";

      int n = 42;
      std::thread t([](int& i) { i *= 2; }, std::ref(n));
      t.join();

      std::cout << n << std::endl;
    }

    {
      std::cout << "\nStop execution of thread with std::this_thread::sleep_for():\n";

      std::thread t(func4);
      t.join();
    }

    {
      std::cout << "\nStop execution of thread till specific time is reached with "
                   "std::this_thread::sleep_until():\n";

      std::thread t(func5);
      t.join();
    }

    {
      std::cout << "\nTo suspend current thread and give other threads a chance use "
                   "std::this_thread::yield():\n";

      std::thread t(func6, std::chrono::milliseconds(1));
      t.join();

      print_time();
    }
  }
}
