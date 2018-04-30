#pragma once

#include <iostream>

// The keyword virtual is optional for declaring overrides in derived classes that can
// lead to confusion when dealing with large classes or hierarchies.
// We will see how to use C++11 special identifiers override and final to declare virtual
// functions or classes.

// Always use the virtual keyword when declaring virtual functions in derived classes that
// are supposed to override virtual functions from a base class, and

// Always use the override special identifier after the declarator part of a virtual
// function declaration or definition.

namespace recipe_1_07 {
  void execute()
  {
    std::cout << "\nRecipe 1.07: Using override and final for virtual methods."
              << "\n----------------------------------------------------------\n";
    {
      class Base {
      public:
        virtual void foo(int const a) {}
      };

      class Derived : public Base {
      public:
        virtual void foo(int const a) {}
      };
    }

    {
      class Base {
        virtual void foo() = 0;
        virtual void bar() {}
        virtual void foobar() = 0;
      };

      class Derived1 : public Base {
        virtual void foo() override = 0;
        virtual void bar() override {}
        virtual void foobar() override {}
      };

      class Derived2 : public Derived1 {
        virtual void foo() override {}
      };
    }

    {
      class Base {
      public:
        virtual void foo() {}
        virtual void bar() {}
      };

      class Derived1 : public Base {
      public:
        // for readability should also use the virtual keyword
        virtual void foo() override {}

        // Error, no Base::bar(char const)
        // virtual void bar(char const c) override {}
      };

      // Use the final special identifier after the declarator part of a virtual function
      // declaration or definition to prevent further overrides in a derived class.
      class Derived2 : public Derived1 {
        virtual void foo() final {}
      };

      class Derived3 : public Derived2 {
        // Error, Derived2::foo() is final.
        // virtual void foo() override {}
      };

      // Use the final special identifier after the declarator part of a virtual function
      // declaration or definition to prevent further overrides in a derived class.

      class Derived4 final : public Derived1 {
        virtual void foo() override {}
      };

      // Error, whole class Derived4 is final.
      // class Derived5 : public Derived4 { };
    }

    {
      // override and final keywords are special identifiers having a meaning only in a
      // member function declaration or definition. They are not reserved keywords and can
      // still be used elsewhere in a program as user-defined identifiers.
      class foo {
        int final = 0;
        void override() {}
      };
    }
  }
} // namespace recipe_1_07
