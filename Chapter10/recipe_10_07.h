#pragma once

// Singleton is probably one of the most well-known design patterns. It restricts the
// instantiation of a single object of a class, something that is necessary in some cases,
// although many times the use of a singleton is rather an anti-pattern that can be
// avoided with other design choices. Since a singleton means a single instance of a class
// is available to an entire program, it is likely that such a unique instance might be
// accessible from different threads.

#include <iostream>

namespace recipe_10_07 {
  // To implement a thread-safe singleton, you should do the following:

  // 1. Define the singleton class:
  class Singleton {
  private:
    // 2. Make the default constructor private:
    Singleton() {}

  public:
    // 3. Make the copy constructor and copy assignment operator public and delete:
    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

    // 4. The function that creates and returns the single instance should be static and
    // should return a reference to the class type. It should declare a static object of
    // the class type and return a reference to it.
    // Though most implementations return a pointer, it actually makes more sense to
    // return a reference, as there is no circumstance under which this function would
    // return a null pointer (no object):
    static Singleton& instance()
    {
      // The implementation of the instance() method may look simplistic and not
      // thread-safe at a first glance, especially if you are familiar with the
      // double-checked locking pattern (DCLP). In C++11, this is actually no longer
      // necessary due to a key detail of how objects with static storage durations are
      // initialized.
      static Singleton single;
      return single;
    }
  };

  // -----------------------------------------------------------------------------------------------

  // There might be situations in larger code bases where you need more than one singleton
  // type. In order to avoid writing the same pattern several times, you can implement it
  // in a generic way. For this, we need to employ the curiously recurring template
  // pattern (or CRTP) seen in the previous recipe. The actual singleton is implemented as
  // a class template. The instance() method creates and returns an object of the type
  // template parameter, which will be the derived class:

  template <class T>
  class SingletonBase {
  protected:
    SingletonBase() {}

  public:
    SingletonBase(SingletonBase const&) = delete;
    SingletonBase& operator=(SingletonBase const&) = delete;

    static T& instance()
    {
      static T single;
      return single;
    }
  };

  // The Singleton class from the previous section has become the SingletonBase class
  // template. The default constructor is no longer private but protected because it must
  // be accessible from the derived class. In this example, the class that needs to have a
  // single object instantiated is called Single. Its constructors must be private, but
  // the default constructor must also be available to the base class template; therefore,
  // SingletonBase<Single> is a friend of the Single class.

  // CRTP:
  class Single : public SingletonBase<Single> {
    Single() {}
    friend class SingletonBase<Single>;

  public:
    void demo()
    {
      std::cout << "demo" << std::endl;
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 10.07: Implementing a thread-safe singleton."
              << "\n---------------------------------------------------\n";

    {
      std::cout << "Singleton:\n";

      auto& s = Singleton::instance();
    }

    {
      std::cout << "\nSingletons with CRTP:\n";

      auto& s = Single::instance();
      s.demo();
    }
  }
}
