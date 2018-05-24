#pragma once

// An alternative to threads is tasks, which are units of work that run in a particular
// thread. The C++ standard does not provide a complete task library, but it enables
// developers to execute functions asynchronously on different threads and communicate
// results back through a promise-future channel. Do this using std::async() and
// std::future.

#include <future>
#include <iostream>
#include <mutex>
#include <thread>

namespace recipe_8_07 {
  std::mutex g_mutex;

  void do_something()
  {
    // Simulate long running operation.
    {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(2s);
    }

    std::lock_guard<std::mutex> lock(g_mutex);
    std::cout << "Operation 1 done!" << std::endl;
  }

  void do_something_else()
  {
    // Simulate long running operation
    {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1s);
    }

    std::lock_guard<std::mutex> lock(g_mutex);
    std::cout << "Operation 2 done!" << std::endl;
  }

  int compute_something()
  {
    // simulate long running operation
    {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(2s);
    }

    return 42;
  }

  int compute_something_else()
  {
    // simulate long running operation
    {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(1s);
    }

    return 24;
  }

  void execute()
  {
    std::cout << "\nRecipe 8.07: Executing functions asynchronously."
              << "\n------------------------------------------------\n";

    {
      std::cout << "async() without return value:\n";

      // 1. Use std::async() to start a new thread to execute the specified function.
      // Create an asynchronous provider and return a future associated with it. Use the
      // std::launch::async policy for the first argument to the function in order to make
      // sure the function will run asynchronously:
      auto f = std::async(std::launch::async, do_something);

      // 2. Continue with the execution of the current thread:
      do_something_else();

      // 3. Call the wait() method on the future object returned by std::async() when you
      // need to make sure the asynchronous operation is completed:
      f.wait();

      std::cout << "all done!" << std::endl;
    }

    {
      std::cout << "\nasync() with return value:\n";

      // Two launch policies:

      // std::launch::async: a new thread is launched to execute the task asynchronously.
      // std::launch::deferred: the task is executed on the calling thread the first time
      // its result is requested.

      // Tip: Always use the overload that requires a launch policy, and always use
      // std::launch::async.
      auto f = std::async(std::launch::async, compute_something);
      auto value = compute_something_else();

      // 3. Call the get() method on the future object returned by std::async() when you
      // need to get the result from the function executed asynchronously:
      value += f.get();

      std::cout << value << std::endl;
    }

    {
      std::cout << "\nPolling routine using wait_for():\n";

      // The future class has two more waiting methods: wait_for() specifies a duration
      // after which the call ends and returns even if the shared state is not yet
      // available through the future; wait_until() specifies a time point after which the
      // call returns even if the shared state is not yet available.

      auto f = std::async(std::launch::async, do_something);
      while(true)
        {
          using namespace std::chrono_literals;
          auto status = f.wait_for(300ms);
          if(status == std::future_status::ready)
            break;
          std::cout << "waiting..." << std::endl;
        }
      std::cout << "Done!" << std::endl;
    }
  }
}
