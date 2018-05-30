#pragma once

// When you declare a parameter or variable as constant, you can either put the const
// keyword before the type (const T c) or after the type (T const c). These two are
// equivalent, but regardless of which of the two styles you use, reading of the
// declaration must be done from the right-hand side. const T c is read as c is a T that
// is constant and T const c as c is a constant T.

// Placing the const keyword after the type is more natural because it is consistent with
// the reading direction, from right to left.

/*
Expression							Description
T* p										P is a non-constant pointer to a non-constant T
const T* p							P is a non-constant pointer to a T that is constant
T const * p							P is a non-constant pointer to a constant T (same as above)
const T * const p				P is a constant pointer to a T that is constant
T const * const p				P is a constant pointer to a constant T (same as above)
T** p										P is a non-constant pointer to a non-constant pointer to a non-constant T
const T** p							P is a non-constant pointer to a non-constant pointer to a constant T
T const ** p						Same as T const ** p
const T* const * p			P is a non-constant pointer to a constant pointer, which is a constant T
T const * const * p			Same as const T * const * p
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace recipe_9_03 {
  struct session {
  };

  // Parameters to functions that are not supposed to be modified within the function
  // should be declared constant:
  session connect(std::string const& uri, int const timeout = 2000)
  {
    /* do something */
    return session{ /* ... */ };
  }

  class contact {
  };

  class addressbook {
    std::vector<contact> contacts;

  public:
    //  For non-constant objects, the method should allow the client to modify the data it
    //  provides access to, but for constant objects, it should not. Therefore, the
    //  non-constant subscript operator returns a reference to a non-constant object, and
    //  the constant subscript operator returns a reference to a constant object: (It
    //  should be noted that, if a member function is constant, even if an object is
    //  constant, data returned by this member function may not be constant)
    contact& operator[](size_t const index)
    {
      throw std::runtime_error("not implemented");
    }

    contact const& operator[](size_t const index) const
    {
      throw std::runtime_error("not implemented");
    }
  };

  class user_settings {
    bool show_online;

  public:
    // Class member functions that do not modify the object state as seen from the
    // outside should be declared constant:
    bool can_show_online() const
    {
      return show_online;
    }

    // Class data members that do not change should be declared constant:
    int const min_update_interval = 15;

    /* other members */
  };

  user_settings get_user_settings()
  {
    return user_settings{};
  }

  void update()
  {
    // Function locals whose value do not change throughout their lifetime should be
    // declared constant:
    user_settings const us = get_user_settings();

    if (us.can_show_online()) { /* do something */
    }

    /* do more */
  }

  // Declaring a member function constant does not mean that the function can only be
  // called on constant objects; it could also mean that the function does not modify the
  // state of the object as seen from the outside. This is a key aspect, but it is usually
  // misunderstood. A class has an internal state that it can expose to its clients
  // through its public interface. However, not all the internal states might be exposed,
  // and what is visible from the public interface might not have a direct representation
  // in the internal state.
  class computation {
    double compute_value(double const input) const
    {
      /* long running operation */
      return input;
    }

    // To be able to modify the cache from the constant function, it is declared mutable:
    mutable std::map<double, double> cache;

  public:
    double compute(double const input) const
    {
      auto it = cache.find(input);
      if (it != cache.end())
        return it->second;

      auto result = compute_value(input);
      cache[input] = result;

      return result;
    }
  };

  // Thread-safe container, access to shared internal data is protected with a mutex.
  template <typename T>
  class container {
    std::vector<T> data;
    // In order to lock and unlock the mutex (both mutable operations) the mutex must be
    // declared mutable:
    mutable std::mutex mutex;

  public:
    void add(T const& value)
    {
      std::lock_guard<std::mutex> lock(mutex);
      data.push_back(value);
    }

    bool contains(T const& value) const
    {
      std::lock_guard<std::mutex> lock(mutex);
      return std::find(std::begin(data), std::end(data), value) != std::end(data);
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 9.03: Ensuring constant correctness for a program."
              << "\n---------------------------------------------------------\n";

    std::cout << "Please see source code.\n";
    {
      update();
    }

    {
      computation const c;
      c.compute(42);
    }

    {
      container<int> c;
      c.add(42);
      auto exists = c.contains(42);
    }

    /*
  int const c = 42;
  int* x;
  int const ** p = &x; // this is an error
  *p = &c;
  *x = 0;              // oops, this modifies c
  */
  }
}
