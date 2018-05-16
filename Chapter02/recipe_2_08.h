#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// The string types from the standard library are a general purpose implementation that
// lacks many helpful methods. Third-party libraries that provide rich sets of string
// functionalities exist. However, in this recipe, we will look at implementing several
// simple, yet helpful, methods you may often need in practice.

// To implement these string helper functions, we need to include the header <string> for
// strings and <algorithm> for the general standard algorithms we will use.

namespace recipe_2_08 {
  namespace string_library {
    // The string library we will be implementing should work with all the standard string
    // types, std::string, std::wstring, std::u16string, and std::u32string.
    template <typename CharT>
    using tstring
      = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    template <typename CharT>
    using tstringstream
      = std::basic_stringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

    namespace mutable_version {
      template <typename CharT>
      inline void to_upper(tstring<CharT>& text)
      {
        std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
      }

      template <typename CharT>
      inline void to_lower(tstring<CharT>& text)
      {
        std::transform(std::begin(text), std::end(text), std::begin(text), tolower);
      }

      template <typename CharT>
      inline void reverse(tstring<CharT>& text)
      {
        std::reverse(std::begin(text), std::end(text));
      }

      template <typename CharT>
      inline void trim(tstring<CharT>& text)
      {
        auto first{ text.find_first_not_of(' ') };
        auto last{ text.find_last_not_of(' ') };
        text = text.substr(first, (last - first + 1));
      }

      template <typename CharT>
      inline void trimleft(tstring<CharT>& text)
      {
        auto first{ text.find_first_not_of(' ') };
        text = text.substr(first, text.size() - first);
      }

      template <typename CharT>
      inline void trimright(tstring<CharT>& text)
      {
        auto last{ text.find_last_not_of(' ') };
        text = text.substr(0, last + 1);
      }
    }

    template <typename CharT>
    inline tstring<CharT> to_upper(tstring<CharT> text)
    {
      std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
      return text;
    }

    template <typename CharT>
    inline tstring<CharT> to_lower(tstring<CharT> text)
    {
      std::transform(std::begin(text), std::end(text), std::begin(text), tolower);
      return text;
    }

    template <typename CharT>
    inline tstring<CharT> reverse(tstring<CharT> text)
    {
      std::reverse(std::begin(text), std::end(text));
      return text;
    }

    template <typename CharT>
    inline tstring<CharT> trim(tstring<CharT> const& text)
    {
      auto first{ text.find_first_not_of(' ') };
      auto last{ text.find_last_not_of(' ') };
      return text.substr(first, (last - first + 1));
    }

    template <typename CharT>
    inline tstring<CharT> trimleft(tstring<CharT> const& text)
    {
      auto first{ text.find_first_not_of(' ') };
      return text.substr(first, text.size() - first);
    }

    template <typename CharT>
    inline tstring<CharT> trimright(tstring<CharT> const& text)
    {
      auto last{ text.find_last_not_of(' ') };
      return text.substr(0, last + 1);
    }

    template <typename CharT>
    inline tstring<CharT> trim(tstring<CharT> const& text, tstring<CharT> const& chars)
    {
      auto first{ text.find_first_not_of(chars) };
      auto last{ text.find_last_not_of(chars) };
      return text.substr(first, (last - first + 1));
    }

    template <typename CharT>
    inline tstring<CharT> trimleft(tstring<CharT> const& text,
                                   tstring<CharT> const& chars)
    {
      auto first{ text.find_first_not_of(chars) };
      return text.substr(first, text.size() - first);
    }

    template <typename CharT>
    inline tstring<CharT> trimright(tstring<CharT> const& text,
                                    tstring<CharT> const& chars)
    {
      auto last{ text.find_last_not_of(chars) };
      return text.substr(0, last + 1);
    }

    template <typename CharT>
    inline tstring<CharT> remove(tstring<CharT> text, CharT const ch)
    {
      auto start = std::remove_if(std::begin(text), std::end(text),
                                  [=](CharT const c) { return c == ch; });
      text.erase(start, std::end(text));
      return text;
    }

    template <typename CharT>
    inline std::vector<tstring<CharT>> split(tstring<CharT> text, CharT const delimiter)
    {
      auto sstr = tstringstream<CharT>{ text };
      auto tokens = std::vector<tstring<CharT>>{};
      auto token = tstring<CharT>{};
      while (std::getline(sstr, token, delimiter)) {
        if (!token.empty())
          tokens.push_back(token);
      }

      return tokens;
    }
  }

  void execute()
  {
    std::cout << "\nRecipe 2.08: Creating a library of string helpers."
              << "\n--------------------------------------------------\n";

    //  For the standard user-defined literal operators.
    using namespace std::string_literals;

    std::cout << "to_upper:\n";
    auto ut{ string_library::to_upper("this is not UPPERCASE"s) };
    // ut = "THIS IS NOT UPPERCASE"
    std::cout << ut << "\n------\n";

    std::cout << "to_lower:\n";
    auto lt{ string_library::to_lower("THIS IS NOT lowercase"s) };
    // lt = "this is not lowercase"
    std::cout << lt << "\n------\n";

    std::cout << "reverse:\n";
    auto rt{ string_library::reverse("cookbook"s) }; // rt = "koobkooc"
    std::cout << rt << "\n------\n";

    std::cout << "trim, trimleft, trimright:\n";
    auto text1{ "   this is an example   "s };
    auto t1{ string_library::trim(text1) };      // t1 = "this is an example"
    auto t2{ string_library::trimleft(text1) };  // t2 = "this is an example   "
    auto t3{ string_library::trimright(text1) }; // t3 = "   this is an example"
    std::cout << t1 << "\n";
    std::cout << t2 << "\n";
    std::cout << t3 << "\n";

    auto chars1{ " !%\n\r"s };
    auto text3{ "!!  this % needs a lot\rof trimming  !\n"s };
    auto t7{ string_library::trim(text3, chars1) };
    // t7 = "this % needs a lot\rof trimming"
    std::cout << t7 << "\n";

    auto t8{ string_library::trimleft(text3, chars1) };
    // t8 = "this % needs a lot\rof trimming  !\n"
    std::cout << t8 << "\n";

    auto t9{ string_library::trimright(text3, chars1) };
    // t9 = "!!  this % needs a lot\rof trimming"
    std::cout << t9 << "\n------\n";

    std::cout << "remove:\n";
    auto text4{ "must remove all * from text**"s };
    auto t10{ string_library::remove(text4, '*') };
    // t10 = "must remove all  from text"
    std::cout << t10 << "\n";

    auto t11{ string_library::remove(text4, '!') };
    // t11 = "must remove all * from text**"
    std::cout << t11 << "\n------\n";

    std::cout << "split:\n";
    auto text5{ "this text will be split   "s };
    auto tokens1{ string_library::split(text5, ' ') };
    // tokens1 = {"this", "text", "will", "be", "split"}
    for (auto& token : tokens1)
      std::cout << token << " ";
    std::cout << "\n------\n";

    auto tokens2{ string_library::split(""s, ' ') };
    // tokens2 = {}
    for (auto& token : tokens2)
      std::cout << token << " ";
    std::cout << std::endl;
  }
}
