#pragma once
#include <iostream>

// This recipe explores the alignas specifier for controlling the alignment requirements
// and the alignof operator that retrieves the alignment requirements of a type.

namespace recipe_1_05 {
  // The alignment matches the size of the largest member.

  // size = 1, alignment = 1
  struct foo1 {
    char a;
  };

  // size = 2, alignment = 1
  struct foo2 {
    char a;
    char b;
  };

  // size = 8, alignment = 4
  // The alignment of members of this structure is done at addresses that are multiples
  // of 4.
  struct foo3 {
    char a;
    int b;
  };

  // This is what the compiler actually does to achieve that. Padding!
  struct foo3_ {
    char a;        // 1 byte
    char _pad0[3]; // 3 bytes padding to put b on a 4-byte boundary
    int b;         // 4 bytes
  };

  // size = 32, alignment = 8 (for the double)
  struct foo4 {
    int a;
    char b;
    float c;
    double d;
    bool e;
  };

  // I think there would be padding between a and b.
  struct foo4_ {
    int a;         // 4 bytes
    char b;        // 1 byte
    char _pad0[3]; // 3 bytes padding to put c on a 8-byte boundary
    float c;       // 4 bytes
    char _pad1[4]; // 4 bytes padding to put d on a 8-byte boundary
    double d;      // 8 bytes
    bool e;        // 1 byte
    char _pad2[7]; // 7 bytes padding to make sizeof struct multiple of 8
  };

  void execute()
  {
    std::cout << "\nRecipe 1.05: Controlling and querying object alignment.\n"
              << "-------------------------------------------------------\n";
    {
      struct alignas(4) foo {
        char a;
        char b;
      };

      struct foo_ {
        char a;
        char b;
        char _pad0[2];
      };
    }

    {
      struct alignas(8) foo {
        alignas(2) char a;
        alignas(8) int b;
      };

      struct foo_ {
        char a;
        char _pad0[7];
        int b;
        char _pad1[4];
      };

      {
        alignas(8) int a;
        alignas(256) long b[4];

        printf("%p\n", &a); // eg. 0000006C0D9EF908
        printf("%p\n", &b); // eg. 0000006C0D9EFA00
      }
    }
  }
} // namespace recipe_1_05
