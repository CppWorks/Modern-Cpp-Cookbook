#pragma once

#include <iostream>

//  The raw form, in which the literal is not parsed by the compiler, is only available
//  for integral and floating-point types.

namespace recipe_2_06 {
  // To exemplify the way raw user-defined literals can be created, we will define binary
  // literals. These binary literals can be of 8-bit, 16-bit, and 32-bit (unsigned) types.
  // These types will be called byte8, byte16, and byte32, and the literals we create will
  // be called _b8, _b16, and _b32.

  namespace binary {
    using byte8 = unsigned char;
    using byte16 = unsigned short;
    using byte32 = unsigned int;

    // 1. Define your literals in a separate namespace to avoid name clashes.
    namespace binary_literals {
      // The templates are defined in yet another nested namespace, called
      // binary_literals_internals. This is also a good practice because it hides (without
      // proper qualification) the implementation details from the client.

      // If we consider the literal 1010_b8, then the literal operator template would be
      // instantiated as operator"" _b8<'1', '0', '1', '0'>().
      namespace binary_literals_internals {
        // The binary_struct class template has a template type CharT for the return type
        // of the function (we need this because our literal operator templates should
        // return either byte8, byte16, or byte32)
        template <typename CharT, char... bits>
        struct binary_struct;

        template <typename CharT, char... bits>
        struct binary_struct<CharT, '0', bits...> {
          // For '0' don't do anything. Just recurse.
          static constexpr CharT value{ binary_struct<CharT, bits...>::value };
        };

        template <typename CharT, char... bits>
        struct binary_struct<CharT, '1', bits...> {
          // For '1' shift to the left to get the actual value and or with the existing
          // value.
          static constexpr CharT value{ static_cast<CharT>(1 << sizeof...(bits))
                                        | binary_struct<CharT, bits...>::value };
        };

        template <typename CharT>
        struct binary_struct<CharT> {
          // For empty bits the value is 0. Recursion ends here.
          static constexpr CharT value{ 0 };
        };
      }

      // 2. Always prefix the used-defined suffix with an underscore.
      // 3. Define a literal operator or literal operator template of the following form:
      template <char... bits>
      constexpr byte8 operator""_b8()
      {
        static_assert(sizeof...(bits) <= 8,
                      "binary literal b8 must be up to 8 digits long");

        return binary_literals_internals::binary_struct<byte8, bits...>::value;
      }

      template <char... bits>
      constexpr byte16 operator""_b16()
      {
        static_assert(sizeof...(bits) <= 16,
                      "binary literal b16 must be up to 16 digits long");

        return binary_literals_internals::binary_struct<byte16, bits...>::value;
      }

      template <char... bits>
      constexpr byte32 operator""_b32()
      {
        static_assert(sizeof...(bits) <= 32,
                      "binary literal b32 must be up to 32 digits long");

        return binary_literals_internals::binary_struct<byte32, bits...>::value;
      }
    }
  }

  void execute()
  {
    std::cout << "\nRecipe 2.06: Creating raw user-defined literals."
              << "\n------------------------------------------------\n";

    using namespace binary;
    using namespace binary_literals;

    auto b1 = 1010_b8;
    auto b2 = 101010101010_b16;
    auto b3 = 010101010101010101010101_b32;

    // b1 outputs newline (b1 is char with value 10 = carriage return)
    std::cout << "b1: " << b1 << std::endl;
    std::cout << "b2: " << b2 << std::endl;
    std::cout << "b3: " << b3 << std::endl;

    // binary literal b8 must be up to 8 digits long
    // auto b4 = 0011111111_b8;

    // binary literal b16 must be up to 16 digits long
    // auto b5 = 001111111111111111_b16;

    // binary literal b32 must be up to 32 digits long
    // auto b6 = 0011111111111111111111111111111111_b32;
  }
}
