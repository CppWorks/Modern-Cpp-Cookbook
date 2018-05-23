#pragma once

// We will see how we can use the directory iterators and the iterating patterns shown
// earlier to find files that match a given criteria.

#include <experimental/filesystem>
#include <functional>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace recipe_7_12 {
  std::vector<fs::path> find_files(fs::path const& dir,
                                   std::function<bool(fs::path const&)> filter)
  {
    auto result = std::vector<fs::path>{};

    if (fs::exists(dir)) {
      for (auto const& entry : fs::recursive_directory_iterator(
             dir, fs::directory_options::follow_directory_symlink)) {
        if (fs::is_regular_file(entry) && filter(entry)) {
          result.push_back(entry);
        }
      }
    }

    return result;
  }

  void execute()
  {
    std::cout << "\nRecipe 7.12: Finding a file."
              << "\n----------------------------\n\n";

    // find files containing prefix 'file_'
    {
      std::cout << "Files beginning with 'file_'\n\n";

      auto results = find_files(fs::current_path() / "..", [](fs::path const& p) {
        auto filename = p.wstring();
        return filename.find(L"file_") != std::wstring::npos;
      });

      for (auto const& path : results) {
        std::cout << path << std::endl;
      }
    }

    // find files with extension '.cpp'
    {
      std::cout << "\nSource files:\n\n";

      auto results = find_files(fs::current_path() / "..", [](fs::path const& p) {
        return p.extension() == L".cpp";
      });

      for (auto const& path : results) {
        std::cout << path << std::endl;
      }
    }
  }
}
