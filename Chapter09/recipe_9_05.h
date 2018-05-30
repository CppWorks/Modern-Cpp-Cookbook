#pragma once

// The language supports compatibility with C casting style in either the (type)expression
// or type(expression) form. However, this type of casting breaks the type safety of C++.
// Therefore, the language also provides several conversions, static_cast, dynamic_cast,
// const_cast, and reinterpret_cast. They are used to better indicate intent and write
// safer code.

#include <iostream>
#include <string>

namespace recipe_9_05 {
  void old_api(char* str, unsigned int size)
  {
    // do something without changing the string
  }

  class control {
  public:
    typedef size_t data_type;

    void set_data(data_type d)
    {
      data = d;
    }
    data_type get_data() const
    {
      return data;
    }

  private:
    data_type data;
  };

  class user_data {
  };

  enum options { one = 1, two, three };

  struct base {
    virtual void run() {}
    virtual ~base() {}
  };

  struct derived : public base {
  };

  struct struct1 {
  };
  struct struct2 {
  };

  void execute()
  {
    std::cout << "\nRecipe 9.05: Performing correct type casts."
              << "\n-------------------------------------------\n";

    // static cast
    {
      // Use static_cast to perform type casting of non-polymorphic types, including
      // casting of integers to enumerations, from floating point to integral values or
      // from a pointer type to another pointer type, such as from a base class to a
      // derived class (downcasting) or from a derived class to a base class (upcasting),
      // without any runtime checks:

      int x = 42, y = 13;
      double d = static_cast<double>(x) / y;

      int n = static_cast<int>(d);

      int value = 1;
      options op = static_cast<options>(value);
    }

    // dynamic cast
    {
      // Use dynamic_cast to perform type casting of pointers or references of polymorphic
      // types from a base class to a derived class or the other way around. These checks
      // are performed at runtime and require that RUNTIME TYPE INFORMATION (RTTI) is
      // enabled. (Seems to be the default with CMake.) Dynamic casting can only be used
      // for pointers and references. This cast is performed at compile time:

      derived d;
      base b;

      base* pb = dynamic_cast<base*>(&d);       // OK
      derived* pd = dynamic_cast<derived*>(&b); // fail

      try {
        base& rb = dynamic_cast<base&>(d);       // OK
        derived& rd = dynamic_cast<derived&>(b); // fail
      } catch (std::bad_cast const& e) {
        std::cout << e.what() << std::endl;
      }

      // struct1 s1;
      // struct2* ps2 = dynamic_cast<struct2*>(&s1); // error
    }

    // const cast
    {
      // Use const_cast to perform conversion between types with different const and
      // volatile specifiers, such as removing const from an object that was not declared
      // as const:

      std::string str{ "sample" };
      old_api(const_cast<char*>(str.c_str()), static_cast<unsigned int>(str.size()));

      // const_cast should only be used to remove const or volatile qualifiers when the
      // object is not declared const or volatile. Anything else incurs undefined
      // behavior, as shown in the example below:
      int const a = 42;
      int const* p = &a;
      int* q = const_cast<int*>(p);
      // undefined behavior
      *q = 0;
    }

    // reinterpret cast
    {
      // Use reinterpret_cast to perform a bit reinterpretation, such as conversion
      // between integers and pointer types, from pointer types to integer, from a pointer
      // type to any other pointer type, without involving any runtime checks.
      // reinterpret_cast is more like a compiler directive. It does not translate into
      // any CPU instructions, but only instructs the compiler to interpret the binary
      // representation of an expression as it was of another, specified type. This is a
      // type-unsafe conversion and should be used with care:

      control c;

      user_data* ud = new user_data();
      c.set_data(reinterpret_cast<control::data_type>(ud));

      user_data* ud2 = reinterpret_cast<user_data*>(c.get_data());

      // undefined behavior
      int* pi = new int{ 42 };
      double* pd = reinterpret_cast<double*>(pi);
    }
  }
}
