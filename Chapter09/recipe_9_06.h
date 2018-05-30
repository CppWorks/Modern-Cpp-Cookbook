#pragma once

// std::unique_ptr: a smart pointer that owns and manages another object or an array of
// objects allocated on the heap and performs the disposal operation when the smart
// pointer goes out of scope.

// unique_ptr is a smart pointer that manages an object or an array allocated on the heap
// through a raw pointer, performing an appropriate disposal when the smart pointer goes
// out of scope, is assigned a new pointer with operator=, or it gives up ownership using
// the release() method. By default, operator delete is used to dispose of the managed
// object. However, the user may supply a custom deleter when constructing the smart
// pointer.

#include <cassert>
#include <iomanip>
#include <iostream>
// The unique_ptr class is available in the std namespace in the <memory> header.
#include <memory>
#include <string>
#include <vector>

namespace recipe_9_06 {
  class foo {
    int a;
    double b;
    std::string c;

  public:
    foo(int const a = 0, double const b = 0, std::string const& c = "")
      : a(a)
      , b(b)
      , c(c)
    {
    }

    void print() const
    {
      std::cout << '(' << a << ',' << b << ',' << std::quoted(c) << ')' << std::endl;
    }
  };

  struct foo_deleter {
    void operator()(foo* pf) const
    {
      std::cout << "Deleting foo..." << std::endl;
      delete pf;
    }
  };

  void func(int* ptr)
  {
    if (ptr != nullptr)
      std::cout << *ptr << std::endl;
    else
      std::cout << "null" << std::endl;
  }

  void some_function(std::unique_ptr<foo> p) {}

  void some_other_function(std::unique_ptr<foo> p, int const v) {}

  int function_that_throws()
  {
    throw std::runtime_error("not implemented");
  }

  struct Base {
    virtual ~Base()
    {
      std::cout << "~Base()" << std::endl;
    }
  };

  struct Derived : public Base {
    virtual ~Derived()
    {
      std::cout << "~Derived()" << std::endl;
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 9.06: Using unique_ptr to uniquely own a memory resource."
              << "\n----------------------------------------------------------------\n";

    {
      std::cout << "Overloaded constructors to create an unique_ptr:\n";

      // Use the available overloaded constructors to create an unique_ptr that manages
      // objects or an array of objects through a pointer. The default constructor creates
      // a pointer that does not manage any object:

      std::unique_ptr<int> pnull;
      std::unique_ptr<int> pi(new int(42));
      std::unique_ptr<int[]> pa(new int[3]{ 1, 2, 3 });
      std::unique_ptr<foo> pf(new foo(42, 42.0, "42"));
    }

    {
      std::cout << "\nUse std::make_unique():\n";

      // Alternatively, use the std::make_unique() function template, available in C++14,
      // to create unique_ptr objects:

      std::unique_ptr<int> pi = std::make_unique<int>(42);
      std::unique_ptr<int[]> pa = std::make_unique<int[]>(3);
      std::unique_ptr<foo> pf = std::make_unique<foo>(42, 42.0, "42");
    }

    {
      std::cout << "\nUse operator []:\n";

      // If a unique_ptr manages an array of objects, operator[] can be used to access
      // individual elements of the array:

      std::unique_ptr<int[]> pa = std::make_unique<int[]>(3);
      for (int i = 0; i < 3; ++i)
        pa[i] = i + 1;

      for (int i = 0; i < 3; ++i)
        std::cout << pa[i] << std::endl;

      // allocate and initialize an array, not possible with std::make_unique
      std::unique_ptr<int[]> pa1(new int[3]{ 1,2,3 });
    }

    {
      std::cout << "\nConvert unique pointer to bool:\n";

      // To check whether unique_ptr can manage an object or not, use the explicit
      // operator bool or check whether get() != nullptr (which is what operator bool
      // does):

      std::unique_ptr<int> pnull;
      if (pnull)
        std::cout << "not null" << std::endl;

      std::unique_ptr<int> pi(new int(42));
      if (pi)
        std::cout << "not null" << std::endl;
    }

    {
      std::cout << "\nUse std::move() to transfert ownership:\n";

      // Use std::move() to transfer the ownership of an object from one unique_ptr to
      // another:

      auto pi = std::make_unique<int>(42);

      auto qi = std::move(pi);
      assert(pi.get() == nullptr);
      assert(qi.get() != nullptr);
    }

    {
      std::cout << "\nDerefence with operator* and operator->:\n";

      // Dereference the pointer to the managed object using operator* and operator->:

      auto pi = std::make_unique<int>(42);
      *pi = 21;

      auto pf1 = std::make_unique<foo>();
      pf1->print();

      auto pf2 = std::make_unique<foo>(42, 42.0, "42");
      pf2->print();
    }

    {
      std::cout << "\nunique_ptr can be stored in containers:\n";

      // unique_ptr objects can be stored in a container. Objects returned by
      // make_unique() can be stored directly. A lvalue object could be statically
      // converted into an rvalue object with std::move() if you want to give up the
      // ownership of the managed object to the unique_ptr object in the container:

      std::vector<std::unique_ptr<foo>> data;
      for (int i = 0; i < 5; i++)
        data.push_back(std::make_unique<foo>(i, i, std::to_string(i)));

      auto pf = std::make_unique<foo>(42, 42.0, "42");

      // unique_ptr can be stored in containers, such as std::vector. Because only one
      // unique_ptr object can own the managed object at any point, the smart pointer
      // cannot be copied to the container; it has to be moved:
      data.push_back(std::move(pf));

      for (auto const& p : data)
        p->print();
    }

    {
      std::cout << "\nUse get() to access raw pointer:\n";

      // To access the raw pointer to the managed object, use get() if you want to retain
      // ownership of the object or release() if you want to release the ownership as
      // well:

      std::unique_ptr<int> pi;
      func(pi.get());

      pi = std::make_unique<int>(42);
      func(pi.get());
    }

    {
      std::cout << "\nUse custom deleter:\n";

      // Use the overloaded constructor that takes a custom deleter if the default delete
      // operator is not appropriate for destroying the managed object or array. Not
      // possible with std::make_unique:

      std::unique_ptr<foo, foo_deleter> pf(new foo(42, 42.0, "42"), foo_deleter());
    }

    {
      some_function(std::unique_ptr<foo>(new foo()));
      some_function(std::make_unique<foo>());
    }

    {
      std::cout << "\nUse try...catch when using unique pointers:\n";

      try {
        some_other_function(std::unique_ptr<foo>(new foo()), function_that_throws());
      } catch (...) {
        std::cout << "unique_ptr() throws.\n";
      }

      try {
        some_other_function(std::make_unique<foo>(), function_that_throws());
      } catch (...) {
        std::cout << "make_unique() throws.\n";
      }
    }

    {
      std::cout << "\nImplicit conversion from Derived to Base class:\n";

      // A unique_ptr that manages the object of a Derived class can be implicitly
      // converted into a unique_ptr that manages an object of class Base if Derived is
      // derived from Base. This implicit conversion is safe only if Base has a virtual
      // destructor (as all base classes should have); otherwise, undefined behavior is
      // employed:

      std::unique_ptr<Derived> pd = std::make_unique<Derived>();
      std::unique_ptr<Base> pb = std::move(pd);
    }
  }
}
