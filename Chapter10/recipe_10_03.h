#pragma once

// C++ supports only positional parameters, which means arguments are passed to
// a function based on the parameter's position. A technique called the named
// parameter idiom provides a method to emulate named parameters.

#include <string>
#include <string_view>

namespace recipe_10_03 {
  class control;

  // To implement the named parameter idiom for a function (usually with many default parameters), do the following:

  // 1. Create a class to wrap the parameters of the function:
  class control_properties {
    int id_;
    std::string text_;
    int width_ = 0;
    int height_ = 0;
    bool visible_ = false;

    // 2. The class or function that needs to access these properties could be
    // declared as friend to avoid writing getters:
    friend class control;

  public:
    // 3. Every positional parameter of the original function that does not have
    // a default value should become a positional parameter without a default
    // value in the constructor of the class:
    control_properties(int const id)
      : id_(id)
    {
    }

    // 4. For every positional parameter of the original function that has a
    // default value, there should be a function (with the same name) that sets
    // the value internally and returns a reference to the class (for chaining):
    control_properties& text(std::string_view t)
    {
      text_ = t.data();
      return *this;
    }

    control_properties& width(int const w)
    {
      width_ = w;
      return *this;
    }

    control_properties& height(int const h)
    {
      height_ = h;
      return *this;
    }

    control_properties& visible(bool const v)
    {
      visible_ = v;
      return *this;
    }
  };

  class control {
    int id_;
    std::string text_;
    int width_;
    int height_;
    bool visible_;

  public:
    // The control class represents a visual control, such as a button or an
    // input and has properties such as numerical identifier, text, size, and
    // visibility. These are provided to the constructor and, except for the ID,
    // all the others have default values.
    control(int const id, std::string_view text = "", int const width = 0,
            int const height = 0, bool const visible = false)
      : id_(id)
      , text_(text)
      , width_(width)
      , height_(height)
      , visible_(visible)
    {
    }

    // 5. The original function should be modified, or an overload should be
    // provided, to take an argument of the new class from which the property
    // values would be read:
    control(control_properties const& cp)
      : id_(cp.id_)
      , text_(cp.text_)
      , width_(cp.width_)
      , height_(cp.height_)
      , visible_(cp.visible_)
    {
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 10.03: Implementing the named parameter idiom."
              << "\n-----------------------------------------------------\n";

    {
      std::cout << "Creating a control with default values (initial implementation).\n";

      control c(1044, "sample", 100, 20, true);
    }

    {
      std::cout << "\nCreating a control with fluent interface.\n";

      // The named parameter idiom has the advantage that it allows you to
      // specify values only for the parameters that you want, in any order,
      // using a name, which is much more intuitive than a fixed, positional
      // order.
      control c(control_properties(1044).visible(true).height(20).width(100));
    }
  }
}
