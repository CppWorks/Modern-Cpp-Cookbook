#pragma once

#include <iostream>
#include <regex>
#include <string>

// The regular expression library also supports text replacement based on regular
// expressions. In this recipe, we will see how to use std::regex_replace.

namespace recipe_2_11 {
  using namespace std::string_literals;

  void execute()
  {
    std::cout
      << "\nRecipe 2.11: Replacing the content of a string using regular expressions."
      << "\n-------------------------------------------------------------------------\n";

    {
      //  Use the std::regex_replace() algorithm with a replacement string as the third
      //  argument. Consider this example: replace all words composed of exactly three
      //  characters that are either a, b, or c with three hyphens.

      std::cout << "Replace three-character words with three hyphens:\n";
      auto text{ "abc aa bca ca bbbb"s };
      auto rx = std::regex{ R"(\b[a|b|c]{3}\b)"s };
      auto newtext = std::regex_replace(text, rx, "---"s);

      std::cout << text << "\n" << newtext << std::endl;
    }

    {
      std::cout
        << "\nReplace three-character words with three hyphens with format_first_only:\n";
      auto text{ "abc aa bca ca bbbb"s };
      auto rx = std::regex{ R"(\b[a|b|c]{3}\b)"s };
      auto newtext
        = std::regex_replace(text, rx, "---"s, std::regex_constants::format_first_only);

      std::cout << text << "\n" << newtext << std::endl;
    }

    {
      std::cout << "\nRemove coma and exchange names:\n";
      auto text{ "bancila, marius"s };
      auto rx = std::regex{ R"((\w+),\s*(\w+))"s };

      // $& indicates the entire match.
      // $1, $2, $3, and so on, indicate the first, second, third submatch, and so on.
      // $` indicates the part of the string before the first match.
      // $' indicates the part of the string after the last match.
      auto newtext = std::regex_replace(text, rx, "$2 $1"s);

      std::cout << text << "\n" << newtext << std::endl;
    }

    {
      std::cout << "\nReplace a with an before vowels:\n";
      auto text{ "this is a example with a error"s };
      auto rx = std::regex{ R"(\ba ((a|e|i|u|o)\w+))"s };
      auto newtext = std::regex_replace(text, rx, "an $1");

      std::cout << text << "\n" << newtext << std::endl;
    }

    {
      std::cout << "\nExtract dates:\n";
      auto text{ "today is 1.06.2016!!"s };
      auto rx = std::regex{ R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{4}))"s };
      auto newtext1 = std::regex_replace(text, rx, R"($5$4$3$2$1)");
      auto newtext2 = std::regex_replace(text, rx, R"([$`][$&][$'])");

      std::cout << text << "\n" << newtext1 << "\n" << newtext2 << std::endl;
    }
  }
}
