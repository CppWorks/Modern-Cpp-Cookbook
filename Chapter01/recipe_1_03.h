#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

// For checking types.
template <class T>
class TD;

// Uniform initialization is arguably one of the most important features from C++11 that
// developers should understand and use.

// *Direct initialization* using ctor.
std::string s1("test");

// *Copy initialization* using copy ctor.
std::string s2 = "test";

// To uniformly initialize objects regardless of their type, use the brace-initialization
// form {} that can be used for both direct initialization and copy initialization. When
// used with brace initialization, these are called direct list and copy list
// initialization.

// direct list initialization
// T object {other};

// copy list initialization
// T object = {other};

namespace recipe_1_03 {

  void func(int const a, int const b, int const c)
  {
    // Print one line.
    std::cout << a << b << c << std::endl;
  }

  void func(std::initializer_list<int> const l)
  {
    // Print a line for each value.
    for (auto const& e : l)
      std::cout << e << std::endl;
  }

  void execute()
  {
    std::cout << "\nRecipe 1.03: Understanding uniform initialization.\n"
              << "--------------------------------------------------\n";
    {
      int a = 42;
      double b = 1.2;
      bool c = false;
    }

    {
      class foo {
        int a_;

      public:
        foo(int a)
          : a_(a)
        {
        }
      };

      foo f1 = 42;
    }

    {
      class foo {
        int a_;
        double b_;

      public:
        foo()
          : a_(0)
          , b_(0)
        {
        }

        foo(int a, double b = 0.0)
          : a_(a)
          , b_(b)
        {
        }
      };

      foo f1; // default initialization
      foo f2(42, 1.2);
      foo f3(42);
      // foo f4();         // function declaration
    }

    {
      struct bar {
        int a_;
        double b_;
      };

      bar b = { 42, 1.2 };

      int a[] = { 1, 2, 3, 4, 5 };
    }

    {
      class foo {
        int a_;
        double b_;

      public:
        foo()
          : a_(0)
          , b_(0)
        {
        }
        foo(int a, double b = 0.0)
          : a_(a)
          , b_(b)
        {
        }
      };

      // POD = Plain Old Data
      // A class (whether defined with the keyword 'struct' or 'class') without
      // constructors, destructors and virtual members functions.

      struct bar {
        int a_;
        double b_;
      };

      // Built-in types:
      int i{ 42 };
      double d{ 1.2 };

      // Arrays:
      int arr1[3]{ 1, 2, 3 };

      // Dynamically allocated arrays:
      int* arr2 = new int[3]{ 1, 2, 3 };

      // User-defined types:
      foo f1{};
      foo f2{ 42, 1.2 };
      foo f3{ 42 };

      // User-defined POD types:
      bar b{ 42, 1.2 };

      // Standard containers:
      std::vector<int> v{ 1, 2, 3 };
      std::map<int, std::string> m{ { 1, "one" }, { 2, "two" } };

      // Obsolete style (before C++11)
      bar b1 = { 42, 1.2 };
      int a[] = { 1, 2, 3, 4, 5 };
    }

    {
      class foo {
        int a_;
        int b_;

      public:
        foo()
          : a_(0)
          , b_(0)
        {
        }

        foo(int a, int b = 0)
          : a_(a)
          , b_(b)
        {
        }
        foo(std::initializer_list<int> l)
        {
        }
      };

      foo f{ 1, 2 }; // calls constructor with initializer_list<int>

      // Obsolete style (before C++11)!!!
      foo f1; // default initialization
      foo f2(42, 1);
      foo f3(42);
      // But! This is a function declaration!
      // foo f4();
    }

    {
      // An initializer list always takes precedence over other functions (including
      // constructors) where brace-initialization is used.
      func({ 1, 2, 3 }); // calls second overload
    }

    {
      // Watch out!
      // Creates a vector with one element with a value 5.
      std::vector<int> v1{ 5 };
      // Creates a vector with five elements
      std::vector<int> v2(5);
    }

    {
      // Brace-initialization does not allow narrowing conversion. A narrowing conversion
      // is an implicit conversion. int i{1.2};  // Error! int i(1.2);  // Warning that
      // implicit conversion will take place.

      double d = 47 / 13;
      // float f1{ d };		// Error!
      float f2{ 47 / 13 }; // OK
    }

    {
      // To fix the error, an explicit conversion must be done:
      int i{ static_cast<int>(1.2) };

      double d = 47 / 13;
      float f1{ static_cast<float>(d) };
    }

    {
      // Direct-list-initialization and copy-list-initialization.
      auto a = { 42 };   // a -> initializer_list<int>
      auto b{ 42 };      // b -> int
      auto c = { 4, 2 }; // c -> initializer_list<int>

      // TD<decltype(c)> cType;

      // Error! Direct-list-initialization of ‘auto’ requires exactly one element.
      // auto d{4, 2};
    }
  }
} // namespace recipe_1_03
