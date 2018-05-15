#pragma once

#include <array>
#include <chrono>
#include <complex>
#include <iostream>
#include <string>

// C++ defines a series of prefixes and suffixes to specify literals.
// C++11 allows creating user-defined literals by defining functions called literal
// operators that introduce suffixes for specifying literals.

// User-defined literals can have two forms: raw and cooked. Raw literals are not
// processed by the compiler, whereas cooked literals are values processed by the
// compiler.

namespace recipe_2_05 {
  // 1. Define your literals in a separate namespace to avoid name clashes.
  namespace compunits {
    // 2. Always prefix the user-defined suffix with an underscore.
    // 3. Define a literal operator of the following form for cooked literals:
    constexpr size_t operator"" _KB(unsigned long long const size)
    {
      return static_cast<size_t>(size * 1024);
    }
  } // namespace compunits

  void examples_kb()
  {
    // 4. Do not forget to use the literal namespace:
    using namespace compunits;

    // 5. Now you can use the KB literal:
    auto size{ 4_KB }; // size_t size = 4096;

    // The literal operator returns a constexpr value so that it can be used where compile
    // time values are expected, such as specifying the size of an array:
    using byte = unsigned char;
    auto buffer = std::array<byte, 1_KB>{}; // std::array<unsigned char, 1024>
  }

  namespace units {
    // A scoped enumeration for the possible types of units:
    enum class unit {
      kilogram,
      liter,
      meter,
      piece,
    };

    // A class template to specify quantities of a particular unit (such as 3.5 kilograms
    // or 42 pieces):
    template <unit U>
    class quantity {
      const double amount;

    public:
      constexpr explicit quantity(double const a)
        : amount(a)
      {
      }

      explicit operator double() const
      {
        return amount;
      }
    };

    // The operator+ and operator- functions for the quantity class template in order to
    // be able to add and subtract quantities:
    template <unit U>
    constexpr quantity<U> operator+(quantity<U> const& q1, quantity<U> const& q2)
    {
      return quantity<U>(static_cast<double>(q1) + static_cast<double>(q2));
    }

    template <unit U>
    constexpr quantity<U> operator-(quantity<U> const& q1, quantity<U> const& q2)
    {
      return quantity<U>(static_cast<double>(q1) - static_cast<double>(q2));
    }

    // Literal operators to create quantity literals, defined in an inner namespace called
    // unit_literals. The purpose of this is to avoid possible name clashes with literals
    // from other namespaces.
    namespace unit_literals {
      // _kg is defined for both integral and floating point literals ( 1_kg, 1.0_kg )
      constexpr quantity<unit::kilogram> operator"" _kg(long double const amount)
      {
        return quantity<unit::kilogram>{ static_cast<double>(amount) };
      }

      constexpr quantity<unit::kilogram> operator"" _kg(unsigned long long const amount)
      {
        return quantity<unit::kilogram>{ static_cast<double>(amount) };
      }

      // _l and _m are defined only for floating point literals ( 4.5_l, 10.0_m )
      constexpr quantity<unit::liter> operator"" _l(long double const amount)
      {
        return quantity<unit::liter>{ static_cast<double>(amount) };
      }

      constexpr quantity<unit::meter> operator"" _m(long double const amount)
      {
        return quantity<unit::meter>{ static_cast<double>(amount) };
      }

      // _pcs is only defined for integral literals ( 42_pcs. )
      constexpr quantity<unit::piece> operator"" _pcs(unsigned long long const amount)
      {
        return quantity<unit::piece>{ static_cast<double>(amount) };
      }
    } // namespace unit_literals
  }   // namespace units

  void example_units()
  {
    using namespace units;
    using namespace unit_literals;

    auto q1{ 1_kg };
    auto q2{ 4.5_kg };
    auto q3{ q1 + q2 };
    auto q4{ q2 - q1 };

    // auto q5{ 1.0_m + 1_pcs }; // error, cannot add meters and pieces
    // auto q6{ 1_l };   // error, cannot have an integer number of liters
    // auto q7{ 2.0_pcs } // error, can only have an integer number of pieces
  }

  void execute()
  {
    std::cout << "\nRecipe 2.05: Creating cooked user-defined literals."
              << "\n---------------------------------------------------\n";

    {
      // without prefixes/suffixes
      auto b{ true };    // boolean
      auto s{ "text" };  // const char[7]
      auto i{ 42 };      // int
      auto d{ 42.5 };    // double
      auto p{ nullptr }; // nullptr_t

      // with prefixes
      auto t1{ L"text" };           // const wchar_t[5]
      auto t2{ LR"(has ' and ")" }; // const wchar_t[5]
      auto hx{ 0xBAD };             // int (in hexadecimal representation)

      // with suffixes
      auto a{ 42u };   // unsigned int
      auto l{ 42l };   // signed long
      auto f{ 42.5f }; // float
    }

    {
      // Though user-defined literals are available from C++11, standard literal operators
      // have been available only from C++14. The following is a list of these standard
      // literal operators:

      // operator""s for defining std::basic_string literals:
      using namespace std::string_literals;
      auto s1{ "text"s };  // std::string
      auto s2{ L"text"s }; // std::wstring
      auto s3{ u"text"s }; // std::u16string
      auto s4{ U"text"s }; // std::u32string
    }

    {
      // operator""h, operator""min, operator""s, operator""ms, operator""us, and
      // operator""ns for creating a std::chrono::duration values:
      using namespace std::literals::chrono_literals;
      auto timer{ 2h + 42min + 15s }; // std::chrono::duration<long long>
    }

    {
      // operator""if, operator""i, and operator""il for creating std::complex values
      using namespace std::literals::complex_literals;
      auto c{ 12.0 + 4.5i }; // std::complex<double>
    }

    examples_kb();
    example_units();
  }
}
