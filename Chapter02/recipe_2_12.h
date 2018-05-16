#pragma once

#include <iostream>
#include <string_view>

// When working with strings, temporary objects are created all the time. This represents
// a performance issue. For this purpose, the C++17 standard provides a new string class
// template called std::basic_string_view that represents a non-owning constant reference
// to a string.

// You should use std::string_view to pass a parameter to a function (or return a value
// from a function), instead of std::string const & unless your code needs to call other
// functions that take std::string parameters (in which case, conversions would be
// necessary).

// The std::basic_string_view class template is intended to solve this problem. This class
// template is very similar to std::basic_string, the two having almost the same
// interface. The reasons for this is that the std::basic_string_view is intended to be
// used instead of a constant reference to an std::basic_string without further code
// changes.

//  On the other hand, converting from an std::basic_string_view to an std::basic_string
//  is easy because the former has both a to_string() and a converting operator
//  std::basic_string to create a new std::basic_string object.

// In addition to the methods that are identical to those available in std::basic_string,
// the std::basic_string_view has two more:

// 1.) remove_prefix(): Shrinks the view by incrementing the start with N characters and
// decrementing the length with N characters.

// 2.) remove_suffix(): Shrinks the view by decrementing the length with N characters.

// When using an std::basic_string_view, you must be aware of two things: you cannot
// change the underlying data referred by a view and you must manage the lifetime of the
// data, as the view is a non-owning reference.

namespace recipe_2_12 {
  std::string get_filename(std::string const& str)
  {
    // Before C++17.
    auto const pos1{ str.find_last_of('\\') };
    auto const pos2{ str.find_last_of('.') };
    return str.substr(pos1 + 1, pos2 - pos1 - 1);
  }

  std::string_view get_filename_view(std::string_view str)
  {
    // With C++17 and string_view.
    auto const pos1{ str.find_last_of('\\') };
    auto const pos2{ str.find_last_of('.') };
    return str.substr(pos1 + 1, pos2 - pos1 - 1);
  }

  std::string_view trim_view(std::string_view str)
  {
    auto const pos1{ str.find_first_not_of(" ") };
    auto const pos2{ str.find_last_not_of(" ") };
    str.remove_suffix(str.length() - pos2 - 1);
    str.remove_prefix(pos1);

    return str;
  }

  void execute()
  {
    std::cout
      << "\nRecipe 2.12: Using string_view instead of constant string references."
      << "\n---------------------------------------------------------------------\n";

    {
      std::cout << "Searching for leading underscore in file name:\n";
      auto name1 = get_filename(R"(c:\test\example1.doc)"); // example1
      auto name2 = get_filename(R"(c:\test\example2)");     // example2
      // The function paramter of get_filename is a constant std::string reference, but
      // the function is called with a string literal, which means std::string needs to be
      // constructed from the literal.
      if (get_filename(R"(c:\test\_sample_.tmp)").front() == '_') {
        std::cout << "Found underscore." << std::endl;
      }
    }

    {
      std::cout << "\nGetting file names:\n";
      char const file1[]{ R"(c:\test\example1.doc)" };
      auto name1 = get_filename_view(file1);

      std::string file2{ R"(c:\test\example2)" };
      // Still temporary objects as file2 is a standard string, but objects are very
      // small.
      auto name2 = get_filename_view(file2);

      // With string_view as argument there are no temporary string objects.
      auto name3 = get_filename_view(std::string_view(file1, 16));

      std::cout << name1 << std::endl;
      std::cout << name2 << std::endl;
      std::cout << name3 << std::endl;
    }

    {
      auto sv1{ trim_view("sample") };
      auto sv2{ trim_view("  sample") };
      auto sv3{ trim_view("sample  ") };
      auto sv4{ trim_view("  sample  ") };

      std::cout << "\nTrimming strings:\n";
      std::cout << sv1 << std::endl;
      std::cout << sv2 << std::endl;
      std::cout << sv3 << std::endl;
      std::cout << sv4 << std::endl;
    }
  }
}
