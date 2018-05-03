// The C++11 standard has introduced a new type of namespace called inline namespaces that
// are basically a mechanism that makes declarations from a nested namespace look and act
// like they were part of the surrounding namespace. Inline namespaces are declared using
// the inline keyword in the namespace declaration (unnamed namespaces can also be
// inlined). This is a helpful feature for library versioning.

// A member of an inline namespace is treated as if it was a member of the surrounding
// namespace. Such a member can be partially specialized, explicitly instantiated, or
// explicitly specialized. This is a transitive property, which means that if a namespace
// A contains an inline namespace B that contains an inline namespace C, then the members
// of C appear as they were members of both B and A and the members of B appear as they
// were members of A.

#pragma once

#include <iostream>

    // To provide multiple versions of a library and let the user decide what version to
    // use, do the following:

    // 1. Define the content of the library inside a namespace.
    // 2. Define each version of the library or parts of it inside an inner inline
    // namespace.
    // 3. Use preprocessor macros and #if directives to enable a particular version of the
    // library.

    namespace recipe_1_12 {
  // 1.
  namespace modernlib {
    // 3.
#ifndef LIB_VERSION_2
    // 2.
    inline namespace version_1 {
      template <typename T>
      int test(T value)
      {
        return 1;
      }
    } // namespace version_1
#endif

    // 3.
#ifdef LIB_VERSION_2
    // 2.
    inline namespace version_2 {
      template <typename T>
      int test(T value)
      {
        return 2;
      }
    } // namespace version_2
#endif
  }

  namespace client {
    struct foo {
      int a;
    };

  } // namespace client

  // The client sees just namespace modernlib, does not know of the inlined namespaces.
  // Client code does not break with more versions of the same library.
  namespace modernlib {
    // Client creates a specialization fpr the test template.
    template <>
    int test(client::foo value)
    {
      return value.a;
    }
  } // namespace modernlib

  namespace client {
    void execute()
    {
      std::cout << "\nRecipe 1.12: Using inline namespaces for symbol versioning."
                << "\n-----------------------------------------------------------\n";

      auto y = modernlib::test(foo{ 42 });
    }
  } // namespace client
} // namespace recipe_1_12
