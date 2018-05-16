#pragma once

// C++11 provides support for regular expressions within the standard library through a
// set of classes, algorithms, and iterators available in the header <regex>.

#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

// In order to verify that a string matches a regular expression, perform the following
// steps:

// 1. Include headers <regex> and <string> and the namespace std::string_literals for
// C++14 standard user-defined literals for strings.

// 2. Use raw string literals to specify the regular expression to avoid escaping
// backslashes (that can occur frequently).

// 3. Create an std::regex/std::wregex object (depending on the character set that is
// used) to encapsulate the regular expression.

// 4. To ignore casing or specify other parsing options, use an overloaded constructor
// that has an extra parameter for regular expression flags, e.g.
// std::regex_constants::icase

// 5. Use std::regex_match() to match the regular expression to an entire string.

namespace recipe_2_09 {
  using namespace std::string_literals;

  template <typename CharT>
  using tstring
    = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  template <typename CharT>
  bool is_valid_format(tstring<CharT> const& pattern, tstring<CharT> const& text)
  {
    auto rx = std::basic_regex<CharT>{ pattern, std::regex_constants::icase };
    return std::regex_match(text, rx);
  }

  bool is_valid_email_format(std::string const& email)
  {
    // This regular expression does not cover all possible e-mail formats.
    auto rx = std::regex{ R"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s,
                          std::regex_constants::icase };
    return std::regex_match(email, rx);
  }

  bool is_valid_email_format_w(std::wstring const& text)
  {
    return is_valid_format(LR"(^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}$)"s, text);
  }

  std::tuple<bool, std::string, std::string, std::string>
  is_valid_email_format_with_result(std::string const& email)
  {
    auto rx = std::regex{ R"(^([A-Z0-9._%+-]+)@([A-Z0-9.-]+)\.([A-Z]{2,})$)"s,
                          std::regex_constants::icase };
    auto result = std::smatch{};
    auto success = std::regex_match(email, result, rx);

    return std::make_tuple(success, success ? result[1].str() : ""s,
                           success ? result[2].str() : ""s,
                           success ? result[3].str() : ""s);
  }

  void execute()
  {
    std::cout
      << "\nRecipe 2.09: Verifying the format of a string using regular expressions."
      << "\n------------------------------------------------------------------------\n";

    auto ltest = [](std::string const& email) {
      std::cout << std::setw(30) << std::left << email << " : "
                << (is_valid_email_format(email) ? "valid" : "invalid") << std::endl;
    };

    auto ltest2 = [](auto const& email) {
      std::wcout << std::setw(30) << std::left << email << L" : "
                 << (is_valid_email_format_w(email) ? L"valid" : L"invalid") << std::endl;
    };

    auto ltest3 = [](std::string const& email) {
      // auto valid{ false };
      // auto localpart = std::string{};
      // auto hostname = std::string{};
      // auto dnslabel = std::string{};
      // std::tie(valid, localpart, hostname, dnslabel)

      auto [valid, localpart, hostname, dnslabel] = is_valid_email_format_with_result(email);

      std::cout << std::setw(30) << std::left << email << " : " << std::setw(10)
                << (valid ? "valid" : "invalid") << std::endl
                << "   local=" << localpart << ";domain=" << hostname
                << ";dns=" << dnslabel << std::endl;
    };

    std::cout << "Just check whether this is a valid email address:\n";
    ltest("JOHN.DOE@DOMAIN.COM"s);
    ltest("JOHNDOE@DOMAIL.CO.UK"s);
    ltest("JOHNDOE@DOMAIL.INFO"s);
    ltest("J.O.H.N_D.O.E@DOMAIN.INFO"s);
    ltest("ROOT@LOCALHOST"s);
    ltest("john.doe@domain.com"s);

    std::cout << "\nCheck wide strings:\n";
    ltest2(L"JOHN.DOE@DOMAIN.COM"s);
    ltest2(L"JOHNDOE@DOMAIL.CO.UK"s);
    ltest2(L"JOHNDOE@DOMAIL.INFO"s);
    ltest2(L"J.O.H.N_D.O.E@DOMAIN.INFO"s);
    ltest2(L"ROOT@LOCALHOST"s);
    ltest2(L"john.doe@domain.com"s);

    std::cout << "\nWe want also the parts:\n";
    ltest3("JOHN.DOE@DOMAIN.COM"s);
    ltest3("JOHNDOE@DOMAIL.CO.UK"s);
    ltest3("JOHNDOE@DOMAIL.INFO"s);
    ltest3("J.O.H.N_D.O.E@DOMAIN.INFO"s);
    ltest3("ROOT@LOCALHOST"s);
    ltest3("john.doe@domain.com"s);
  }
}
