#pragma once

// Book: Anthony Williams in C++ concurrency in action (2012):

// https://www.manning.com/books/c-plus-plus-concurrency-in-action-second-edition

// Mutexes are synchronization primitives that can be used to protect access to shared
// data. However, the standard library provides a synchronization primitive called a
// condition variable that enables a thread to signal to others that a certain condition
// has occurred. The thread or the threads that are waiting on the condition variable are
// blocked until the condition variable is signaled or until a timeout or a spurious
// wakeup occurs.

#include <array>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>

namespace recipe_8_05 {
  using namespace std::chrono_literals;

  // 1. Define a condition variable
  std::condition_variable g_queuecheck;
  // 2. Define a mutex for std::cout.
  std::mutex g_lockprint;
  // 2'. Define a mutex for shared data (queue).
  std::mutex g_lockqueue;
  // 3. Define shared data.
  std::queue<int> g_buffer;

  bool g_done = false;

  void producer(int const id, std::mt19937& generator,
                std::uniform_int_distribution<int>& dsleep,
                std::uniform_int_distribution<int>& dcode)
  {
    for (int i = 0; i < 3; ++i) {
      // Simulate work.
      std::this_thread::sleep_for(std::chrono::seconds(dsleep(generator)));

      // Generate data.
      int value = id * 100 + dcode(generator);

      {
        std::unique_lock<std::mutex> locker(g_lockprint);
        std::cout << "[produced]: " << value << std::endl;
      }

      // Notify consumers.
      {
        // 4. lock the mutex before modifying the data
        std::unique_lock<std::mutex> locker(g_lockqueue);

        g_buffer.push(value);

        // 5.  In the producing thread, signal the condition variable with a call to
        // notify_one() or notify_all():
        g_queuecheck.notify_one();
      }
    }
  }

  void consumer()
  {
    while (!g_done) {
      // 6. In the consuming thread, acquire a unique lock on the mutex and use it to wait
      // on the condition variable: (wait(), wait_for(), or wait_until())
      std::unique_lock<std::mutex> locker(g_lockqueue);
      // All the waiting methods atomically release the mutex and block the thread until
      // the condition variable is signaled. At this point, the thread is unblocked and
      // the mutex must be atomically acquired again.

      // Checking that the buffer is not empty when a wakeup occurs (to avoid spurious
      // wakeups). wait_for() uses a timeout of 1 second and returns after the timeout has
      // occurred, even if the condition is signaled.
      g_queuecheck.wait_for(locker, std::chrono::seconds(1), [&]() { return !g_buffer.empty(); });

      // Condition variables cannot be made completely predictable on multiprocessor
      // systems. Therefore, spurious wakeups may occur and a thread is unlocked even if
      // nobody signals the condition variable. So, it is necessary to check whether the
      // condition is true after the thread has been unblocked. However, spurious wakeups
      // may occur multiple times and, therefore, it is necessary to check the condition
      // variable in a loop. (g_buffer.empty() in this case.)

      // If there are values in the queue process them.
      while (!g_buffer.empty()) {
        std::unique_lock<std::mutex> locker(g_lockprint);
        // 7. In the consuming thread, use the shared data after the condition is
        // notified:
        std::cout << "[consumed]: " << g_buffer.front() << std::endl;
        g_buffer.pop();
      }
    }
  }

  void execute()
  {
    std::cout << "\nRecipe 8.05: Sending notifications between threads."
              << "\n---------------------------------------------------\n";

    auto seed_data = std::array<int, std::mt19937::state_size>{};
    std::random_device rd{};

    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    auto generator = std::mt19937{ seq };
    auto dsleep = std::uniform_int_distribution<>{ 1, 3 };
    auto dcode = std::uniform_int_distribution<>{ 1, 99 };

    std::cout << "start producing and consuming..." << std::endl;

    // One consumer thread.
    std::thread consumerthread(consumer);

    // Multiple producer threads.
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
      threads.emplace_back(producer, i, std::ref(generator), std::ref(dsleep),
                           std::ref(dcode));
    }

    // Wait for the workers to finish.
    for (auto& t : threads)
      t.join();

    // Notify the logger to finish and wait for it.
    g_done = true;
    consumerthread.join();

    std::cout << "done producing and consuming" << std::endl;
  }
}
