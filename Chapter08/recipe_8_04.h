#pragma once

// std::recursive_mutex and std::recursive_timed_mutex are two implementations that allow
// you to use multiple locking in the same thread. A typical use of a recursive mutex is
// to protect access to a shared resource from a recursive function. Recursive mutexes
// have a greater overhead than non-recursive mutexes and, when possible, they should be
// avoided.

// This recipe presents a use case for transforming a thread-safe type using a recursive
// mutex into a thread-safe type using a non-recursive mutex.

// The implementation of foo_rec was probably intended to avoid duplication of code, yet
// this particular approach is rather a design error that can be improved. Rather than
// reusing public thread-safe functions, we can provide private non-thread-safe functions
// that could then be called from the public interface.

#include <mutex>
#include <iostream>

namespace recipe_8_04 {
  class foo_rec {
    // An std::recursive_mutex class may be locked multiple times from a thread, either
    // with a call to lock() or try_lock(). When a thread locks an available recursive
    // mutex, it acquires its ownership; as a result of this, consecutive attempts to lock
    // the mutex from the same thread do not block the execution of the thread, creating a
    // deadlock. The recursive mutex is, however, released only when an equal number of
    // calls to unlock() are made!!!
    std::recursive_mutex m;

    // The foo_rec class uses a recursive mutex to protect access to shared data; in this
    // case, it is an integer member variable that is accessed from two thread-safe public
    // functions: update(), update_and_return().
    int data;

  public:
    foo_rec(int const d = 0)
      : data(d)
    {
    }

    void update(int const d)
    {
      std::lock_guard<std::recursive_mutex> lock(m);
      data = d;
    }

    int update_with_return(int const d)
    {
      std::lock_guard<std::recursive_mutex> lock(m);
      auto temp = data;
      update(d);
      return temp;
    }
  };

  class foo {
  public:
    foo(int const d = 0)
      : data(d)
    {
    }

    void update(int const d)
    {
      std::lock_guard<std::mutex> lock(m);
      internal_update(d);
    }

    int update_with_return(int const d)
    {
      std::lock_guard<std::mutex> lock(m);
      auto temp = data;
      internal_update(d);
      return temp;
    }

  private:
    std::mutex m;
    int data;

    void internal_update(int const d)
    {
      data = d;
    }
  };

  void execute() {
    std::cout << "\nRecipe 8.04: Avoiding using recursive mutexes."
              << "\n----------------------------------------------\n";

    std::cout << "See source code.\n";
  }
}
