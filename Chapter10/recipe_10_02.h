#pragma once

// PIMPL stands for pointer to implementation (but is also known as the Cheshire
// cat idiom or the compiler firewall idiom) and is an opaque pointer technique
// that enables the separation of the implementation details from an interface.

// This has the advantage that it enables changing the implementation without
// modifying the interface and, therefore, avoiding the need to recompile the
// code that is using the interface.

// The code can arguably be less readable, as there is a level of indirection
// and all the implementation details need to be looked up in the other files.
// In this recipe, the pimpl class definition is provided in the source
// file of the public class, but in practice, it could be in separate files.

// This approach does not work with protected members because these have to be
// available to the derived classes.

// This approach does not work with the private virtual functions, that have to
// appear in the class, either because they override functions from a base
// class, or have to be available for overriding in a derived class.

// As a rule of thumb, when implementing the pimpl idiom, always put all private
// member data and functions, except for the virtual ones, in the pimpl class
// and leave the protected data members and functions and all private virtual
// functions in the public class.

#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#include "control.h"

namespace recipe_10_02 {

class oldcontrol {
  std::string text;
  int width = 0;
  int height = 0;
  bool visible = true;

  void draw() {
    std::cout << "control " << std::endl
              << "  visible: " << std::boolalpha << visible << std::noboolalpha
              << std::endl
              << "  size: " << width << ", " << height << std::endl
              << "  text: " << text << std::endl;
  }

public:
  void set_text(std::string_view t) {
    text = t.data();
    draw();
  }

  void resize(int const w, int const h) {
    width = w;
    height = h;
    draw();
  }

  void show() {
    visible = true;
    draw();
  }

  void hide() {
    visible = false;
    draw();
  }
};

void execute() {
  std::cout << "\nRecipe 10.02: Implementing the pimpl idiom."
            << "\n-------------------------------------------\n";

  {
    std::cout << "Old Control:\n";

    oldcontrol c;
    c.resize(100, 20);
    c.set_text("sample");
    c.hide();

    // The original control class is both copyable and movable:
    oldcontrol c2 = c;
    c2.show();
    oldcontrol c3 = std::move(c2);
    c3.hide();
  }

  {
    std::cout << "\nNew Control:\n";

    control c;
    c.resize(100, 20);
    c.set_text("sample");
    c.hide();

    // The refactored control class is only movable, not copyable.
    control c2 = std::move(c);
    c2.show();
  }

  {
    std::cout << "\nCopyable:\n";

    //  In order to make it both copyable and movable, we must provide the copy
    //  constructor and copy assignment operator and both the move constructor
    //  and move assignment operator. The latter ones can be defaulted, but the
    //  former ones must be explicitly implemented to create a new control_pimpl
    //  object from the object that it is copied from.
    
    control_copyable c;
    c.resize(100, 20);
    c.set_text("sample");
    c.hide();

    control_copyable c2 = c;
    c2.show();

    control_copyable c3 = std::move(c2);
    c3.hide();
  }
}
}
