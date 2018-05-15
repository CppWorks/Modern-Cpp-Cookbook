#pragma once

// With C++11, every constructor without the explicit specifier is considered a converting
// constructor. We will see how to use explicit constructors and conversion operators and
// how to avoid implicit conversions.

#include <cassert>
#include <iostream>

namespace recipe_1_10 {
  // The following class has three constructors:
  // a default constructor (without parameters),
  // a constructor that takes an int,
  // and a constructor that takes two parameters, an int and a double.
  // As of C++11, these are all considered converting constructors.
  // The class also has a conversion operator that converts the type to a bool.
  struct foo {
    foo()
    {
      std::cout << "foo" << std::endl;
    }
    foo(int const a)
    {
      std::cout << "foo(a)" << std::endl;
    }
    foo(int const a, double const b)
    {
      std::cout << "foo(a, b)" << std::endl;
    }

    operator bool() const
    {
      return true;
    }
  };

  struct foo2 {
    foo2()
    {
      std::cout << "foo2" << std::endl;
    }
    foo2(std::initializer_list<int> l)
    {
      std::cout << "foo2(l)" << std::endl;
    }
    foo2(int const a)
    {
      std::cout << "foo2(a)" << std::endl;
    }
    foo2(int const a, double const b)
    {
      std::cout << "foo2(a, b)" << std::endl;
    }

    operator bool() const
    {
      return true;
    }
  };

  void bar(foo const f) {}

  enum ItemSizes { DefaultHeight, Large, MaxSize };

  class string_buffer {
  public:
    explicit string_buffer()
    {
      std::cout << "string_buffer()" << std::endl;
    }

    explicit string_buffer(size_t const size)
    {
      std::cout << "string_buffer(size)" << std::endl;
    }

    explicit string_buffer(char const* const ptr)
    {
      std::cout << "string_buffer(ptr)" << std::endl;
    }

    explicit operator bool() const
    {
      return true;
    }
    explicit operator char* const() const
    {
      return nullptr;
    }
  };

  // Both an explicit constructor and an explicit converting operator:
  struct handle_t {
    explicit handle_t(int const h)
      : handle(h)
    {
    }

    explicit operator bool() const
    {
      return handle != 0;
    };

  private:
    int handle;
  };

  void execute()
  {
    std::cout << "\nRecipe 1.10: Using explicit constructors and conversion operators to "
                 "avoid implicit conversion."
              << "\n---------------------------------------------------------------------"
                 "--------------------------\n";
    {
      // default constructor
      foo f1;   // foo
      foo f2{}; // foo

      // constructor with an int
      // f3 is initialized using the functional form
      foo f3(1); // foo(a)
      // f4 is copy initialized
      foo f4 = 1; // foo(a)
      // f5 is directly initialized using brace-init-list
      foo f5{ 1 }; // foo(a)
      // f6 is copy initialized
      foo f6 = { 1 }; // foo(a)

      // constructor with int and double
      foo f7(1, 2.0);      // foo(a, b)
      foo f8{ 1, 2.0 };    // foo(a, b)
      foo f9 = { 1, 2.0 }; // foo(a, b)

      std::cout << "...............................................\n";

      // It may be important to note that if foo defines a constructor that takes an
      // std::initializer_list, then all the initializations using {} would resolve to
      // that constructor. See foo2.
      // In this case, f5 and f6 will print foo(l), while f8 and f9 will generate compiler
      // errors because all elements of the initializer list should be integers.
      foo2 f2_1;         // foo2
      foo2 f2_2{};       // foo2
      foo2 f2_3(1);      // foo2(a)
      foo2 f2_4 = 1;     // foo2(a)
      foo2 f2_5{ 1 };    // foo2(l)
      foo2 f2_6 = { 1 }; // foo2(l)
      foo2 f2_7(1, 2.0); // foo2(a, b)
      // foo2 f2_8{ 1, 2.0 };    // Error
      // foo2 f2_9 = { 1, 2.0 }; // Error

      // The conversion operator to bool in the example above also enables us to use foo
      // objects where boolean values are expected.
      // The first two are examples where foo is expected to be used as boolean but the
      // last two with addition and test for equality are probably incorrect, as we most
      // likely expect to add foo objects and test foo objects for equality, not the
      // booleans they implicitly convert to.

      bool flag = f1;
      if (f2) {
      }
      std::cout << "\nf3 + f4 = " << f3 + f4;
      assert(f5 == f6);
      std::cout << "\nf5 == f6\n\n";
    }

    {
      // These may all look right, but the implicit conversion constructors enable
      // scenarios where the implicit conversion may not be what we wanted:
      bar({});         // foo()
      bar(1);          // foo(a)
      bar({ 1, 2.0 }); // foo(a, b)
    }

    {
      // With explicit constructors, the compiler is able to immediately flag erroneous
      // situations and developers can react accordingly, either fixing the initialization
      // with a correct value or providing an explicit cast.

      string_buffer b4 = string_buffer('a');
      string_buffer b5 = static_cast<string_buffer>(MaxSize);
      string_buffer b6 = string_buffer{ "a" };

      // The following definitions are still possible (and wrong) with explicit
      // constructors:
      std::cout << "b7{ 'a' } -> ";
      string_buffer b7{ 'a' };
      std::cout << "b8('a') -> ";
      string_buffer b8('a');

      // Error, no implicit conversion.
      // std::cout << b4 + b5 << std::endl;
      // if (b4 == b5) {}

      std::cout << "\nb4 + b5 = " << static_cast<bool>(b4) + static_cast<bool>(b5)
                << std::endl;
      if (static_cast<bool>(b4) == static_cast<bool>(b5)) {
      }
    }

    {
      auto h = handle_t{ 42 };
      bool ok = static_cast<bool>(h);
      if (h) {
      }
    }
  }
}
