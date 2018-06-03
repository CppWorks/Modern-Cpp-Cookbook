#pragma once

// The attorney-client idiom provides a simple mechanism to restrict friends access to
// only designated private parts of a class.

#include <iostream>

namespace recipe_10_05 {
  namespace oldversion {
    class Client {
      int data_1;
      int data_2;

      void action1() {}
      void action2() {}

      // Friend is supposed to access only parts of the private details, for instance, data1
      // and action1(), but has access to everything:
      friend class Friend;

    public:
      // public interface
    };

    class Friend {
    public:
      void access_client_data(Client& c)
      {
        c.action1();
        c.action2(); // Should not be allowed
        auto d1 = c.data_1;
        auto d2 = c.data_2; // Should not be allowed
      }
    };
  }

  // Take the following steps to restrict a friend's access to the private parts of a
  // class:

  class Client {
    int data_1;
    int data_2;

    void action1() {}
    void action2() {}

    // 1. In the client class that provides access to its private parts to a friend,
    // declare the friendships to an intermediate class, called the Attorney class:
    friend class Attorney;

  public:
    // public interface
  };

  // 2. Create a class that contains only private (inline) functions that access the
  // private parts of the client. This intermediate class allows the actual friend to
  // access its private parts:
  class Attorney {

    // Instead of providing friendship directly to those using its internal state, the
    // client class offers friendship to an attorney, which in turn provides access to a
    // restricted set of private data or functions of the client. It does so by defining
    // private static functions. Usually, these are also inline functions, which avoids
    // any runtime overhead due to the level of indirection the attorney class introduces.

    static inline void run_action1(Client& c)
    {
      c.action1();
    }

    static inline int get_data1(Client& c)
    {
      return c.data_1;
    }

    // A friend of a friend is a friend (but with limitations):
    friend class Friend;
  };

  class Friend {
  public:
    void access_client_data(Client& c)
    {
      // 3. In the Friend class, access the private parts of only the Client class
      // indirectly through the Attorney class:
      Attorney::run_action1(c);
      auto d1 = Attorney::get_data1(c);
    }
  };

  // ------------------------------------------------------------------------------------------

  // FRIENDSHIP IS NOT INHERITABLE, which means that a class or function that is friend to
  // a class B is not friend with a class D that is derived from B. However, virtual
  // functions overridden in D are still accessible polymorphically through a pointer or
  // reference to B from a friend class.

  class B {
    virtual void execute()
    {
      std::cout << "base" << std::endl;
    }

    friend class BAttorney;
  };

  class D : public B {
    virtual void execute() override
    {
      std::cout << "derived" << std::endl;
    }
  };

  class BAttorney {
    static inline void execute(B& b)
    {
      b.execute();
    }

    friend class F;
  };

  class F {
  public:
    void run()
    {
      B b;
      BAttorney::execute(b); // prints 'base'

      D d;
      BAttorney::execute(d); // prints 'derived'
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 10.05: Handling friendship with the attorney-client idiom."
              << "\n-----------------------------------------------------------------\n";

    {
      std::cout << "A friend has access to all methods and data.\n";

      oldversion::Client c;
      oldversion::Friend f;
      f.access_client_data(c);
    }

    {
      std::cout << "\nRestrict a friend to access only allowed methods and data.\n";

      Client c;
      Friend f;
      f.access_client_data(c);
    }

    {
      std::cout << "\nFriendship is not inheritable:\n";

      F f;
      f.run();
    }
  }
}
