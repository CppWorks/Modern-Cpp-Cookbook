#pragma once

#include <iostream>
#include <map>

// 1. Use an std::tuple for the return type.
// 2. Use structured bindings to unpack the values of the tuple into named objects.
// 3. Use decomposition declaration to bind the returned values to variables inside an 'if'
//    statement or 'switch' statement.

namespace recipe_1_13 {
  // 1. Use an std::tuple for the return type.
  std::tuple<int, std::string, double> find()
  {
    return std::make_tuple(1, "marius", 1234.5);
  }

  void execute()
  {
    std::cout
      << "\nRecipe 1.13: Using structured bindings to handle multi-return values."
      << "\n---------------------------------------------------------------------\n";

    std::cout << "\nUsing std::tie:";
    std::cout << "\n---------------\n";

    {
      std::map<int, std::string> m;
      // The insert method returns a std::pair containing an iterator to the inserted
      // element or the element that prevented the insertion, and a boolean indicating
      // whether the insertion was successful or not.
      auto result = m.insert({ 1, "one" });
      std::cout << "inserted = " << result.second << std::endl
                << "value = " << result.first->second << std::endl;
    }

    {
      // The preceding code can be made more readable with the use of std::tie, that
      // unpacks tuples into individual objects (and works with std::pair because
      // std::tuple has a converting assignment from std::pair):

      std::map<int, std::string> m;
      std::map<int, std::string>::iterator it;
      bool inserted;

      std::tie(it, inserted) = m.insert({ 1, "one" });
      std::cout << "inserted = " << inserted << std::endl
                << "value = " << it->second << std::endl;

      std::tie(it, inserted) = m.insert({ 1, "two" });
      std::cout << "inserted = " << inserted << std::endl
                << "value = " << it->second << std::endl;
    }

    {
      int id;
      std::string name;
      double score;

      std::tie(id, name, score) = find();

      std::cout << "id=" << id << " name=" << name << " score=" << score << std::endl;
    }

      // C++17 only
#ifdef __cpp_structured_bindings
    {
      std::cout << "\nC++17 has structured bindings:";
      std::cout << "\n------------------------------\n";
      std::map<int, std::string> m;

      // 2. Use decomposition declaration to bind the returned values to variables inside an
      //    if statement or switch statement.
      if (auto[it, inserted] = m.insert({ 1, "two" }); inserted) {
        std::cout << it->second << std::endl;
      }

      {
        // 3. Use structured bindings to unpack the values of the tuple into named
        //    objects.
        auto[it, inserted] = m.insert({ 1, "one" });
        std::cout << "inserted = " << inserted << std::endl
                  << "value = " << it->second << std::endl;
      }

      // The use of multiple blocks in the above example is necessary because variables
      // cannot be redeclared in the same block, and structured bindings imply a
      // declaration using the auto specifier. Therefore, if you need to make multiple
      // calls like in the example above and use structured bindings you must either use
      // different variable names or multiple blocks as shown above. An alternative to
      // that is to avoid structured bindings and use std::tie(), because it can be called
      // multiple times with the same variables, therefore you only need to declare them
      // once.

      {
        auto[it, inserted] = m.insert({ 1, "two" });
        std::cout << "inserted = " << inserted << std::endl
                  << "value = " << it->second << std::endl;
      }

      auto[id, name, score] = find();

      if (auto[id, name, score] = find(); score > 1000) {
        std::cout << name << std::endl;
      }
    }
#endif
  }
} // namespace recipe_1_13
