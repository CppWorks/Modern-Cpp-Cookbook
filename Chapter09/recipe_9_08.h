#pragma once

// Move semantics are a key feature that drives the performance improvements of modern
// C++. However, it requires that classes implement a move constructor and assignment
// operator. These are provided by the compiler in some circumstances, but in practice, it
// is often the case that you have to explicitly write them.

// The move constructor and move assignment operator are provided by default by the
// compiler unless a user-defined copy constructor, move constructor, copy assignment
// operator, move assignment operator, or destructor exists already.

// An rvalue is an object that does not have a name; it lives temporarily during the evaluation of an expression and is destroyed at the next semicolon:
// T a;
// T b = a;
// T c = a + b;

// In the preceding example, a, b, and c are lvalues; they are objects that have a name
// which can be used to refer to the object at any point throughout its lifetime. On the
// other hand, when you evaluate the expression a+b, the compiler creates a temporary
// object (which, in this case, is assigned to c) and then destroyed (when a semicolon is
// encountered). These temporary objects are called rvalues because they usually appear on
// the right-hand side of an assignment expression. In C++11, we can refer to these
// objects through rvalue references, expressed with &&.

// Move semantics are important in the context of rvalues. This is because they allow you
// to take ownership of the resources from the temporary object that is destroyed without
// the client being able to use it after the move operation is completed. On the other
// hand, lvalues cannot be moved; they can only be copied. This is because they can be
// accessed after the move operation, and the client expects the object to be in the same
// state.

// The move constructor is different than a copy constructor because it takes an rvalue
// reference to the class type T(T&&), as opposed to an lvalue reference in the case of
// the copy constructor T(T const&). Similarly, move assignment takes an rvalue reference,
// namely T& operator=(T&&), as opposed to an lvalue reference for the copy assignment
// operator, namely T& operator=(T const &).

#include <algorithm>
#include <iostream>
#include <vector>

namespace recipe_9_08 {
  class Buffer {
    unsigned char* ptr;
    size_t length;

  public:
    Buffer()
      : ptr(nullptr)
      , length(0)
    {
      std::cout << "Default constructor.\n";
    }

    explicit Buffer(size_t const size)
      : ptr(new unsigned char[size]{ 0 })
      , length(size)
    {
      std::cout << "Explicit constructor.\n";
    }

    ~Buffer()
    {
      delete[] ptr;
    }

    Buffer(Buffer const& other)
      : ptr(new unsigned char[other.length])
      , length(other.length)
    {
      std::cout << "Copy constructor.\n";
      std::copy(other.ptr, other.ptr + other.length, ptr);
    }

    Buffer& operator=(Buffer const& other)
    {
      std::cout << "Assignment operator.\n";

      if (this != &other) {
        delete[] ptr;

        ptr = new unsigned char[other.length];
        length = other.length;

        std::copy(other.ptr, other.ptr + other.length, ptr);
      }

      return *this;
    }

    // To implement the move constructor for a class, do the following:
    // 1. Write a constructor that takes an rvalue reference to the class type:
    Buffer(Buffer&& other)
    {
      std::cout << "Move constructor.\n";

      // copy

      // 2. Assign all the data members from the rvalue reference to the current object. This
      // can be done either in the body of the constructor, as follows, or in the
      // initialization list, which is the preferred way:
      ptr = other.ptr;
      length = other.length;

      // reset

      // 3. Assign the data members from the rvalue reference to default values:
      other.ptr = nullptr;
      other.length = 0;
    }

    // Shorter version of a move constructor:

    // There are two points that must be noticed in this example:

    // Member initialization in the constructor's initialization list is necessary because
    // these members could potentially be used in the move assignment operator later on
    // (such as the ptr member in this example).

    // Static casting of other to an rvalue reference.Without this explicit conversion,
    // the copy assignment operator would be called.This is because even if an rvalue is
    // passed to this constructor as an argument, when it is assigned a name, it is bound
    // to an lvalue.Therefore, other is actually an lvalue, and it must be converted into
    // an rvalue reference in order to invoke the move assignment operator.

    // Buffer(Buffer&& other)
    //   :ptr(nullptr),length(0)
    // {
    //
    //  Implementing both the move constructor and move assignment operator involves
    //  writing similar code (the entire code of the move constructor was also
    //  present in the move assignment operator). This can actually be avoided by
    //  calling the move assignment operator in the move constructor:
    //
    //   *this = std::move(other);
    // }

    // To implement the move assignment operator for a class, do the following:
    // 1. Write an assignment operator that takes an rvalue reference to the class
    // type and returns a reference to it:
    Buffer& operator=(Buffer&& other)
    {
      std::cout << "Move assignment.\n";

      // 2. Check that the rvalue reference does not refer to the same object as this, and
      // if they are different, perform steps 3 to 5:
      if (this != &other) {
        // clean up existing resources

        // 3. Dispose all the resources (such as memory, handles, and so on) from the
        // current object:
        delete[] ptr;

        // copy

        // 4. Assign all the data members from the rvalue reference to the current object:
        ptr = other.ptr;
        length = other.length;

        // reset

        // 5. Assign the data members from the rvalue reference to default values:
        other.ptr = nullptr;
        other.length = 0;
      }
      // 6. Return a reference to the current object, regardless of whether steps 3 to 5 were executed or not:
      return *this;
    }

    size_t size() const
    {
      return length;
    }
    unsigned char* data() const
    {
      return ptr;
    }
  };

  void execute()
  {
    std::cout << "\nRecipe 9.08: Implementing move semantics."
              << "\n-----------------------------------------\n";

    {
      // When a move constructor/assignment operator exists, an rvalue is moved
      // automatically. lvalues can also be moved, but this requires an explicit static
      // cast to an rvalue reference. This can be done using the std::move() function,
      // which basically performs a static_cast<T&&>.

      // After an object is moved, it must remain in a valid state. However, there is no
      // requirement regarding what this state should be. For consistency, you should set
      // all member fields to their default value (numerical types to 0, pointers to
      // nullptr, booleans to false, and so on):

      std::vector<Buffer> c;    // (explict constructor?)
      c.push_back(Buffer(100)); // move (move constructor)

      Buffer b(200); // explicit constructor
      std::cout << (void*)b.data() << std::endl;
      c.push_back(b); // copy (copy constructor)

      std::cout << (void *)b.data() << std::endl;
      c.push_back(std::move(b)); // move (move constructor)
      std::cout << (void *)b.data() << std::endl;
    }

    {
      std::cout << "\nDifferent ways to construct and assign:\n";

      Buffer b1;                // default constructor
      Buffer b2(100);           // explicit constructor
      Buffer b3(b2);            // copy constructor
      b1 = b3;                  // assignment operator
      Buffer b4(std::move(b1)); // move constructor
      b3 = std::move(b4);       // move assignment
    }
  }
}
