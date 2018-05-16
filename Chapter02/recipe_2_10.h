#pragma once

#include <iostream>
#include <regex>
#include <string>

// In the previous recipe, we have looked at how to use std::regex_match() to verify that
// the content of a string matches a particular format. The library provides another
// algorithm called std::regex_search() that matches a regular expression against any part
// of a string, and not only the entire string as regex_match() does. This function,
// however, does not allow searching through all the occurrences of a regular expression
// in an input string. For this purpose, we need to use one of the iterator classes
// available in the library.

// For this purpose, we will consider the problem of parsing a text file containing
// name-value pairs.

// 1. To search for the first occurrence of a regular expression in a given text, use the
// general purpose algorithm std::regex_search().

// 2. To find all the occurrences of a regular expression in a given text, use the
// iterator std::regex_iterator.

// 3. To iterate through all the subexpressions of a match, use the iterator
// std::regex_token_iterator.

namespace recipe_2_10 {
  using namespace std::string_literals;

  void execute()
  {
    std::cout
      << "\nRecipe 2.10: Parsing the content of a string using regular expressions."
      << "\n-----------------------------------------------------------------------\n";

    auto text{
      R"(
# This is a commment
timeout=120
server = 127.0.0.1

#retrycount=3
)"s
    };

    // Original regexp doesn't work under Linux
    // auto rx = std::regex{ R"(^(?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*)$)"s };

    auto rx = std::regex{ R"((?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*))"s };

    {
      std::cout << "Using std::smatch:\n";
      auto match = std::smatch{};
      //  The submatch at index 0 is always the entire match.
      if (std::regex_search(text, match, rx)) {
        std::cout << match[1] << '=' << match[2] << std::endl;
      } else {
        std::cout << "No match\n";
      }
    }

    {
      std::cout << "\nUsing std::sregex_iterator:\n";
      // It allows not only iterating through all the matches, but also accessing all the
      // submatches of a match.
      auto end = std::sregex_iterator{};
      for (auto it = std::sregex_iterator{ std::begin(text), std::end(text), rx };
           it != end; ++it) {
        std::cout << '\'' << (*it)[1] << "\'=\'" << (*it)[2] << '\'' << std::endl;
      }
    }

    {
      std::cout << "\nUsing std::sregex_token_iterator:\n";
      auto end = std::sregex_token_iterator{};
      //  In the constructor we used, we did not specify the index of the subexpression to
      //  access through the iterator; therefore, the default value of 0 is used. That
      //  means this program will print the entire matches.
      for (auto it = std::sregex_token_iterator{ std::begin(text), std::end(text), rx };
           it != end; ++it) {
        std::cout << *it << std::endl;
      }
    }

    {
      std::cout << "\nUsing std::sregex_token_iterator with index 1:\n";
      auto end = std::sregex_token_iterator{};
      for (auto it
           // We wanted to access only the first subexpression -> specify the index of the
           // subexpression in the constructor of the token iterator (1).
           = std::sregex_token_iterator{ std::begin(text), std::end(text), rx, 1 };
           it != end; ++it) {
        std::cout << *it << std::endl;
      }
    }

    {
      std::cout << "\nUsing std::sregex_token_iterator with index -1:\n";
      auto end = std::sregex_token_iterator{};
      for (auto it
           // An interesting thing about the token iterator is that it can return the
           // unmatched parts of the string if the index of the subexpressions is -1
           = std::sregex_token_iterator{ std::begin(text), std::end(text), rx, -1 };
           it != end; ++it) {
        std::cout << *it << std::endl;
      }
    }
  }
}
