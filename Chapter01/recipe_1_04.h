#pragma once

#include <iostream>
#include <string>

// The order in which non-static data members are initialized is the order in which they
// were declared in the class definition, and not the order of their initialization in a
// constructor initializer list. On the other hand, the order in which non-static data
// members are destroyed is the reversed order of construction.

namespace recipe_1_04 {
  struct Point {
    double X;
    double Y;

    // Using constructor initialization list.
    Point(double const x = 0.0, double const y = 0.0)
      : X(x)
      , Y(y)
    {
    }
  };

  struct foo {
    // Using assignments in the constructor is not efficient, as this can create temporary
    // objects that are later discarded.
    foo()
    {
      std::cout << "default constructor" << std::endl;
    }
    foo(std::string const& text)
    {
      std::cout << "constructor '" << text << "'" << std::endl;
    }
    foo(foo const& other)
    {
      std::cout << "copy constructor" << std::endl;
    }
    foo(foo&& other)
    {
      std::cout << "move constructor" << std::endl;
    };
    foo& operator=(foo const& other)
    {
      std::cout << "assignment" << std::endl;
      return *this;
    }
    foo& operator=(foo&& other)
    {
      std::cout << "move assignment" << std::endl;
      return *this;
    }
    ~foo()
    {
      std::cout << "destructor" << std::endl;
    }
  };

  enum class TextVerticalAligment { Top, Middle, Bottom };
  enum class TextHorizontalAligment { Left, Center, Right };

  void execute()
  {
    std::cout
      << "\nRecipe 1.04: Understanding the various forms of non-static member "
         "initialization.\n"
      << "-------------------------------------------------------------------------"
         "--------\n";
    {
      struct bar {
        foo f;

        bar(foo const& value)
        {
          f = value;
        }
      };

      foo f;
      // unnecessary default constructor + assignment.
      bar b(f);
    }
    std::cout << "...............................................\n";
    {
      struct bar {
        foo f;

        bar(foo const& value)
          : f(value)
        {
        }
      };

      foo f;
      // now just copy constructor
      bar b(f);
    }
    std::cout << "...............................................\n";
    {
      enum class TextFlow { LeftToRight, RightToLeft };

      struct Control {
        // default member initializations
        const int DefaultHeight{ 20 };
        const int DefaultWidth = 100;
        TextFlow textFlow = TextFlow::LeftToRight;

        // 'text' is the only one not assigned in the declaration. Will be done in the
        // constructor.
        std::string text;

        Control(std::string t)
          : text(t)
        {
        }
      };
    }

    {
      // If a data member is initialized both with the default member initialization and
      // constructor initializer list, the latter takes precedence and the default value
      // is discarded.
      struct bar {
        foo f{ "default value" };

        bar()
          : f{ "constructor initializer" }
        {
        }
      };

      // Using the appropriate initialization method for each member leads not only to
      // more efficient code but also to better organized and more readable code.
      bar b;
    }
  }
} // namespace recipe_1_04
