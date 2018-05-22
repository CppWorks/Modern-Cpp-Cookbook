#pragma once

// The exit handlers, regardless of the method they are registered with, are called only
// when the program terminates normally or quickly.

// If multiple handlers are registered, then they are called in the reverse order of the
// registration.

// exit(), quick_exit(), atexit(), and at_quick_exit(), are available in the namespace std
// in the header <cstdlib>.
#include <cstdlib>
#include <iostream>

namespace recipe_6_08 {
  void exit_handler_1()
  {
    std::cout << "exit handler 1" << std::endl;
  }

  void exit_handler_2()
  {
    std::cout << "exit handler 2" << std::endl;
  }

  void quick_exit_handler_1()
  {
    std::cout << "quick exit handler 1" << std::endl;
  }

  void quick_exit_handler_2()
  {
    std::cout << "quick exit handler 2" << std::endl;
  }

  struct static_foo {
    ~static_foo()
    {
      std::cout << "static foo destroyed!" << std::endl;
    }
    static static_foo* instance()
    {
      static static_foo obj;
      return &obj;
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 6.08: Registering a function to be called when a program "
                 "exits normally."
              << "\n---------------------------------------------------------------------"
                 "----------\n";

    {
      std::cout << "\nstd::atexit() to register functions to be invoked when they return "
                   "from main() or when a call to std::exit() is made:\n";

      std::atexit(exit_handler_1);
      static_foo::instance();
      std::atexit(exit_handler_2);
      std::atexit([]() { std::cout << "exit handler 3" << std::endl; });

      // std::exit(42);    // exit handlers are invoked
      // std::terminate(); // exit handlers are not invoked
    }

    {
      std::cout << "\nstd::at_quick_exit() to register functions to be invoked when a "
                   "call to std::quick_exit() is made:\n";

      std::at_quick_exit(quick_exit_handler_1);
      std::at_quick_exit(quick_exit_handler_2);
      std::at_quick_exit([]() { std::cout << "quick exit handler 3" << std::endl; });

      // std::quick_exit(42); // exit handlers are invoked
      // std::terminate();    // exit handlers are not invoked
    }
  }
}
