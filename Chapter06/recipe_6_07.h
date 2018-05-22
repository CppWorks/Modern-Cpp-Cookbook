#pragma once

// std::variant is a new standard container added to C++17

// Variants are intended to be used for holding alternatives of similar non-polymorphic and non-POD types.

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace recipe_6_07 {
  using namespace std::string_literals;

  template <typename CharT>
  using tstring
    = std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT>>;

  template <typename CharT>
  inline tstring<CharT> to_upper(tstring<CharT> text)
  {
    std::transform(std::begin(text), std::end(text), std::begin(text), toupper);
    return text;
  }

  enum class Genre { Drama, Action, SF, Commedy };

  struct Movie {
    std::string title;
    std::chrono::minutes length;
    std::vector<Genre> genre;
  };

  struct Track {
    std::string title;
    std::chrono::seconds length;
  };

  struct Music {
    std::string title;
    std::string artist;
    std::vector<Track> tracks;
  };

  struct Software {
    std::string title;
    std::string vendor;
  };

  // Here is our little std::variant:
  using dvd = std::variant<Movie, Music, Software>;

  void execute()
  {
    std::cout << "\nRecipe 6.07: Visiting a std::variant."
              << "\n-------------------------------------\n";

    {
      using namespace std::chrono_literals;

      std::vector<dvd> dvds{
        Movie{ "The Matrix"s, 2h + 16min, { Genre::Action, Genre::SF } },
        Music{
          "The Wall"s,
          "Pink Floyd"s,
          { { "Mother"s, 5min + 32s }, { "Another Brick in the Wall"s, 9min + 8s } } },
        Software{ "Windows"s, "Microsoft"s },
      };

      // To visit a variant, you must provide one or more actions for the possible
      // alternatives of the variant. There are several types of visitors that are used
      // for different purposes:

      // Visitation is done by invoking std::visit() with the visitor and one or more
      // variant objects. In the examples we visit a single variant object, but visiting
      // multiple variants does not imply anything more than passing them as arguments to
      // std::visit().

      // 1. Void visitor:
      for (auto const& d : dvds) {
        std::visit([](auto&& arg) { std::cout << arg.title << std::endl; }, d);
      }

      std::cout << "----------------------\n";

      // 2. Value returning visitor:
      for (auto const& d : dvds) {
        auto result = std::visit(
          [](auto&& arg) -> dvd {
            auto cpy{ arg };
            cpy.title = to_upper(cpy.title);
            return cpy;
          },
          d);

        std::visit([](auto&& arg) { std::cout << arg.title << std::endl; }, result);
      }

      std::cout << "----------------------\n";

      // 3. Type-matching visitor.

      // Implemented by providing a function object that has an overloaded call operator
      // for each alternative type of the variant:
      struct visitor_functor {
        void operator()(Movie const& arg) const
        {
          std::cout << "Movie" << std::endl;
          std::cout << "\tTitle: " << arg.title << std::endl;
          std::cout << "\tLength: " << arg.length.count() << "min" << std::endl;
        }

        void operator()(Music const& arg) const
        {
          std::cout << "Music" << std::endl;
          std::cout << "\tTitle: " << arg.title << std::endl;
          std::cout << "\tArtist: " << arg.artist << std::endl;
          for (auto const& t : arg.tracks)
            std::cout << "\t\tTrack: " << t.title << ", " << t.length.count() << "sec"
                      << std::endl;
        }

        void operator()(Software const& arg) const
        {
          std::cout << "Software" << std::endl;
          std::cout << "\tTitle: " << arg.title << std::endl;
          std::cout << "\tVendor: " << arg.vendor << std::endl;
        }
      };

      for (auto const& d : dvds) {
        std::visit(visitor_functor(), d);
      }

      std::cout << "----------------------\n";

      // 4. Type-matching visitor.

      // Implemented by providing a lambda expression that performs an action based on the
      // type of the alternative:
      for (auto const& d : dvds) {
        std::visit(
          [](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Movie>) {
              std::cout << "Movie" << std::endl;
              std::cout << "\tTitle: " << arg.title << std::endl;
              std::cout << "\tLength: " << arg.length.count() << "min" << std::endl;
            } else if constexpr (std::is_same_v<T, Music>) {
              std::cout << "Music" << std::endl;
              std::cout << "\tTitle: " << arg.title << std::endl;
              std::cout << "\tArtist: " << arg.artist << std::endl;
              for (auto const& t : arg.tracks)
                std::cout << "\t\tTrack: " << t.title << ", " << t.length.count() << "sec"
                          << std::endl;
            } else if constexpr (std::is_same_v<T, Software>) {
              std::cout << "Software" << std::endl;
              std::cout << "\tTitle: " << arg.title << std::endl;
              std::cout << "\tVendor: " << arg.vendor << std::endl;
            }
          },
          d);
      }

      // Movie
      //   Title: The Matrix
      //   Length: 136min
      // Music
      //   Title: The Wall
      //   Artist: Pink Floyd
      //     Track: Mother, 332sec
      //     Track: Another Brick in the Wall, 548sec
      // Software
      //   Title: Windows
      //   Vendor: Microsoft
    }
  }
}
