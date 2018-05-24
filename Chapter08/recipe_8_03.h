#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

namespace recipe_8_03 {
  // A mutex is a synchronization primitive that allows us to protect simultaneous access
  // to shared resources from multiple threads. std::mutex is the most commonly used mutex
  // type. There are also std::timed_mutex, std::recursive_mutex,
  // std::recursive_timed_mutex.

  // The first thread that locks an available mutex takes ownership of it and continues
  // with the execution. All consecutive attempts to lock the mutex from any thread fail,
  // including the thread that already owns the mutex, and the lock() method blocks the
  // thread until the mutex is released with a call to unlock().

  // Use the following pattern for synchronizing access with a single shared resource:
  // 1. Define a mutex in the appropriate context (class or global scope):
  std::mutex g_mutex;

  void thread_func_1()
  {
    using namespace std::chrono_literals;

    // This method of using the mutex is, however, prone to error. This is because each
    // call to lock() must be paired with a call to unlock() on all execution paths, that
    // is both normal return paths and exception return paths. In order to safely acquire
    // and release a mutex, regardless of the way the execution of a function goes, the
    // C++ standard defines several locking classes: std::lock_guard (represents a mutex
    // wrapper implemented in an RAII manner. It attempts to acquire the mutex at the time
    // of its construction and release it upon destruction), std::unique_lock,
    // std::shared_lock, std::scoped_lock.

    // 2. Acquire a lock on the mutex before accessing the shared resource in each thread:
    std::lock_guard<std::mutex> lock(g_mutex);
    // Use the shared resource such as std::cout:
    std::cout << "running thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "done in thread " << std::this_thread::get_id() << std::endl;
  }

  void thread_func_2()
  {
    using namespace std::chrono_literals;

    {
      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "running thread " << std::this_thread::get_id() << std::endl;
    }

    std::this_thread::yield();
    std::this_thread::sleep_for(1s);

    {
      std::lock_guard<std::mutex> lock(g_mutex);
      std::cout << "done in thread " << std::this_thread::get_id() << std::endl;
    }
  }

  void thread_func_3()
  {
    using namespace std::chrono_literals;

    g_mutex.lock();
    std::cout << "running thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(2s);
    std::cout << "done in thread " << std::this_thread::get_id() << std::endl;
    g_mutex.unlock();
  }

  //  Typical implementation of lock_guard:
  template <class M>
  class lock_guard {
  public:
    typedef M mutex_type;

    explicit lock_guard(M& Mtx)
      : mtx(Mtx)
    {
      mtx.lock();
    }

    lock_guard(M& Mtx, std::adopt_lock_t)
      : mtx(Mtx)
    {
    }

    ~lock_guard() noexcept
    {
      mtx.unlock();
    }

    lock_guard(const lock_guard&) = delete;
    lock_guard& operator=(const lock_guard&) = delete;

  private:
    M& mtx;
  };

  template <typename T>
  struct container {
    // Use the following pattern for synchronizing access to multiple shared resources
    // at the same time to avoid deadlocks:

    // 1. Define a mutex for each shared resource in the appropriate context (global or
    // class scope):
    std::mutex mutex;
    std::vector<T> data;
  };

  template <typename T>
  void move_between(container<T>& c1, container<T>& c2, T const value)
  {
    // 2. Lock the mutexes at the same time using a deadlock avoidance algorithm with
    // std::lock():
    std::lock(c1.mutex, c2.mutex);

    // 3. After locking them, adopt the ownership of each mutex into an std::lock_guard
    // class to ensure they are safely released at the end of the function (or scope):
    std::lock_guard<std::mutex> l1(c1.mutex, std::adopt_lock);
    std::lock_guard<std::mutex> l2(c2.mutex, std::adopt_lock);

    c1.data.erase(std::remove(c1.data.begin(), c1.data.end(), value), c1.data.end());
    c2.data.push_back(value);
  }

  template <typename T>
  void print_container(container<T> const& c)
  {
    for (auto const& e : c.data)
      std::cout << e << ' ';
    std::cout << std::endl;
  }

  void execute()
  {
    std::cout << "\nRecipe 8.03: Synchronizing access to shared data with mutexes and locks."
              << "\n------------------------------------------------------------------------\n";

    {
      std::cout << "Running several threads locking std::cout:\n";

      std::vector<std::thread> threads;
      for (int i = 0; i < 3; ++i)
        threads.emplace_back(thread_func_1);

      for (auto& t : threads)
        t.join();
    }

    {
      std::cout << "\nRunning several threads in parallel with std::this_thread::yield:\n";

      std::vector<std::thread> threads;
      for (int i = 0; i < 3; ++i)
        threads.emplace_back(thread_func_2);

      for (auto& t : threads)
        t.join();
    }

    {
      std::cout << "\nTwo threads accessing same vectors:\n";

      container<int> c1;
      c1.data.push_back(1);
      c1.data.push_back(2);
      c1.data.push_back(3);

      container<int> c2;
      c2.data.push_back(4);
      c2.data.push_back(5);
      c2.data.push_back(6);

      std::cout << "Before:\n";
      print_container(c1);
      print_container(c2);

      std::cout << "Now two threads are accessing both containers.\n";
      // Removes 3 from c1, adds 3 to c2
      std::thread t1(move_between<int>, std::ref(c1), std::ref(c2), 3);
      // Removes 6 from c2, adds 6 to c1
      std::thread t2(move_between<int>, std::ref(c2), std::ref(c1), 6);

      t1.join();
      t2.join();

      std::cout << "After:\n";
      print_container(c1);
      print_container(c2);
    }
  }
}
