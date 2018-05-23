#pragma once

// The C++ input/output library provides a general purpose mechanism for handling
// internationalization features through LOCALES and FACETS.

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <locale>

namespace recipe_7_03 {
  void execute()
  {
    std::cout << "\nRecipe 7.03: Using localized settings for streams."
              << "\n--------------------------------------------------\n";

    {
      std::cout << "Use std::locale class to represent the localization settings.\n";

      // default construct
      auto loc_default = std::locale{};

      // from a name
      auto loc_us = std::locale{ "en_US.utf8" };

      // from another locale except for a facet
      auto loc1 = std::locale{ loc_default, new std::collate<wchar_t> };

      // from another local, except the facet in a category
      auto loc2 = std::locale{ loc_default, loc_us, std::locale::collate };
    }

    auto now = std::chrono::system_clock::now();
    auto stime = std::chrono::system_clock::to_time_t(now);
    auto ltime = std::localtime(&stime);

    std::vector<std::string> names{
      "John", "Adele", "ÅŠivind", "FranÃ§ois", "Robert", "Ä¨ke"
    };

    auto sort_and_print = [](std::vector<std::string> v, std::locale const& loc) {
      std::sort(v.begin(), v.end(), loc);
      for (auto const& s : v)
        std::cout << s << ' ';
      std::cout << std::endl;
    };

    {
      // Use a particular locale:
      std::cout << "\nGerman locale:\n";

      auto loc = std::locale("de_DE.utf8");

      // By default, all streams use the classic locale to write or parse text. However,
      // it is possible to change the locale used by a stream using the stream's imbue()
      // method. This is a member of the std::ios_base class that is the base for all
      // input/output streams. A companion member is the getloc() method that returns a
      // copy of the current stream's locale.

      // Use the imbue() method to change the current locale of an input/output stream:
      std::cout.imbue(loc);

      std::cout << 1000.50 << std::endl;                               // 1.000,5
      std::cout << std::showbase << std::put_money(1050) << std::endl; // 10,50 â‚¬
      std::cout << std::put_time(ltime, "%c") << std::endl; // So 04 Dez 2016 17:54:06 JST

      sort_and_print(names, loc);
    }

    {
      std::cout << "\nDefault user locale:\n";

      // Use a locale corresponding to the user settings (as defined in the system). This
      // is done by constructing an std::locale object from an empty string:

      auto loc = std::locale("");
      std::cout.imbue(loc);

      std::cout << 1000.50 << std::endl;                               // 1,000.5
      std::cout << std::showbase << std::put_money(1050) << std::endl; // $10.50
      std::cout << std::put_time(ltime, "%c")
                << std::endl; // Sun 04 Dec 2016 05:54:06 PM JST

      sort_and_print(names, loc); // adele Åke François John Øivind Robert
    }

    {
      std::cout << "\nEnglish American locale:\n";

      // Set and use the global locale:
      std::locale::global(std::locale("en_US.utf8"));

      auto loc = std::locale{};
      std::cout.imbue(loc);

      std::cout << 1000.50 << std::endl;                               // 1 000,5
      std::cout << std::showbase << std::put_money(1050) << std::endl; // 10,50 kr
      std::cout << std::put_time(ltime, "%c") << std::endl; // sön  4 dec 2016 18:02:29

      sort_and_print(names, loc); // adele François John Robert Åke Øivind
    }

    {
      std::cout << "\nClassic (default C locale) locale:\n";

      auto loc = std::locale::classic();
      std::cout.imbue(loc);

      std::cout << 1000.50 << std::endl;                               // 1000.5
      std::cout << std::showbase << std::put_money(1050) << std::endl; // 1050
      std::cout << std::put_time(ltime, "%c") << std::endl; // Sun Dec  4 17:55:14 2016

      sort_and_print(names, loc);
    }
  }
}
