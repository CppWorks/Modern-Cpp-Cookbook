#pragma once

#include <iostream>
#include <string>

// To avoid escaping characters, C++11 introduced raw string literals that do not process
// escape sequences. What you see is what you get.

// To avoid escaping characters, define the string literals with the following:

// 1. Use R"( literal )" as the default form.
// 2. Use R"delimiter( literal )delimiter" where delimiter is any character sequence not
// present in the actual string when the sequence )" should actually be part of the
// string.

// The s suffix is to define basic_string literals.

namespace recipe_2_07 {
  void execute()
  {
    std::cout
      << "\nRecipe 2.07: Using raw string literals to avoid escaping characters."
      << "\n--------------------------------------------------------------------\n\n";

    using namespace std::string_literals;

    {
      std::cout << "Without raw strings:\n\n";

      auto filename{ "C:\\Users\\Marius\\Documents\\"s };

      auto pattern{ "(\\w+)=(\\d+)$"s };

      auto sqlselect{ "SELECT *\n\
FROM Books\n\
WHERE Publisher=\'Paktpub\'\n\
ORDER BY PubDate DESC"s };

      std::cout << filename << std::endl;
      std::cout << pattern << std::endl;
      std::cout << sqlselect << std::endl;
      std::cout << "---------------------------------------------------\n";
    }

    {
      std::cout << "With raw strings:\n\n";

      auto filename{ R"(C:\Users\Marius\Documents\)"s };

      auto pattern{ R"((\w+)=(\d+)$)"s };

      auto sqlselect{
        R"(SELECT *
FROM Books
WHERE Publisher='Paktpub'
ORDER BY PubDate DESC)"s
      };
      std::cout << filename << std::endl;
      std::cout << pattern << std::endl;
      std::cout << sqlselect << std::endl;
      std::cout << "---------------------------------------------------\n\n";
    }

    {
      auto filename1{ R"(C:\Users\Marius\Documents\)"s };
      auto filename2{ R"(C:\\Users\\Marius\\Documents\\)"s };

      // prints "C:\Users\Marius\Documents\"
      std::cout << filename1 << std::endl;

      // prints "C:\\Users\\Marius\\Documents\\"
      std::cout << filename2 << std::endl;

      auto text{ R"!!(This text contains both "( and )".)!!"s };
      std::cout << text << std::endl;
    }

    {
      // Raw string literals can be prefixed by one of L, u8, u, and U to indicate a wide,
      // UTF-8, UTF-16, or UTF-32 string literal.

      auto t1{ LR"(text)" };  // const wchar_t*
      auto t2{ u8R"(text)" }; // const char*
      auto t3{ uR"(text)" };  // const char16_t*
      auto t4{ UR"(text)" };  // const char32_t*

      auto t5{ LR"(text)"s };  // wstring
      auto t6{ u8R"(text)"s }; // string
      auto t7{ uR"(text)"s };  // u16string
      auto t8{ UR"(text)"s };  // u32string
    }
  }
}
