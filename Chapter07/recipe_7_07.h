#pragma once

// https://stackoverflow.com/questions/33149878/experimentalfilesystem-linker-error/33159746#33159746

#include <cassert>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace recipe_7_07 {
  void execute()
  {
    std::cout << "\nRecipe 7.07: Working with filesystem paths."
              << "\n-------------------------------------------\n\n";

    // append
    {
      auto path = fs::path{ "/home/marius/docs" };
      path /= "book";
      path = path / "modern" / "cpp";
      path.append("programming");

      std::cout << path << std::endl;
    }

    // concat
    {
      auto path = fs::path{ "/home/marius/docs" };

      path += "/book";
      path.concat("/modern");

      std::cout << path << std::endl;
    }

    // decomposition
    {
      auto path = fs::path{ "/home/marius/docs" };

      path /= "sample.file.txt";

      std::cout << "root:        " << path.root_name() << std::endl
                << "root dir:    " << path.root_directory() << std::endl
                << "root path:   " << path.root_path() << std::endl
                << "rel path:    " << path.relative_path() << std::endl
                << "parent path: " << path.parent_path() << std::endl
                << "filename:    " << path.filename() << std::endl
                << "stem:        " << path.stem() << std::endl
                << "extension:   " << path.extension() << std::endl;
    }

    // query
    {
      auto path = fs::path{ "/home/marius/docs" };

      path /= "sample.file.txt";

      std::cout << "has root:        " << path.has_root_name() << std::endl
                << "has root dir:    " << path.has_root_directory() << std::endl
                << "has root path:   " << path.has_root_path() << std::endl
                << "has rel path:    " << path.has_relative_path() << std::endl
                << "has parent path: " << path.has_parent_path() << std::endl
                << "has filename:    " << path.has_filename() << std::endl
                << "has stem:        " << path.has_stem() << std::endl
                << "has extension:   " << path.has_extension() << std::endl;
    }

    // absolute / relative
    {
      auto path1 = fs::current_path();
      auto path2 = fs::path{ "marius/temp" };

      std::cout << "absolute: " << path1.is_absolute() << std::endl
                << "absolute: " << path2.is_absolute() << std::endl;
    }

    // modifiers
    {
      auto path = fs::path{ "/home/marius/docs" };

      path /= "sample.file.txt";

      path.replace_filename("output");
      path.replace_extension(".log");

      assert(fs::path{ "/home/marius/docs/output.log" } == path);

      path.remove_filename();
      assert(fs::path{ "/home/marius/docs" } == path);
    }

    // preferred
    {
      auto path = fs::path{ "/home/marius/docs" };
      path.make_preferred();
      // std::cout << path << std::endl;
      assert(path == fs::path{ "/home/marius/docs" });
    }

    // iterating
    {
      auto path = fs::path{ "/home/marius/docs" };

      path /= "sample.file.txt";

      for (auto const& part : path) {
        std::cout << part << std::endl;
      }
    }
  }
}
