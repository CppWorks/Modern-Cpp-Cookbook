#pragma once

// C++ standard provides a container called std::bitset for fixed-size sequences of bits.

// A bitset represents a fixed-size sequence of bits, with the size defined at compile
// time.

// The standard std::bitset class is intended as a C++ alternative to this C-like working
// style with sets of bits. It enables us to write more robust and safer code because it
// abstracts the bit operations with member functions.

#include <bitset>
#include <iostream>
#include <string>
#include <vector>

namespace recipe_5_02 {
  using namespace std::string_literals;

#define BORDER_NONE 0x00
#define BORDER_LEFT 0x01
#define BORDER_TOP 0x02
#define BORDER_RIGHT 0x04
#define BORDER_BOTTOM 0x08

  struct border_flags {
    static const int left = 0;
    static const int top = 1;
    static const int right = 2;
    static const int bottom = 3;
  };

  void apply_style(unsigned int const style)
  {
    if (style & BORDER_BOTTOM) {
    }
  }

  // The bitset can be created from an integer and can convert its value to an integer
  // using the to_ulong() or to_ullong() methods. However, if the size of the bitset is
  // larger than the size of these numerical types and any of the bits beyond the size of
  // the requested numerical type is set to 1, then these methods throw an
  // std::overflow_error exception because the value cannot be represented on unsigned
  // long or unsigned long long.

  template <size_t N>
  std::vector<unsigned long> bitset_to_vectorulong(std::bitset<N> bs)
  {
    auto result = std::vector<unsigned long>{};
    auto const size = 8 * sizeof(unsigned long);
    auto const mask = std::bitset<N>{ static_cast<unsigned long>(-1) };

    auto totalbits = 0;
    while (totalbits < N) {
      auto value = (bs & mask).to_ulong();
      result.push_back(value);
      bs >>= size;
      totalbits += size;
    }

    return result;
  }

  void execute()
  {
    std::cout << "Recipe 5.02: Using bitset for fixed-size sequences of bits.\n"
              << "-----------------------------------------------------------\n\n";

    // construct
    std::cout << "To construct an std::bitset object, use one of the available constructors:\n";
    std::cout << "........................................................................\n";
    {
      std::cout << "\nAn empty bitset with all bits set to 0:\n";
      std::bitset<8> b1; // [0,0,0,0,0,0,0,0]
      std::cout << b1 << std::endl;

      std::cout << "\nA bitset from a numerical value:\n";
      std::bitset<8> b2{ 10 }; // [0,0,0,0,1,0,1,0]
      std::cout << b2 << std::endl;

      std::cout << "\nA bitset from a string of '0' and '1':\n";
      std::bitset<8> b3{ "1010"s }; // [0,0,0,0,1,0,1,0]
      std::cout << b3 << std::endl;

      std::cout << "\nA bitset from a string containing any two characters representing '0' and '1'\n";
      std::bitset<8> b4{ "ooooxoxo"s, 0, std::string::npos, 'o', 'x' };
      std::cout << b4 << std::endl;
    }

    std::cout << "\nTo test individual bits in the set or the entire set for specific values.\n";
    std::cout << ".........................................................................\n";
    // element access
    {
      std::cout << "\ncount() to get the number of bits set to 1: ";
      std::bitset<8> bs{ 10 };
      std::cout << "has " << bs.count() << " 1s" << std::endl;

      std::cout << "\nany() to check whether there is at least one bit set to 1: ";
      if (bs.any())
        std::cout << "has some 1s" << std::endl;
      else
        std::cout << "has only 0s" << std::endl;

      std::cout << "\nall() to check whether all the bits are set to 1: ";
      if (bs.all())
        std::cout << "has only 1s" << std::endl;
      else
        std::cout << "has at least one 0" << std::endl;

      std::cout << "\nnone() to check whether all the bits are set to 0: ";
      if (bs.none())
        std::cout << "has no 1s" << std::endl;
      else
        std::cout << "has 1s" << std::endl;

      std::cout << "\ntest() to check the value of an individual bit: ";
      if (!bs.test(0))
        std::cout << "even" << std::endl;
      else
        std::cout << "odd" << std::endl;

      std::cout << "\noperator[] to access and test individual bits: ";
      if (!bs[0])
        std::cout << "even" << std::endl;
      else
        std::cout << "odd" << std::endl;
    }

    std::cout << "\nTo modify the content of a bitset.\n";
    std::cout << "..................................\n";
    // modifiers
    {
      std::bitset<8> b1{ 42 }; // [0,0,1,0,1,0,1,0]
      std::bitset<8> b2{ 11 }; // [0,0,0,0,1,0,1,1]
      std::cout << b1 << std::endl;
      std::cout << b2 << std::endl;

      std::cout << "\nMember operators |=, &=, ^= , and ~ to perform binary or, and, "
                   "xor, and not operations, or non-member operators |, &, and ^:\n";

      auto b3 = b1 | b2; // [0,0,1,0,1,0,1,1]
      auto b4 = b1 & b2; // [0,0,0,0,1,0,1,0]
      auto b5 = b1 ^ b2; // [1,1,0,1,1,1,1,0]
      auto b6 = ~b1;     // [1,1,0,1,0,1,0,1]
      std::cout << b3 << std::endl;
      std::cout << b4 << std::endl;
      std::cout << b5 << std::endl;
      std::cout << b6 << std::endl;

      std::cout << "\nMember operators <<=, <<, >>=, >> to perform shifting operations:\n";
      auto b7 = b1 << 2; // [1,0,1,0,1,0,0,0]
      auto b8 = b1 >> 2; // [0,0,0,0,1,0,1,0]
      std::cout << b7 << std::endl;
      std::cout << b8 << std::endl;

      std::cout << "\nflip() to toggle the entire set or an individual bit from 0 to 1 or from 1 to 0:\n";
      b1.flip();        // [1,1,0,1,0,1,0,1]
      std::cout << b1 << std::endl;
      b1.flip(0);       // [1,1,0,1,0,1,0,0]
      std::cout << b1 << std::endl;
      std::cout << "\nset() to change the entire set or an individual bit to true or the specified value:\n";
      b1.set(0, true);  // [1,1,0,1,0,1,0,1]
      std::cout << b1 << std::endl;
      b1.set(0, false); // [1,1,0,1,0,1,0,0]
      std::cout << b1 << std::endl;
      std::cout << "\nreset() to change the entire set or an individual bit to false:\n";
      b1.reset(2);      // [1,1,0,1,0,0,0,0]
      std::cout << b1 << std::endl;
    }
    std::cout << "\nTo convert a bitset to a numerical or string value.\n";
    std::cout << "...................................................\n";
    // conversion
    {
      std::bitset<8> bs{ 42 };
      std::cout << bs << std::endl;

      std::cout << "\nto_ulong() and to_ullong() to convert to unsigned long or unsigned long long:\n";
      auto n1 = bs.to_ulong();  // n1 = 42UL
      auto n2 = bs.to_ullong(); // n2 = 42ULL
      std::cout << n1 << std::endl;
      std::cout << n2 << std::endl;

      std::cout << "\nto_string() to convert to std::basic_string; by default the result is a string containing '0' and '1', but you can specify a different character for these two values:\n";
      auto s1 = bs.to_string();         // s1 = "00101010"
      auto s2 = bs.to_string('o', 'x'); // s2 = "ooxoxoxo"
      std::cout << s1 << std::endl;
      std::cout << s2 << std::endl;
    }

    std::cout << "\nConvert C-like style code into C++-like style code.\n";
    std::cout << "...................................................\n";
    std::cout << "Please check source code.\n\n";
    // C-like style
    {
      // initialize with no flags
      unsigned int style = BORDER_NONE;
      // set a flag
      style = BORDER_BOTTOM;
      // add more flags
      style |= BORDER_LEFT | BORDER_RIGHT | BORDER_TOP;
      // remove some flags
      style &= ~BORDER_LEFT;
      style &= ~BORDER_RIGHT;
      // test if a flag is set
      if ((style & BORDER_BOTTOM) == BORDER_BOTTOM) {
      }
      // pass the flags as argument to a function
      apply_style(style);
    }

    // C++ style
    {
      // initialize with no flags
      std::bitset<4> style;
      // set a flag
      style.set(border_flags::bottom);
      // set more flags
      style.set(border_flags::left).set(border_flags::top).set(border_flags::right);
      // remove some flags
      style[border_flags::left] = 0;
      style.reset(border_flags::right);
      // test if a flag is set
      if (style.test(border_flags::bottom)) {
      }
      // pass the flags as argument to a function
      apply_style(style.to_ulong());
    }

    std::cout << "\nConverting huge bitsets requires special handling.\n";
    std::cout << "..................................................\n";
    {
      std::bitset<128> bs = (std::bitset<128>(0xFEDC) << 96)
        | (std::bitset<128>(0xBA98) << 64) | (std::bitset<128>(0x7654) << 32)
        | std::bitset<128>(0x3210);

      std::cout << bs << std::endl;

      auto result = bitset_to_vectorulong(bs);
      for (auto const v : result)
        std::cout << std::hex << v << std::endl;

      std::cout << std::dec;
    }
  }
}
