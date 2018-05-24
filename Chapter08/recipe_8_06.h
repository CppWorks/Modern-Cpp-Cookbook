#pragma once

// In recipe 8.01 we learned that thread functions cannot return values, and threads
// should use other means, such as shared data, to do so. However, synchronization is
// required. An alternative to communicating a return value or an exception with either
// the main or another thread is using std::promise.

// The promise-future pair is basically a communication channel that enables a thread to
// communicate a value or exception with another thread through a shared state. The
// promise is an asynchronous provider of the result and has an associated future that
// represents an asynchronous return object.

#include <future>
#include <iostream>
#include <mutex>
#include <thread>

namespace recipe_8_06 {
  std::mutex g_mutex;

  // 1. Make a promise available to the thread function through a parameter:
  void produce_value(std::promise<int>& p)
  {
    // simulate long running operation
    {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1s);
    }

    // 2. Call set_value() on the premise or set_exception() to set the result to indicate
    // an exception:
    // If an exception is set to the promise value, calling the get() method on the future
    // will throw this exception.
    p.set_value(42);
  }

  // 3. Make the future associated with the promise available to the other thread function
  // through a parameter:
  void consume_value(std::future<int>& f)
  {
    // 4. Call get() on the future object to get the result set to the promise:
    //  This blocks the calling thread until the value from the shared state is being made
    //  available.
    auto value = f.get();

    std::lock_guard<std::mutex> lock(g_mutex);
    std::cout << value << std::endl;
  }

  void execute()
  {
    std::cout
      << "\nRecipe 8.06: Using promises and futures to return values from threads."
      << "\n----------------------------------------------------------------------\n";

    // Establishing a promise-future channel.
    std::promise<int> p;
    std::thread t1(produce_value, std::ref(p));

    // 5. In the calling thread, use get_future() on the promise to get the future
    // associated with the promise:
    std::future<int> f = p.get_future();
    std::thread t2(consume_value, std::ref(f));

    t1.join();
    t2.join();
  }
}
