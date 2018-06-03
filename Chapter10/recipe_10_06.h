#pragma once

// A technique called the curiously recurring template pattern (or CRTP) allows simulating
// the virtual functions-based runtime polymorphism at compile time, by deriving classes
// from a base class template parameterized with the derived class. This technique is used
// extensively in some libraries, including the Microsoft's Active Template Library (ATL)
// and Windows Template Library (WTL).

// The curiously recurring template pattern enables the simulation of virtual calls at
// compile time using metaprogramming that eventually translates to functions overloading.

#include <iostream>
#include <memory>
#include <vector>

namespace recipe_10_06 {
  namespace demo1 {
    // To implement the curiously recurring template pattern in order to achieve static
    // polymorphism, do the following:

    // 1. Provide a class template that will represent the base class for other classes
    // that should be treated polymorphically at compile time. Polymorphic functions are
    // invoked from this class:
    template <class T>
    class base {
    public:
      void func1()
      {
        // To invoke the functions from the derived class, we must first obtain a pointer
        // to the derived class. That is done with a static_cast conversion:
        static_cast<T*>(this)->func1();
      }
    };

    // 2. Derived classes use the class template as their base class; THE DERIVED CLASS IS
    // ALSO THE TEMPLATE ARGUMENT FOR THE BASE CLASS. The derived class implements the
    // functions that are invoked from the base class:
    class derived : public base<derived> {
    public:
      void func1()
      {
        std::cout << "derived::func1" << std::endl;
      }
    };

    // 3. Function templates can handle derived classes polymorphically through a pointer
    // or reference to the base class template:
    template <class T>
    void do_something(base<T>& b)
    {
      b.func1();
    }
  }

  namespace demo2 {
    template <class T>
    class control {
    public:
      void draw()
      {
        static_cast<T*>(this)->erase_background();
        static_cast<T*>(this)->paint();
      }
    };

    // This pattern may look rather strange at a first glance, but it is perfectly legal.
    // The idea is to derive a class from a base class that is a template class and to
    // pass the derived class itself for the type template parameter of the base class.
    // The base class then makes calls to the derived class functions. In our example,
    // control<button>::draw() is declared before the button class is known to the
    // compiler. However, the control class is a class template, that means, it is
    // instantiated only when the compiler encounters code that uses it. At that point,
    // the button class, in this example, is already defined and known to the compiler, so
    // calls to button::erase_background() and button::paint() can be made.

    class button : public control<button> {
    private:
      friend class control<button>;

      void erase_background()
      {
        std::cout << "erasing button background..." << std::endl;
      }

      void paint()
      {
        std::cout << "painting button..." << std::endl;
      }
    };

    class checkbox : public control<checkbox> {
    public:
      void erase_background()
      {
        std::cout << "erasing checkbox background..." << std::endl;
      }

      void paint()
      {
        std::cout << "painting checkbox..." << std::endl;
      }
    };

    template <class T>
    void draw_control(control<T>& c)
    {
      c.draw();
    }

    template <class T>
    class fancybutton : public control<fancybutton<T>> {
    public:
      void erase_background()
      {
        static_cast<T*>(this)->paint_area();
      }

      void paint()
      {
        std::cout << "painting button..." << std::endl;
      }
    };

    class transparentbutton : public fancybutton<transparentbutton> {
    public:
      void paint_area()
      {
        std::cout << "painting transparent button background..." << std::endl;
      }
    };
  }

  namespace demo3 {

    // When objects of types implementing the CRTP need to be stored homogeneously in a
    // container, an additional idiom must be used. The base class template must be itself
    // derived from another class with pure virtual functions (and a virtual public
    // destructor).

    class controlbase {
    public:
      virtual void draw() = 0;
      virtual ~controlbase() {}
    };

    template <class T>
    class control : public controlbase {
      T* derived()
      {
        return static_cast<T*>(this);
      }

    public:
      virtual void draw() override
      {
        derived()->erase_background();
        derived()->paint();
      }
    };

    class button : public control<button> {
    public:
      void erase_background()
      {
        std::cout << "erasing button background..." << std::endl;
      }

      void paint()
      {
        std::cout << "painting button..." << std::endl;
      }
    };

    class checkbox : public control<checkbox> {
    public:
      void erase_background()
      {
        std::cout << "erasing checkbox background..." << std::endl;
      }

      void paint()
      {
        std::cout << "painting checkbox..." << std::endl;
      }
    };

    void draw_controls(std::vector<std::shared_ptr<controlbase>>& v)
    {
      for (auto& c : v) {
        c->draw();
      }
    }
  }

  void execute()
  {
    std::cout << "\nRecipe 10.06: Static polymorphism with the curiously recurring "
                 "template pattern."
              << "\n---------------------------------------------------------------------"
                 "-----------\n";

    {
      std::cout << "Demo 1:\n";

      using namespace demo1;

      derived d;
      d.func1();

      // Calls derived function!
      do_something(d);
    }

    {
      std::cout << "\nDemo 2:\n";

      using namespace demo2;

      button b;
      b.draw();
      checkbox c;

      draw_control(b);
      draw_control(c);
    }

    {
      std::cout << "\nDemo 2 (transparent button):\n";

      using namespace demo2;

      transparentbutton b;
      b.draw();
    }

    {
      std::cout << "\nDemo 3:\n";

      using namespace demo3;

      //  We can store pointers to the abstract class in a container, such as std::vector:
      std::vector<std::shared_ptr<controlbase>> v;
      v.emplace_back(std::make_shared<button>());
      v.emplace_back(std::make_shared<checkbox>());

      draw_controls(v);
    }
  }
}
