#pragma once

// Exceptions are a mechanism for simpler and more robust error handling, as opposed to
// returning error codes that could greatly complicate and clutter the code.

// Exceptions are thrown and handled only when a function fails, which should happen more
// rarely than successful executions. This can actually lead to faster code than code that
// returns and tests error codes.

//  Exceptions should be a mechanism which constructors should use to indicate failure.
//  Together with the RESOURCE ACQUISITION IS INITIALIZATION (RAII) idiom, this ensures
//  safe acquisition and release of resources in all situations. On the other hand,
//  exceptions are not allowed to leave a destructor. When this happens, the program
//  abnormally terminates with a call to std::terminate().

// The rule of thumb for dealing with exceptions in constructors and destructors is as follows:

// 1. Use exceptions to indicate the errors that occur in constructors.

// 2. Do not throw or let exceptions leave destructors.

// Some guidelines for exception throwing:

// 1. Prefer throwing either standard exceptions or your own exceptions derived from
// std::exception or another standard exception.

// 2. Avoid throwing exceptions of built-in types, such as integers.

// 3. When using a library or framework that provides its own exception hierarchy, prefer
// throwing exceptions from this hierarchy or your own exceptions derived from it, at
// least in the parts of the code tightly related to it to keep the code consistent.

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

namespace recipe_9_01 {
  class simple_error : public std::exception {
  public:
    virtual const char* what() const noexcept override
    {
      return "Simple exception.";
    }
  };

  class another_logic_error : public std::logic_error {
  public:
    another_logic_error()
      : std::logic_error("Simple logic exception.")
    {
    }
  };

  // Exceptions and error codes are not mutually exclusive. Exceptions should be used only
  // for transferring the control flow in exceptional situations, not for controlling the
  // data flow in a program.
  class advanced_error : public std::runtime_error {
    int error_code;

    std::string make_message(int const e)
    {
      std::stringstream ss;
      ss << "Error with code " << e << ".";
      return ss.str();
    }

  public:
    advanced_error(int const e)
      : std::runtime_error(make_message(e).c_str())
      , error_code(e)
    {
    }

    int error() const noexcept
    {
      return error_code;
    }
  };

  void throwing_func()
  {
    // Throw exceptions by value:
    throw std::system_error(std::make_error_code(std::errc::timed_out));
  }

  void another_throwing_func()
  {
    throw std::string{ "error!" };
  }

  void throw_simple()
  {
    throw simple_error();
  }

  void throw_advanced()
  {
    throw advanced_error(42);
  }

  void handle_exception()
  {
    // Exceptions prefixed with bad_, such as std::bad_alloc, std::bad_cast, and
    // std::bad_function_call, represent various errors in a program

    try {
      // Use throw; to rethrow the current exception. This can be used to create a single
      // exception handling function for multiple exceptions. Throw the exception object
      // (for example, throw e;) when you want to hide the original location of the
      // exception:
      throw; // throw current exception
    }
    catch (const std::logic_error&) {
      // std::logic_error represents an exception that indicates an error in the program
      // logic, such as an invalid argument, an index beyond the bounds of a range, and so
      // on.
      std::cout << "Logic error.\n";
    } catch (const std::runtime_error&) {
      //  std::runtime_error represents an exception that indicates an error beyond the
      //  scope of the program or that cannot be predicted due to various factors,
      //  including external ones, such as overflows and underflows or operating system
      //  errors.
      std::cout << "Runtime error.\n";
    } catch (const std::exception&) {
      // The base class for all these exceptions is std::exception.
      std::cout << "Standard exception.\n";
    }
  }

  void execute()
  {
    std::cout << "Recipe 9.01: Using exceptions for error handling.\n"
              << "-------------------------------------------------\n";

    auto exprint = [](std::exception const& e) { std::cout << e.what() << std::endl; };

    {
      std::cout << "Catching exceptions by constant reference:\n";

      try {
        throwing_func();
      }
      // Catch exceptions by reference, or in most cases, by constant reference:
      catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
      }
    }

    {
      std::cout << "\nOrder catch statements:\n";

      try {
        throwing_func();
      }
      // Order catch statements from the most derived class to the base class of the
      // hierarchy when catching multiple exceptions from a class hierarchy:
      catch (std::system_error const& e) {
        exprint(e);
      } catch (std::runtime_error const& e) {
        exprint(e);
      } catch (std::exception const& e) {
        exprint(e);
      }
      // Use catch(...) to catch all the exceptions, regardless of their type:
      catch (...) {
        std::cout << "unknown exception" << std::endl;
      }
    }

    {
      std::cout << "\nRethrowing exceptions:\n";

      try {
        try {
          throwing_func();
        } catch (...) {
          auto e = std::current_exception();
          std::rethrow_exception(e);
        }
      } catch (std::exception const& e) {
        exprint(e);
      }
    }

    {
      std::cout << "\nSimple error:\n";

      try {
        throw_simple();
      } catch (simple_error const& e) {
        exprint(e);
      }
    }

    {
      std::cout << "\nAdvanced error:\n";

      try {
        throw_advanced();
      } catch (advanced_error const& e) {
        exprint(e);
      }
    }

    {
      std::cout << "\nCatch all exceptions:\n";

      try {
        throwing_func();
      } catch (...) {
        handle_exception();
      }
    }
  }
}
