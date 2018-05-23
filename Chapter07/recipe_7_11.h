#pragma once

// The file library provides two directory iterators, one called directory_iterator that
// iterates the content of a directory, and one called recursive_directory_iterator that
// iterates recursively the content of a directory and its subdirectories.

#include <experimental/filesystem>
#include <iomanip>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace recipe_7_11 {
  void visit_directory_1(fs::path const& dir)
  {
    std::cout << "Visit directory:\n";
    std::cout << "----------------\n\n";

    if (fs::exists(dir) && fs::is_directory(dir)) {
      for (auto const& entry : fs::directory_iterator(dir)) {
        auto filename = entry.path().filename();
        if (fs::is_directory(entry.status()))
          std::cout << "[+]" << filename << std::endl;
        else if (fs::is_symlink(entry.status()))
          std::cout << "[>]" << filename << std::endl;
        else if (fs::is_regular_file(entry.status()))
          std::cout << "   " << filename << std::endl;
        else
          std::cout << "[?]" << filename << std::endl;
      }
    } else {
      std::wcout << "Directory " << dir.c_str() << " does not exit" << std::endl;
    }
  }

  void visit_directory_2(fs::path const& dir)
  {
    std::cout << "\n12Visit directory recursively:\n";
    std::cout << "----------------------------\n\n";

    if (fs::exists(dir) && fs::is_directory(dir)) {
      for (auto const& entry : fs::recursive_directory_iterator(dir)) {
        auto filename = entry.path().filename();
        if (fs::is_directory(entry.status()))
          std::cout << "[+]" << filename << std::endl;
        else if (fs::is_symlink(entry.status()))
          std::cout << "[>]" << filename << std::endl;
        else if (fs::is_regular_file(entry.status()))
          std::cout << "   " << filename << std::endl;
        else
          std::cout << "[?]" << filename << std::endl;
      }
    } else {
      std::wcout << "Directory " << dir.c_str() << " does not exit" << std::endl;
    }
  }

  void visit_directory(fs::path const& dir, bool const recursive = false,
                       unsigned int const level = 0)
  {
    std::cout << "\nVisit directory recursively (manual recursion):\n";
    std::cout << "-----------------------------------------------\n\n";

    if (fs::exists(dir) && fs::is_directory(dir)) {
      auto lead = std::string(level * 3, ' ');
      for (auto const& entry : fs::directory_iterator(dir)) {
        auto filename = entry.path().filename();
        if (fs::is_directory(entry.status())) {
          std::cout << lead << "[+]" << filename << std::endl;
          if (recursive)
            visit_directory(entry, recursive, level + 1);
        } else if (fs::is_symlink(entry.status()))
          std::cout << lead << "[>]" << filename << std::endl;
        else if (fs::is_regular_file(entry.status()))
          std::cout << lead << "   " << filename << std::endl;
        else
          std::cout << lead << "[?]" << filename << std::endl;
      }
    } else {
      std::wcout << "Directory " << dir.c_str() << " does not exit" << std::endl;
    }
  }

  std::uintmax_t dir_size(fs::path const& path)
  {
    auto size = static_cast<uintmax_t>(-1);

    if (fs::exists(path) && fs::is_directory(path)) {
      for (auto const& entry : fs::recursive_directory_iterator(path)) {
        if (fs::is_regular_file(entry.status()) || fs::is_symlink(entry.status())) {
          auto err = std::error_code{};
          auto filesize = fs::file_size(entry);
          if (filesize != static_cast<uintmax_t>(-1))
            size += filesize;
        }
      }
    }

    return size;
  }

  void execute()
  {
    std::cout << "\nRecipe 7.11: Enumerating the content of a directory."
              << "\n----------------------------------------------------\n\n";

    auto path = fs::current_path() / ".";
    visit_directory_1(path);
    visit_directory_2(path);
    visit_directory(path, true);

    std::cout << dir_size(path) << std::endl;
  }
}
