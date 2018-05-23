#pragma once

// Use the following pattern:

// 1. Create a temporary file.

// 2. Copy only the content that you want from the original file to the temporary file.

// 3. Delete the original file.

// 4. Rename/move the temporary file to the name/location of the original file.

// If you take this approach, then you must make sure that the temporary file that is
// later replacing the original file has the same file permissions as the original file,
// otherwise, depending on the context of your solution, it can lead to problems. It might
// actually be better to copy the content of the temporary file to the original file.

#include <cstdio>
#include <cassert>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace recipe_7_09 {
  void execute()
  {
    std::cout << "\nRecipe 7.09: Removing content from a file."
              << "\n------------------------------------------\n\n";

    auto path = fs::current_path();
    auto initialpath = path / "sample.plays";
    assert(fs::exists(initialpath));

    auto filepath = path / "sample.dat";
    auto temppath = fs::temp_directory_path() / "sample.temp";
    std::cout << temppath << std::endl;
    auto err = std::error_code{};

    // make a copy of the original file
    {
      auto success = fs::copy_file(initialpath, filepath, err);
      if (!success || err) {
        std::cout << err.message() << std::endl;
        return;
      }
    }

    // remove content from file
    {
      std::ifstream in(filepath);
      if (!in.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return;
      }

      // 1. Create a temporary file.
      std::ofstream out(temppath, std::ios::trunc);
      if (!out.is_open()) {
        std::cout << "Temporary file could not be created!" << std::endl;
        return;
      }

      // 2. Copy only the content that you want from the original file to the temporary
      // file.
      auto line = std::string{};
      while (std::getline(in, line)) {
        if (!line.empty() && line.at(0) != ';') {
          std::cout << line << " " << line.at(0) << std::endl;
          out << line << '\n';
        }
      }

      in.close();
      out.close();

      // 3. Delete the original file.
      auto success = fs::remove(initialpath, err);
      if (!success || err) {
        std::cout << err.message() << std::endl;
        return;
      }

      // 4. Rename/move the temporary file to the name/location of the original file.
      fs::rename(temppath, initialpath, err);
      if (err) {
        std::cout << err.message() << std::endl;
      }
    }

    // clean up
    {
      auto success = fs::remove(filepath, err);
      if (!success || err) {
        std::cout << err.message() << std::endl;
      }
    }
  }
}
