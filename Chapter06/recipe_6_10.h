#pragma once

#include <string>
#include <type_traits>
#include <iostream>

namespace recipe_6_10 {
  using namespace std::string_literals;

  struct foo {
    std::string serialize()
    {
      return "plain"s;
    }
  };

  struct bar {
    std::string serialize_with_encoding()
    {
      return "encoded"s;
    }
  };

  // Default value is false:
  template <typename T>
  struct is_serializable_with_encoding {
    static const bool value = false;
  };

  // Specialization for bar:
  template <>
  struct is_serializable_with_encoding<bar> {
    static const bool value = true;
  };

  namespace details {
    // Default template uses serialize()
    template <bool b>
    struct serializer {
      template <typename T>
      static auto serialize(T& v)
      {
        return v.serialize();
      }
    };

    // Specialization uses serialize_with_encoding():
    template <>
    struct serializer<true> {
      template <typename T>
      static auto serialize(T& v)
      {
        return v.serialize_with_encoding();
      }
    };
  }

  // Wrapper for serialize():
  template <typename T>
  auto serialize(T& v)
  {
    // if is_serializable_with_encoding<T>::value == true calls finally serialize_with_encoding()
    // if is_serializable_with_encoding<T>::value == true calls finally serialize()
    return details::serializer<is_serializable_with_encoding<T>::value>::serialize(v);
  }

  void execute()
  {
    std::cout << "\nRecipe 6.10: Writing your own type traits."
              << "\n------------------------------------------\n";

    {
      std::cout << "\nis_serializable_with_encoding? foo, bar, int, string:\n";

      std::cout << is_serializable_with_encoding<foo>::value << std::endl;
      std::cout << is_serializable_with_encoding<bar>::value << std::endl;
      std::cout << is_serializable_with_encoding<int>::value << std::endl;
      std::cout << is_serializable_with_encoding<std::string>::value << std::endl;
    }

    {
      std::cout << "\nWith a wrapper around serialize():\n";

      foo f;
      bar b;

      std::cout << serialize(f) << std::endl;
      std::cout << serialize(b) << std::endl;
    }
  }
}
