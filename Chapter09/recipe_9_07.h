#pragma once

// The C++ standard provides another smart pointer, called std::shared_ptr; it is similar
// to std::unique_ptr in many ways, but the difference is that it can share the ownership
// of an object or array with other std::shared_ptr.

#include <cassert>
#include <iomanip>
#include <iostream>
// Both the shared_ptr and weak_ptr classes, as well as the make_shared() function
// template, are available in the std namespace in the <memory> header.
#include <memory>
#include <string>
#include <vector>

namespace recipe_9_07 {

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
      std::cout << "deleting foo..." << std::endl;
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

    void print()
    {
      std::cout << "Derived" << std::endl;
    }
  };

  struct Apprentice;

  struct Master : std::enable_shared_from_this<Master> {
    ~Master()
    {
      std::cout << "~Master" << std::endl;
    }

    void take_apprentice(std::shared_ptr<Apprentice> a);

  private:
    std::shared_ptr<Apprentice> apprentice;
  };

  struct Apprentice {
    ~Apprentice()
    {
      std::cout << "~Apprentice" << std::endl;
    }

    void take_master(std::weak_ptr<Master> m);

  private:
    std::weak_ptr<Master> master;
  };

  void Master::take_apprentice(std::shared_ptr<Apprentice> a)
  {
    apprentice = a;
    apprentice->take_master(shared_from_this());
  }

  void Apprentice::take_master(std::weak_ptr<Master> m)
  {
    master = m;
  }

  void execute()
  {
    std::cout << "\nRecipe 9.07: Using shared_ptr to share a memory resource."
              << "\n---------------------------------------------------------\n";

    // constructors
    {
      std::cout << "shared_ptr constructors:\n";

      // Use one of the available overloaded constructors to create a shared_ptr that
      // manages an object through a pointer. The default constructor creates an empty
      // shared_ptr which does not manage any object:

      std::shared_ptr<int> pnull1;
      std::shared_ptr<int> pnull2(nullptr);
      std::shared_ptr<int> pi1(new int(42));
      std::shared_ptr<int> pi2 = pi1;

      assert(pi1.use_count() == 2);

      std::shared_ptr<foo> pf1(new foo());
      pf1->print();

      std::shared_ptr<foo> pf2(new foo(42, 42.0, "42"));
      pf2->print();
    }

    // make_shared
    {
      std::cout << "\nUse make_shared() alternatively:\n";

      // Alternatively, use the std::make_shared() function template, available since
      // C++11, for creating shared_ptr objects:

      std::shared_ptr<int> pi = std::make_shared<int>(42);
      std::shared_ptr<foo> pf1 = std::make_shared<foo>();
      pf1->print();
      std::shared_ptr<foo> pf2 = std::make_shared<foo>(42, 42.0, "42");
      pf2->print();
    }

    // custom deleter
    {
      std::cout << "\nUse custom deleter:\n";

      // Use the overloaded constructor that takes a custom deleter if the default delete
      // operation is not appropriate for destroying the managed object:

      std::shared_ptr<foo> pf1(new foo(42, 42.0, "42"), foo_deleter());

      std::shared_ptr<foo> pf2(new foo(42, 42.0, "42"), [](auto p) {
        std::cout << "deleting foo from lambda..." << std::endl;
        delete p;
      });
    }

    // arrays
    {
      std::cout << "\nDefine a deleter for arrays:\n";

      // Always specify a deleter when managing an array of objects. The deleter can
      // either be a partial specialization of std::default_delete for arrays or any
      // function that takes a pointer to the template type:

      std::shared_ptr<int> pa1(new int[3]{ 1, 2, 3 }, std::default_delete<int[]>());

      std::shared_ptr<int> pa2(new int[3]{ 1, 2, 3 }, [](auto p) { delete[] p; });
    }

    // dereferencing
    {
      std::cout << "\nDereference smart pointer with * and ->\n";

      // Dereference the pointer to the managed object using operator* and operator->:

      std::shared_ptr<int> pi = std::make_shared<int>(42);
      *pi = 21;

      std::shared_ptr<foo> pf = std::make_shared<foo>(42, 42.0, "42");
      pf->print();
    }

    // empty check
    {
      std::cout << "\nImplicit converstion to bool:\n";

      // To check whether a shared_ptr could manage an object or not, use the explicit
      // operator bool or check whether get() != nullptr (which is what operator bool
      // does):

      std::shared_ptr<int> pnull;
      if (pnull)
        std::cout << "not null" << std::endl;

      std::shared_ptr<int> pi(new int(42));
      if (pi)
        std::cout << "not null" << std::endl;
    }

    // get
    {
      std::cout << "\nUse get() to access raw pointer:\n";

      // To access the raw pointer to the managed object, use the get() function:

      std::shared_ptr<int> pi;
      func(pi.get());

      pi = std::make_shared<int>(42);
      func(pi.get());
    }

    // container storing
    {
      std::cout << "\nStore shared pointers in containers:\n";

      // shared_ptr objects can be stored in containers, such as std::vector:

      std::vector<std::shared_ptr<foo>> data;
      for (int i = 0; i < 5; i++)
        data.push_back(std::make_shared<foo>(i, i, std::to_string(i)));

      auto pf = std::make_shared<foo>(42, 42.0, "42");

      data.push_back(std::move(pf));
      assert(!pf);

      for (auto const& p : data)
        p->print();
    }

    // conversion
    {
      std::shared_ptr<Derived> pd = std::make_shared<Derived>();
      std::shared_ptr<Base> pb = pd;

      std::static_pointer_cast<Derived>(pb)->print();
    }

    // weak pointer
    {
      std::cout << "\nweak_ptr():\n";

      // Use weak_ptr to maintain a non-owning reference to a shared object, which can be
      // later accessed through a shared_ptr constructed from the weak_ptr object:

      auto sp1 = std::make_shared<int>(42);
      assert(sp1.use_count() == 1);

      std::weak_ptr<int> wpi = sp1;
      assert(sp1.use_count() == 1);

      auto sp2 = wpi.lock();
      assert(sp1.use_count() == 2);
      assert(sp2.use_count() == 2);

      sp1.reset();
      assert(sp1.use_count() == 0);
      assert(sp2.use_count() == 1);
    }

    // enable_shared_from_this
    {
      std::cout << "\nUse std::enable_shared_from_this:\n";

      // Use the std::enable_shared_from_this class template as the base class for a type
      // when you need to create shared_ptr objects for instances that are already managed
      // by another shared_ptr object:

      auto m = std::make_shared<Master>();
      auto a = std::make_shared<Apprentice>();

      m->take_apprentice(a);
    }
  }
}
