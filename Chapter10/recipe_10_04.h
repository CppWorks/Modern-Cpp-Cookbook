#pragma once

// Virtual functions provide customization points for a class, by allowing derived classes
// to modify implementations from a base class. When a derived class object is handled
// through a pointer or a reference to a base class, calls to overridden virtual functions
// end up invoking the overridden implementation from the derived class.

// The non-virtual idiom (NVI) helps enforcing the promised contract of an interface.

// Implementing this idiom requires following several simple design guidelines:

// 1. Make (public) interfaces non-virtual.

// 2. Make virtual functions private.

// 3. Make virtual functions protected only if the base implementation has to be called
// from a derived class.

// 4. Make the base class destructor either public and virtual or protected and
// nonvirtual.

// A special mention of the destructor of a class is required for this idiom. It is often
// stressed that base class destructors should be virtual so that objects can be deleted
// polymorphically (through a pointer or references to a base class). Destructing objects
// polymorphically when the destructor is not virtual incurs undefined behavior. However,
// not all base classes are intended to be deleted polymorphically. For those particular
// cases, the base class destructor should not be virtual. However, it should also not be
// public, but protected.

#include <iostream>
#include <memory>
#include <vector>

namespace recipe_10_04 {
  class control {
  private:
    // 2. Make virtual functions private:
    virtual void paint() = 0;

  protected:
    // 3. Make virtual functions protected only if the base implementation has to be called
    // from a derived class:
    virtual void initialize_impl()
    {
      std::cout << "initializing control..." << std::endl;
    }

    virtual void erase_background()
    {
      std::cout << "erasing control background..." << std::endl;
    }

  public:
    // The only functionality defined by the control class is drawing the controls. The
    // draw() method is nonvirtual, but it calls two virtual methods, erase_background()
    // and paint(), to implement the two phases of drawing the control.

    // 1. Make (public) interfaces non-virtual:
    void draw()
    {
      erase_background();
      paint();
    }

    void initialize()
    {
      initialize_impl();
    }

    // The destructor of the control class is public and virtual because objects are
    // expected to be deleted polymorphically.

    // 4. Make the base class destructor either public and virtual or protected and
    // nonvirtual:
    virtual ~control()
    {
      std::cout << "destroying control..." << std::endl;
    }
  };

  class button : public control {
  private:
    virtual void paint() override
    {
      std::cout << "painting button..." << std::endl;
    }

  protected:
    virtual void initialize_impl()
    {
      control::initialize_impl();
      std::cout << "initializing button..." << std::endl;
    }

    virtual void erase_background() override
    {
      control::erase_background();
      std::cout << "erasing button background..." << std::endl;
    }

  public:
    ~button()
    {
      std::cout << "destroying button..." << std::endl;
    }
  };

  class checkbox : public button {
  private:
    virtual void paint() override
    {
      std::cout << "painting checkbox..." << std::endl;
    }

  protected:
    virtual void erase_background() override
    {
      button::erase_background();
      std::cout << "erasing checkbox background..." << std::endl;
    }

  public:
    ~checkbox()
    {
      std::cout << "destroying checkbox..." << std::endl;
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 10.04: Separating interfaces from implementations with the "
                 "non-virtual interface idiom."
              << "\n---------------------------------------------------------------------"
                 "-------------------------\n";

    {
      std::vector<std::shared_ptr<control>> controls;

      controls.push_back(std::make_shared<button>());
      controls.push_back(std::make_shared<checkbox>());

      for (auto& c : controls)
        c->draw();
    }

    {
      button b;
      b.initialize();
      b.draw();
    }
  }
}
