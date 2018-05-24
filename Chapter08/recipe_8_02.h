#pragma once

// Exceptions cannot leave the top-level thread function because they cause the program to
// abnormally terminate. But exceptions can be transported between threads within a
// std::exception_ptr wrapper.

// std::current_exception(), std::rethrow_exception(), and std::exception_ptr are all
// available in C++11.

//  We assume that multiple threads can throw exceptions and therefore need a container to
//  hold them all. If there is a single exception from a single thread at a time, then you
//  do not need a shared container and a mutex to synchronize access to it. You can use a
//  single global object of the type std::exception_ptr to hold the exception transported
//  between threads.

#include <exception>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <string>

namespace recipe_8_02 {
  // 1. Use a global container to hold instances of std::exception_ptr:
  std::vector<std::exception_ptr> g_exceptions;
  // 2. Use a global mutex to synchronize access to the shared container:
  std::mutex g_mutex;

  using namespace std::string_literals;

  void func1()
  {
    throw std::runtime_error("exception 1"s);
  }

  void func2()
  {
    throw std::runtime_error("exception 2");
  }

  void thread_func1()
  {
    // 3. Use a try...catch block for the code that is being executed in the top-level
    // thread function:
    try {
      func1();
    } catch (...) {
      std::cout << "Caught runtime error 1.\n";
      // The std::current_exception() is a function that is typically used in a catch
      // clause to capture the current exception and create an instance of
      // std::exception_ptr. This is done to hold a copy or reference (depending on the
      // implementation) to the original exception.

      // The std::exception_ptr objects can be passed to other threads where they can be
      // rethrown and caught in a try...catch block.

      // 3':  Use std::current_exception() to capture the current exception and wrap a
      // copy or its reference into an std::exception_ptr pointer, which is added to the
      // shared container for exceptions:
      std::lock_guard<std::mutex> lock(g_mutex);
      g_exceptions.push_back(std::current_exception());
    }
  }

  void thread_func2()
  {
    try {
      func2();
    } catch (...) {
      std::cout << "Caught runtime error 2.\n";
      std::lock_guard<std::mutex> lock(g_mutex);
      g_exceptions.push_back(std::current_exception());
    }
  }

  void execute()
  {
    std::cout << "\nRecipe 8.02: Handling exceptions from thread function."
              << "\n------------------------------------------------------\n";

    // 4. Clear the container from the main thread before you start the threads:
    g_exceptions.clear();

    std::thread t1(thread_func1);
    std::thread t2(thread_func2);
    t1.join();
    t2.join();

    // 5. In the main thread, after the execution of all the threads has finished, inspect
    // the caught exceptions and handle each of them appropriately:
    for (auto const& e : g_exceptions) {
      try {
        if (e != nullptr)
          // The std::rethrow_exception() is a function that takes std::exception_ptr as
          // an argument and throws the exception object referred to by its argument:
          std::rethrow_exception(e);
      } catch (std::exception const& ex) {
        std::cout << "Catching exceptions from the worker threads: ";
        std::cout << ex.what() << std::endl;
      }
    }
  }
}
